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

uniform vec3 uLightPos;
uniform vec3 uLightColor;

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

void main()
{
	vec3 N = normalize(Normal);
	vec3 L = normalize(uLightPos - FragPos);
	vec3 V = normalize(uPos - FragPos);
	vec3 H = normalize(L + V);

	float diff = max(dot(N, L), 0.0);
	vec3 diffuse = diff * uMaterial.albedo;

	float spec = pow(max(dot(N, H), 0.0), 32.0 * (1.0 - uMaterial.roughness));
	vec3 specular = spec * mix(vec3(0.04), uLightColor, uMaterial.metallic);

	vec3 color = diffuse + specular;

	FragColor = vec4(color, 1.0);
}
