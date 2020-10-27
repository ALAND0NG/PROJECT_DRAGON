#include "Header/Material.h"

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
