#include <gtest/gtest.h>
#include <engine/renderer.hpp>
#include <scene/scene.hpp>
#include <components/transform_component.hpp>
#include <components/mesh_component.hpp>
#include <components/camera_component.hpp>
#include <components/light_component.hpp>
#include <components/rigid_body_component.hpp>
#include <components/grid_component.hpp>

using namespace solarsim;

class RendererComponentsTest : public ::testing::Test {
	protected:
		void SetUp() override {
			scene = std::make_unique<Scene>();
		}

		void TearDown() override {
			scene.reset();
		}

		std::unique_ptr<Scene> scene;
};

// Test 1: Renderer UBO data structures
TEST_F(RendererComponentsTest, UBODataStructures) {
	// Test CameraUBO structure
	Renderer::CameraUBO camUBO;
	camUBO.pos = glm::vec3(1.0f, 2.0f, 3.0f);
	camUBO.view = glm::mat4(1.0f);
	camUBO.proj = glm::mat4(1.0f);
	camUBO.viewProj = glm::mat4(1.0f);

	EXPECT_EQ(camUBO.pos, glm::vec3(1.0f, 2.0f, 3.0f));

	// Test LightData structure
	Renderer::LightData lightData;
	lightData.pos = glm::vec4(10.0f, 5.0f, 0.0f, 0.0f);
	lightData.color = glm::vec4(1.0f, 0.9f, 0.8f, 100.0f);

	EXPECT_EQ(lightData.pos, glm::vec4(10.0f, 5.0f, 0.0f, 0.0f));

	// Test RBData structure
	Renderer::RBData rbData;
	rbData.mPos = glm::vec4(5.0f, 3.0f, 2.0f, 1000.0f);

	EXPECT_EQ(rbData.mPos, glm::vec4(5.0f, 3.0f, 2.0f, 1000.0f));
}

// Test 2: Component default values
TEST_F(RendererComponentsTest, ComponentDefaults) {
	// Test CameraComponent defaults
	CameraComponent cam;
	EXPECT_EQ(cam.fov, 45.0f);
	EXPECT_EQ(cam.near, 0.1f);
	EXPECT_EQ(cam.far, 2000.0f);
	EXPECT_EQ(cam.aspect, 800.0f / 600.0f);
	EXPECT_TRUE(cam.primary);

	// Test LightComponent defaults
	LightComponent light;
	EXPECT_EQ(light.color, glm::vec3(1.0f));
	EXPECT_EQ(light.radius, 135.0f);

	// Test MeshComponent (no specific defaults, but test creation)
	MeshComponent mesh;
	EXPECT_TRUE(mesh.meshID.empty());
	EXPECT_TRUE(mesh.materialID.empty());

	// Test GridComponent
	GridComponent grid;
	EXPECT_TRUE(grid.meshID.empty());
	EXPECT_TRUE(grid.materialID.empty());
}

// Test 3: Entity view combinations for rendering
TEST_F(RendererComponentsTest, RendererViewCombinations) {
	auto& registry = scene->registry;

	// Create different types of renderable entities
	Entity meshOnly = registry.createEntity();
	registry.addComponent(meshOnly, TransformComponent{});
	registry.addComponent(meshOnly, MeshComponent{});

	Entity lightOnly = registry.createEntity();
	registry.addComponent(lightOnly, TransformComponent{});
	registry.addComponent(lightOnly, LightComponent{});

	Entity physicsOnly = registry.createEntity();
	registry.addComponent(physicsOnly, TransformComponent{});
	registry.addComponent(physicsOnly, RigidBodyComponent{});

	Entity complexEntity = registry.createEntity();
	registry.addComponent(complexEntity, TransformComponent{});
	registry.addComponent(complexEntity, MeshComponent{});
	registry.addComponent(complexEntity, LightComponent{});
	registry.addComponent(complexEntity, RigidBodyComponent{});

	// Test different view combinations
	auto meshEntities = registry.view<TransformComponent, MeshComponent>();
	EXPECT_EQ(meshEntities.size(), 2); // meshOnly and complexEntity

	auto lightEntities = registry.view<TransformComponent, LightComponent>();
	EXPECT_EQ(lightEntities.size(), 2); // lightOnly and complexEntity

	auto physicsEntities = registry.view<TransformComponent, RigidBodyComponent>();
	EXPECT_EQ(physicsEntities.size(), 2); // physicsOnly and complexEntity

	auto allThree = registry.view<TransformComponent, MeshComponent, LightComponent, RigidBodyComponent>();
	EXPECT_EQ(allThree.size(), 1); // Only complexEntity
}

// Test 4: Transform matrix caching
TEST_F(RendererComponentsTest, TransformMatrixCaching) {
	auto& registry = scene->registry;

	Entity entity = registry.createEntity();
	TransformComponent transform;
	transform.position = glm::vec3(5.0f, 3.0f, 1.0f);
	transform.dirty = true;

	registry.addComponent(entity, transform);

	auto& tf = registry.getComponent<TransformComponent>(entity);

	// First call should calculate matrix
	glm::mat4 matrix1 = tf.getModelMatrix();
	EXPECT_FALSE(tf.dirty);

	// Second call should use cached matrix
	glm::mat4 matrix2 = tf.getModelMatrix();
	EXPECT_FALSE(tf.dirty);

	// Matrices should be identical
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			EXPECT_EQ(matrix1[i][j], matrix2[i][j]);
		}
	}

	// Changing position should mark dirty again
	tf.position.x += 1.0f;
	tf.dirty = true;
	EXPECT_TRUE(tf.dirty);
}

// Test 5: Light component properties
TEST_F(RendererComponentsTest, LightComponentProperties) {
	auto& registry = scene->registry;

	Entity light = registry.createEntity();
	LightComponent lightComp;
	lightComp.color = glm::vec3(0.8f, 0.9f, 1.0f);
	lightComp.radius = 200.0f;

	registry.addComponent(light, lightComp);

	auto& lightRetrieved = registry.getComponent<LightComponent>(light);
	EXPECT_EQ(lightRetrieved.color, glm::vec3(0.8f, 0.9f, 1.0f));
	EXPECT_EQ(lightRetrieved.radius, 200.0f);

	// Test different light colors
	Entity warmLight = registry.createEntity();
	registry.addComponent(warmLight, LightComponent{
			.color = glm::vec3(1.0f, 0.9f, 0.7f),
			.radius = 150.0f
			});

	auto& warmLightComp = registry.getComponent<LightComponent>(warmLight);
	EXPECT_EQ(warmLightComp.color, glm::vec3(1.0f, 0.9f, 0.7f));
	EXPECT_EQ(warmLightComp.radius, 150.0f);
}
