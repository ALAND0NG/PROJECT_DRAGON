#version 410

layout(location = 0) in vec3 inPosition;
layout(location = 0) out vec3 outNormal;

uniform mat4 u_SkyboxMatrix;

void main()
{

	vec4 pos = u_SkyboxMatrix * vec4(inPosition, 1.0);
	gl_Position = pos.xyww;

	//normals
	outNormal = vec3(1);
}