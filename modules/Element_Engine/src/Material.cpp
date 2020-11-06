#include "Material.h"

void Material::LoadDiffuseFromFile(std::string path)
{
	m_DiffuseMap_DATA = Texture2DData::LoadFromFile(path);
	m_Diffuse = Texture2D::Create();
	m_Diffuse->LoadData(m_DiffuseMap_DATA);
}

void Material::LoadSpecularFromFile(std::string path)
{
	m_SpecularMap_DATA = Texture2DData::LoadFromFile(path);
	m_Specular = Texture2D::Create();
	m_Specular->LoadData(m_SpecularMap_DATA);
}




Texture2D::sptr Material::GetAlbedo()
{
	return Albedo;
}

void Material::SetAlbedo(Texture2D::sptr albedo)
{
	Albedo = albedo;
}

Texture2D::sptr Material::GetSpecular()
{
	return Specular;
}

void Material::SetSpecular(Texture2D::sptr spec)
{
	Specular = spec;
}

float Material::GetShininess()
{
	return Shininess;
}

void Material::SetShininess(float shininess)
{
	Shininess = shininess;
}
