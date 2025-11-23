#version 330 core

layout(std140) uniform LightsBuffer {
	struct Light {
		vec4 pos;
		vec4 color;
	} lights[64];
	int lightCount;
};

in vec3 WorldPos;

out vec4 FragColor;

void main()
{
	vec3 result = vec3(0.0);
	for (int i = 0; i < lightCount; ++i) {
		float distanceToLight = length(lights[i].pos.xyz - WorldPos);
		float brightness = 1.0 - smoothstep(0.0, lights[i].color.w, distanceToLight);
		float ambient = 0.1;
		brightness = max(ambient, brightness);
		result += lights[i].color.xyz * brightness;
	}
	FragColor = vec4(result, 1.0);
}
