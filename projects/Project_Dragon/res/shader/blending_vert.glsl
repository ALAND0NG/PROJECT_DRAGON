#version 410

//Keyframe 1				//frame pos,col,normal,uv
layout(location = 0) in vec3 f1p1;
layout(location = 1) in vec3 f1c1;
layout(location = 2) in vec3 f1n1;
layout(location = 3) in vec2 f1u1;

//Keyframe 2
layout(location = 4) in vec3 f1p2;
layout(location = 5) in vec3 f1c2;
layout(location = 6) in vec3 f1n2;
//7 here as well

//Keyframe 3
layout(location = 8) in vec3 f2p1;
layout(location = 9) in vec3 f2c1;
layout(location = 10) in vec3 f2n1;
layout(location = 11) in vec2 f2u1;

//Keyframe 4
layout(location = 12) in vec3 f2p2;
layout(location = 13) in vec3 f2c2;
layout(location = 14) in vec3 f2n2;



//We only output the result from the lerp between frame 1 & 2
layout(location = 0) out vec3 outPos;
layout(location = 1) out vec3 outColor;
layout(location = 2) out vec3 outNormal;
layout(location = 3) out vec2 outUV;

uniform mat4 u_ModelViewProjection;
uniform mat4 u_View;
uniform mat4 u_Model;
//uniform mat3 u_ModelRotation;
uniform vec3 u_LightPos;

//for interpolation
uniform float t;
uniform float blend;

void main() 
{
	vec3 frame1posres;
	frame1posres = mix(f1p1,f1p2, t);

	vec3 frame1ColMix;
	frame1ColMix = mix(f1c1, f1c2, t);

	vec3 frame1normMix;
	frame1normMix = mix(f1n1, f1n2,t);

	vec3 frame2posres;
	frame1posres = mix(f2p1,f2p2, t);

	vec3 frame2ColMix;
	frame1ColMix = mix(f2c1, f2c2, t);

	vec3 frame2normMix;
	frame1normMix = mix(f2n1, f2n2,t);


	outPos = (u_Model * vec4(mix(frame1posres,frame2posres, blend),1.0)).xyz;
	outNormal = (u_Model * vec4(mix(frame1normMix, frame2normMix, blend),1)).xyz;
	outColor = f1c1;

	outUV = f1u1;

	gl_Position = u_ModelViewProjection * vec4(outPos,1.0);
	
}
