#pragma once

#include <Header/Texture2DData.h>
#include <Header/Texture2D.h>

class Texture //ECS component for Textures wraps around the Texture2D class
{
public:

	
	
	void LoadDiffuseFromFile(std::string path);
	void LoadSpecularFromFile(std::string path);


	Texture2D::sptr GetDiffuse()
	{
		return m_Diffuse;
	}

	Texture2D::sptr GetSpec()
	{
		return m_Specular;
	}

private:
	
	Texture2DData::sptr m_DiffuseMap_DATA;
	Texture2DData::sptr m_SpecularMap_DATA;
	Texture2D::sptr m_Diffuse;
	Texture2D::sptr m_Specular;

};