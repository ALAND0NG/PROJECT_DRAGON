#pragma once
#include "TextureCubeMap.h"
#include "Shader.h" //I want to attach the shader dirrectly to this component, since its basically a one off
//this serves more as a flag for our rendering system update
class Skybox
{
public:
	Shader::sptr skybox;

};