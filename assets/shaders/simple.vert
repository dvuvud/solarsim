#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

layout(std140) uniform CameraBuffer {
	vec3 uPos; float pad0;
	mat4 uV;
	mat4 uP;
	mat4 uVP;
};

uniform mat4 uModel;

out vec3 FragPos;
out vec3 Normal;

void main()
{
	FragPos = vec3(uModel * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(uModel))) * aNormal; 
	gl_Position = uVP * vec4(FragPos, 1.0);
}
