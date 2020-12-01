#version 410 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inUV;

out vec2 TexCoords;

uniform mat4 MVP;

void main()
{
    TexCoords = inUV;
    gl_Position = MVP * vec4(inPos, 1);
}