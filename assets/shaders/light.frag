#version 330

out vec4 FragColor;

struct Material {
	vec3 albedo;
	float metallic;
	float roughness;
};

uniform Material uMaterial;

void main() {
	FragColor = vec4(uMaterial.albedo, 1.0);
}
