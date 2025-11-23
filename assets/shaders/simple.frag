#version 330 core

struct Material {
	vec3 albedo;
	float metallic;
	float roughness;
};

uniform Material uMaterial;

layout(std140) uniform CameraBuffer {
	vec3 uPos;
	mat4 uV;
	mat4 uP;
	mat4 uVP;
};

layout(std140) uniform LightsBuffer {
	struct Light {
		vec3 pos;
		vec3 color;
	} lights[64];
	int lightCount;
};

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

void main()
{
	const float lightRadius = 40.0;
	vec3 N = normalize(Normal);
	vec3 V = normalize(uPos - FragPos);

	vec3 finalColor = 0.1 * uMaterial.albedo;

	for (int i = 0; i < lightCount; ++i) {
		vec3 L = normalize(lights[i].pos - FragPos);
		vec3 H = normalize(L + V);

		float diff = max(dot(N, L), 0.0);
		vec3 diffuse = diff * uMaterial.albedo;

		float spec = pow(max(dot(N, H), 0.0), 32.0 * (1.0 - uMaterial.roughness));
		vec3 specular = spec * mix(vec3(0.04), lights[i].color, uMaterial.metallic);

		float distanceToLight = length(lights[i].pos - FragPos);
		float attenuation = 1.0 - smoothstep(0.0, lightRadius, distanceToLight);
		finalColor += (diffuse + specular) * attenuation;
	}

	FragColor = vec4(finalColor, 1.0);
}
