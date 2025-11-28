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
		vec4 pos;
		vec4 color;
	} lights[64];
	int lightCount;
};

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

void main()
{
	vec3 N = normalize(Normal);
	vec3 V = normalize(uPos - FragPos);

	vec3 finalColor = 0.03 * uMaterial.albedo;

	for (int i = 0; i < lightCount; ++i) {
		vec3 L = normalize(lights[i].pos.xyz - FragPos);

		float NdotL = max(dot(N, L), 0.0);
		vec3 diffuse = NdotL * lights[i].color.xyz * uMaterial.albedo;

		vec3 specular = vec3(0.0);
		if (NdotL > 0) {
			vec3 H = normalize(L + V);
			float spec = pow(max(dot(N, H), 0.0), 32.0 * (1.0 - uMaterial.roughness));
			specular = spec * mix(vec3(0.04), lights[i].color.xyz, uMaterial.metallic);
		}

		float distanceToLight = length(lights[i].pos.xyz - FragPos);
		float attenuation = 1.0 - smoothstep(0.0, lights[i].color.w, distanceToLight);
		finalColor += (diffuse + specular) * attenuation;
	}

	FragColor = vec4(finalColor, 1.0);
}
