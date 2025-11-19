#version 330 core
in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material uMaterial;

uniform vec3 uLightPositions[16];
uniform vec3 uLightColors[16];
uniform float uLightRadii[16];
uniform int uLightCount;

out vec4 FragColor;

void main()
{
	vec3 result = vec3(0.0);
	vec3 norm = normalize(Normal);
	for (int i = 0; i < uLightCount; ++i) {
		vec3 lightDir = uLightPositions[i] - FragPos;
		float distanceToLight = length(lightDir);
		lightDir = normalize(lightDir);

		vec3 ambient = uLightColors[i] * uMaterial.ambient;

		float brightness = 1.0 - smoothstep(0.0, uLightRadii[i], distanceToLight);

		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * uLightColors[i] * uMaterial.diffuse * brightness;

		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
		vec3 specular = uMaterial.specular * spec * uLightColors[i] * brightness;

		result += diffuse + specular + ambient;
	}

	FragColor = vec4(result, 1.0);
}
