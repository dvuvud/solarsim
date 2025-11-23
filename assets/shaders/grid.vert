#version 330 core

layout(location = 0) in vec3 aPos;

layout(std140) uniform CameraBuffer {
	vec3 uPos; float pad0;
	mat4 uV;
	mat4 uP;
	mat4 uVP;
};

void main()
{
	gl_Position = uVP * vec4(aPos, 1.0);
}
