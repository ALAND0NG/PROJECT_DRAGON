#include <Header/Texture.h>

void Texture::LoadDiffuseFromFile(std::string path)
{
	m_DiffuseMap_DATA = Texture2DData::LoadFromFile(path);
	m_Diffuse = Texture2D::Create();
	m_Diffuse->LoadData(m_DiffuseMap_DATA);
}

void Texture::LoadSpecularFromFile(std::string path)
{
	m_SpecularMap_DATA = Texture2DData::LoadFromFile(path);
	m_Specular = Texture2D::Create();
	m_Specular->LoadData(m_SpecularMap_DATA);
}
