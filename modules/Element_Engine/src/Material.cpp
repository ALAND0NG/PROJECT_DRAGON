#include "Material.h"

void Material::LoadDiffuseFromFile(std::string path)
{
	m_DiffuseMap_DATA = Texture2DData::LoadFromFile(path);
	m_Diffuse = Texture2D::Create();
	m_Diffuse->LoadData(m_DiffuseMap_DATA);

	///////////////////////////
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//anisotropic

	float a = 0.f;
	glGetFloatv(GL_TEXTURE_MAX_ANISOTROPY, &a);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, 16.f);
}

void Material::LoadSpecularFromFile(std::string path)
{
	m_SpecularMap_DATA = Texture2DData::LoadFromFile(path);
	m_Specular = Texture2D::Create();
	m_Specular->LoadData(m_SpecularMap_DATA);

	///////////////////////////
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//anisotropic

	float a = 0.f;
	glGetFloatv(GL_TEXTURE_MAX_ANISOTROPY, &a);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, 16.f);
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
