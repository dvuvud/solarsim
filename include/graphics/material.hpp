#pragma once

namespace solarsim {
	class Shader;
	class Material {
		public:
			Material(Shader* p_shader) : m_shader(p_shader) {}
			Shader* m_shader;
	};
}
