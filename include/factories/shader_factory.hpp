#pragma once

#include <graphics/shader.hpp>

namespace solarsim {
	class ShaderFactory {
		public:
			static ShaderFactory& Get() {
				static ShaderFactory instance;
				return instance;
			}

			std::shared_ptr<Shader> LoadShader(const std::string& name) {
				auto it = shaderCache.find(name);
				if (it != shaderCache.end())
					return it->second;

				auto shader = std::make_shared<Shader>();
				shader->LoadFromFile("assets/shaders/" + name + ".vert",
						"assets/shaders/" + name + ".frag");

				shaderCache[name] = shader;
				return shader;
			}

		private:
			ShaderFactory() {}
			~ShaderFactory() {}
			std::unordered_map<std::string, std::shared_ptr<Shader>> shaderCache;
	};
}
