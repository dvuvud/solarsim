#pragma once

#include <graphics/shader.hpp>
#include <string>

namespace solarsim {
	class Material {
		public:
			Material(const std::string& vertexPath, const std::string& fragPath) : m_shader(vertexPath.c_str(), fragPath.c_str()) {}

			Material(const Material&) = delete;
			Material& operator=(const Material&) = delete;

			// TODO: Update this later as Material gets more things added to it
			Material(Material&&) noexcept = default;
			Material& operator=(Material&&) noexcept = default;

			void bind() {m_shader.bind();}
			Shader m_shader;
		private:
	};
}
