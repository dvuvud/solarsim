#version 330 core

layout(std140) uniform LightsBuffer {
	struct Light {
		vec3 position; float pad0;
		vec3 color; float pad1;
	} lights[64];
	int lightCount;
	vec3 pad2;
};

out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
