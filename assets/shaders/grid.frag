#version 330 core

layout(std140) uniform LightsBuffer {
	struct Light {
		vec3 pos;
		vec3 color;
	} lights[64];
	int lightCount;
};

in vec3 WorldPos;

out vec4 FragColor;

void main()
{
	const float lightRadius = 40.0;
	vec3 result = vec3(0.0);
	for (int i = 0; i < lightCount; ++i) {
		float distanceToLight = length(lights[i].pos - WorldPos);
		float brightness = 1.0 - smoothstep(0.0, lightRadius, distanceToLight);
		float ambient = 0.1;
		brightness = max(ambient, brightness);
		result += lights[i].color * brightness;
	}
	FragColor = vec4(result, 1.0);
}
