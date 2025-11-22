#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

out vec3 FragPos;
out vec3 Normal;

void main()
{
	FragPos = vec3(uModel * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(uModel))) * aNormal; 
	gl_Position = uProj * uView * vec4(FragPos, 1.0);
}
