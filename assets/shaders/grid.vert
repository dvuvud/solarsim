#version 330 core

layout(location = 0) in vec3 aPos;

layout(std140) uniform CameraBuffer {
	vec3 uPos; float pad0;
	mat4 uV;
	mat4 uP;
	mat4 uVP;
};

layout(std140) uniform RigidbodyBuffer {
	struct RB {
		vec4 mPos;
	} RBs[64];
	int count;
};

out vec3 WorldPos;

void main()
{
	const float INTENSITY = 0.025;
	const float SMOOTHING = 0.1;
	const float FALLOFF = 0.01;

	vec3 warpedPos = aPos;

	for(int i = 0; i < count; ++i) {
		vec3 toEntity = RBs[i].mPos.xyz - aPos;
		float dis = length(toEntity);
		float smoothedDis = dis + SMOOTHING;

		float gravityEffect = -RBs[i].mPos.w * exp(-smoothedDis * FALLOFF);
		warpedPos.y += gravityEffect * INTENSITY;
	}

	WorldPos = warpedPos;
	gl_Position = uVP * vec4(warpedPos, 1.0);
}
