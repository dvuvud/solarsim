#version 330 core

layout(std140) uniform LightsBuffer {
	struct Light {
		vec3 pos;
		vec3 color;
	} lights[64];
	int lightCount;
};

out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
