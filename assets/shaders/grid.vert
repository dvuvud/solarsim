#version 330 core

layout(location = 0) in vec3 aPos;

out vec3 WorldPos;

uniform vec4 uEntities[64]; // Limits the amount of entities that can have an effect
uniform int uEntityCount;
uniform mat4 uVP;

void main() {
	const float WARP_INTENSITY = 0.1;
	const float DISTANCE_SMOOTHING = 0.1;
	const float FALLOFF = 0.05;

	vec3 warpedPos = aPos;

	for(int i = 0; i < uEntityCount; ++i) {
		vec3 entityPos = uEntities[i].xyz;
		float mass = uEntities[i].w;

		vec3 toEntity = entityPos - aPos;
		float distance = length(toEntity);
		float smoothedDistance = distance + DISTANCE_SMOOTHING;

		float gravityEffect = -mass * exp(-smoothedDistance * FALLOFF);
		warpedPos.y += gravityEffect * WARP_INTENSITY;
	}

	WorldPos = warpedPos;
	gl_Position = uVP * vec4(warpedPos, 1.0);
}
