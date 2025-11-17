#version 330 core

out vec4 FragColor;

in vec3 WorldPos;

uniform vec3 uLightPositions[16];
uniform vec3 uLightColors[16];
uniform float uLightRadii[16];
uniform int uLightCount;

void main() {
	vec3 result = vec3(0.0);
	for (int i = 0; i < uLightCount; ++i) {
		float distanceToLight = length(uLightPositions[i] - WorldPos);
		float brightness = 1.0 - smoothstep(0.0, uLightRadii[i], distanceToLight);
		float ambient = 0.1;
		brightness = max(ambient, brightness);
		result += uLightColors[i] * brightness;
	}
	FragColor = vec4(result, 1.0);
}
