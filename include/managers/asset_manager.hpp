#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

namespace solarsim {
	struct Mesh;
	struct Material;
	struct Shader;

	/** Temporarily predefined cube mesh with positions and normals */
	const std::vector<float> cube = {
		// positions          // normals
		// Front face
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		// Back face
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		// Left face
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		// Right face
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		// Top face
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,

		// Bottom face
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f
	};

	/**
	 * @brief Manages loading and caching of game assets (meshes, materials, shaders)
	 * 
	 * @note Singleton pattern with lazy loading and caching
	 * @warning All asset loading requires active OpenGL context
	 */
	class AssetManager {
		public:
			AssetManager(const AssetManager&) = delete;
			AssetManager& operator=(const AssetManager&) = delete;

			/**
			 * @brief Get the singleton AssetManager instance
			 * @return AssetManager& Reference to the asset manager
			 */
			static AssetManager& get();

			/**
			 * @brief Load or retrieve a cached mesh by ID
			 * @param meshID Unique identifier for the mesh
			 * @return std::shared_ptr<Mesh> Shared pointer to the mesh
			 * 
			 * @note Currently supports predefined shapes: "cube", "sphere", "grid"
			 * @warning Undefined behavior if meshID is not recognized as of now
			 */
			std::shared_ptr<Mesh> LoadMesh(const std::string& meshID);

			/**
			 * @brief Load or retrieve a cached material by ID
			 * @param materialID Unique identifier for the material
			 * @return std::shared_ptr<Material> Shared pointer to the material
			 * 
			 * @note Currently supports predefined materials only
			 * @warning Undefined behavior if materialID is not recognized as of now
			 */
			std::shared_ptr<Material> LoadMaterial(const std::string& materialID);

			/**
			 * @brief Load or retrieve a cached shader by ID
			 * @param shaderID Unique identifier for the shader
			 * @return std::shared_ptr<Shader> Shared pointer to the shader
			 * 
			 * @note Currently supports predefined shaders only
			 * @warning Undefined behavior if shaderID is not recognized as of now
			 */
			std::shared_ptr<Shader> LoadShader(const std::string& shaderID);

		private:
			/** Cache of loaded materials */
			std::unordered_map<std::string, std::shared_ptr<Material>> loadedMaterials;
			/** Cache of loaded meshes */
			std::unordered_map<std::string, std::shared_ptr<Mesh>> loadedMeshes;
			/** Cache of loaded shader shaders */
			std::unordered_map<std::string, std::shared_ptr<Shader>> loadedShaders;

			/**
			 * @brief Generate sphere mesh geometry
			 * @param vertices Output vector for vertex data
			 * @param indices Output vector for index data
			 * @param radius Sphere radius
			 * @param resolution Tessellation resolution
			 */
			void generateSphere(std::vector<float>& vertices, std::vector<uint32_t>& indices, float radius=1.0f, int resolution=100);

			/**
			 * @brief Generate grid mesh geometry
			 * @param vertices Output vector for vertex data
			 * @param indices Output vector for index data
			 * @param spacing Distance between grid lines
			 * @param extent Number of lines in each direction from center
			 */
			void generateGrid(std::vector<float>& vertices, std::vector<uint32_t>& indices, float spacing=20.0f, int extent=100);

			AssetManager() {}
			~AssetManager() {}
	};
}
