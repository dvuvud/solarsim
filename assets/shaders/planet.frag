#version 330 core
in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 viewPos;

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

		float brightness = 1.0 - smoothstep(0.0, uLightRadii[i], distanceToLight);

		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * uLightColors[i] * brightness;

		float specularStrength = 0.5;
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
		vec3 specular = specularStrength * spec * uLightColors[i] * brightness;

		result += (diffuse * objectColor) + specular;
	}

	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * objectColor;

	result += ambient;

	FragColor = vec4(result, 1.0);
}
