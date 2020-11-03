#version 410

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inUV;

uniform sampler2D s_Diffuse;
uniform sampler2D s_Diffuse2;
uniform sampler2D s_Specular;

uniform float Tex1Str;
uniform float Tex2Str;

uniform vec3  u_AmbientCol;
uniform float u_AmbientStrength;

uniform vec3  u_LightCol;
uniform float u_AmbientLightStrength;
uniform float u_SpecularLightStrength;
uniform float u_Shininess;
// NEW in week 7, see https://learnopengl.com/Lighting/Light-casters for a good reference on how this all works, or
// https://developer.valvesoftware.com/wiki/Constant-Linear-Quadratic_Falloff
uniform float u_LightAttenuationConstant;
uniform float u_LightAttenuationLinear;
uniform float u_LightAttenuationQuadratic;

uniform vec3  u_CamPos;

uniform int u_LightCount;

//fuck it all the lights are the same just have seperate positions & also hard coded to have a max of 99 fuck you
uniform vec3 LightPositions[99];

out vec4 frag_color;





// https://learnopengl.com/Advanced-Lighting/Advanced-Lighting
void main() {
	// Lecture 5
	vec3 ambient = u_AmbientLightStrength * u_LightCol;

	vec3 result;

	float dist;

	float attenuation;

	vec3 viewDir;

	vec3 h;

	float texSpec;

	float spec;

	vec3 specular;

	vec4 textureColor1;

	vec4 textureColor2;

	vec4 textureColor;



	// Diffuse
	vec3 N = normalize(inNormal);
	vec3 lightDir[99];
	for (int i = 0; i<= u_LightCount; i++)
	{
	lightDir[i] = normalize(LightPositions[i] - inPos);
	

	float dif = max(dot(N, lightDir[i]), 0.0);
	vec3 diffuse = dif * u_LightCol;// add diffuse intensity

	//Attenuation
	dist = length(LightPositions[i] - inPos);
	attenuation = 1.0f / (
		u_LightAttenuationConstant + 
		u_LightAttenuationLinear * dist +
		u_LightAttenuationQuadratic * dist * dist);

	// Specular
	viewDir  = normalize(u_CamPos - inPos);
	h        = normalize(lightDir[i] + viewDir);
	

	// Get the specular power from the specular map
	texSpec = texture(s_Specular, inUV).x;
	spec = pow(max(dot(N, h), 0.0), u_Shininess); // Shininess coefficient (can be a uniform)
	specular = u_SpecularLightStrength * texSpec * spec * u_LightCol; // Can also use a specular color
	
	// Get the albedo from the diffuse / albedo map
	textureColor1 = texture(s_Diffuse, inUV) * Tex1Str;
	textureColor2 = texture(s_Diffuse2, inUV) * Tex2Str;
	textureColor = textureColor1 + textureColor2;

	result += (
		(u_AmbientCol * u_AmbientStrength) + // global ambient light
		(ambient + diffuse + specular) * attenuation // light factors from our single light
		) * inColor * textureColor.rgb; // Object color

	}
	frag_color = vec4(result, textureColor.a);
}
