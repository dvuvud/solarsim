#version 330 core

out vec4 FragColor;

in vec3 WorldPos;

uniform vec3 uLightPos;
uniform float uLightRadius;

void main() {
	float distanceToLight = length(uLightPos - WorldPos);
	float brightness = 1.0 - smoothstep(0.0, uLightRadius, distanceToLight);
	float ambient = 0.1;
	brightness = max(ambient, brightness);
	FragColor = vec4(vec3(brightness), 1.0);
}
