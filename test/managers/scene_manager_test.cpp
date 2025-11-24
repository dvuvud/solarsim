#include <gtest/gtest.h>
#include <managers/scene_manager.hpp>
#include <scene/scene.hpp>

using namespace solarsim;

class SceneManagerTest : public ::testing::Test {
	protected:
		void SetUp() override {
			sceneManager = &SceneManager::get();
		}

		void TearDown() override {
			sceneManager->unloadScene();
		}

		SceneManager* sceneManager;
};

// Test 1: Singleton pattern
TEST_F(SceneManagerTest, SingletonPattern) {
	SceneManager& instance1 = SceneManager::get();
	SceneManager& instance2 = SceneManager::get();

	// Should return the same instance
	EXPECT_EQ(&instance1, &instance2);
}

// Test 2: Initial state
TEST_F(SceneManagerTest, InitialState) {
	// Initially no active scene
	EXPECT_EQ(sceneManager->active(), nullptr);
}

// Test 3: Scene loading
TEST_F(SceneManagerTest, SceneLoading) {
	auto scene = std::make_unique<Scene>();
	Scene* scenePtr = scene.get();

	sceneManager->loadScene(std::move(scene));

	EXPECT_EQ(sceneManager->active(), scenePtr);
	EXPECT_NE(sceneManager->active(), nullptr);
}

// Test 4: Scene unloading
TEST_F(SceneManagerTest, SceneUnloading) {
	// Load a scene first
	sceneManager->loadScene(std::make_unique<Scene>());
	EXPECT_NE(sceneManager->active(), nullptr);

	// Then unload it
	sceneManager->unloadScene();
	EXPECT_EQ(sceneManager->active(), nullptr);
}

// Test 5: Scene replacement
TEST_F(SceneManagerTest, SceneReplacement) {
	auto scene1 = std::make_unique<Scene>();
	Scene* scene1Ptr = scene1.get();

	sceneManager->loadScene(std::move(scene1));
	EXPECT_EQ(sceneManager->active(), scene1Ptr);

	auto scene2 = std::make_unique<Scene>();
	Scene* scene2Ptr = scene2.get();

	// Load new scene (should replace the old one)
	sceneManager->loadScene(std::move(scene2));
	EXPECT_EQ(sceneManager->active(), scene2Ptr);
	EXPECT_NE(sceneManager->active(), scene1Ptr);
}

// Test 6: Scene state persistence
TEST_F(SceneManagerTest, SceneStatePersistence) {
	auto scene = std::make_unique<Scene>();
	scene->paused = true;
	scene->reverse = true;
	scene->timeScale = 2.0f;

	sceneManager->loadScene(std::move(scene));

	// Verify state is preserved
	EXPECT_TRUE(sceneManager->active()->paused);
	EXPECT_TRUE(sceneManager->active()->reverse);
	EXPECT_EQ(sceneManager->active()->timeScale, 2.0f);
}
