#pragma once
#include <Header/Texture2D.h>

//basic ECS component for Material

class Material
{
public:

	void SetAll(Texture2D::sptr alb, Texture2D::sptr spec, float shin)
	{
		Albedo = alb;
		Specular = spec;
		Shininess = shin;
	}

	Texture2D::sptr GetAlbedo();
	void SetAlbedo(Texture2D::sptr albedo);
	Texture2D::sptr GetSpecular();
	void SetSpecular(Texture2D::sptr spec);
	float GetShininess();
	void SetShininess(float shininess);



private:
	Texture2D::sptr Albedo;
	Texture2D::sptr Specular;
	float           Shininess;
};