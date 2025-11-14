#pragma once

#include <graphics/shader.hpp>
#include <string>

namespace solarsim {
	class Material {
		public:
			Material(const std::string& vertexPath, const std::string& fragPath) : m_shader(vertexPath.c_str(), fragPath.c_str()) {}
			void bind() {m_shader.bind();}
			Shader m_shader;
		private:
	};
}
