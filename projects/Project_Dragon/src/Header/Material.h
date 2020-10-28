#pragma once
#include <Header/Texture2D.h>

//basic ECS component for Material

class Material
{
public:

	
	
	void SetAll(float shin)
	{
		Albedo = m_Diffuse;
		Albedo2 = m_Diff2;
		Specular = m_Specular;
		Shininess = shin;
	}


	void LoadDiffuseFromFile(std::string path);
	void LoadSpecularFromFile(std::string path);
	void LoadDiffuse2FromFile(std::string path);


	Texture2D::sptr GetAlbedo();
	Texture2D::sptr GetAlbedo2()
	{
		return Albedo2;
	}
	void SetAlbedo(Texture2D::sptr albedo);
	Texture2D::sptr GetSpecular();
	void SetSpecular(Texture2D::sptr spec);
	float GetShininess();
	void SetShininess(float shininess);

	float Tex1Str;
	float Tex2Str;


private:
	Texture2D::sptr Albedo;
	Texture2D::sptr Albedo2;
	Texture2D::sptr Specular;
	float           Shininess;


	Texture2DData::sptr m_DiffuseMap_DATA;
	Texture2DData::sptr m_SpecularMap_DATA;
	Texture2D::sptr m_Diffuse;
	Texture2D::sptr m_Specular;
	Texture2D::sptr m_Diff2;

};