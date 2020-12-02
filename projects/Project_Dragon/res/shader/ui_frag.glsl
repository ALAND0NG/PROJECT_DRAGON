#version 410

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inUV;
out vec3 color;

uniform sampler2D s_Specular;
uniform sampler2D s_Diffuse;
uniform vec3 spriteColor;

void main()
{    
    color = vec3(texture(s_Specular, inUV));
}