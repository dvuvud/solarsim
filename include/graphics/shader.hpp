#pragma once

#include <string>
#include <glm/mat4x4.hpp>

namespace solarsim {
	struct Shader
	{
		unsigned int programID;
		void use();
		void setUniform(const std::string& name, const glm::mat4& value);
	};
}
