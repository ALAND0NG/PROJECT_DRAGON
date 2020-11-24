#pragma once
#include "MorphAnimator.h"
#include <OBJLoader.h>


class Blender
{
public:
	Blender()
	{
		m_vao = VertexArrayObject::Create();
	}

	//bad bad speedrun yeet
	void SendToVao();
	void LoadFrame(std::string filePath, glm::vec4 color)
	{
		m_AnimData.m_Frames.push_back(OBJLoader::LoadFrame(filePath, color));
	}
	void Update();

	void AddNewAnimation(int firstframe, int lastframe, float timeperframe)
	{
		Animation newAnimation;
		newAnimation.m_FirstFrame = firstframe;
		newAnimation.m_LastFrame = lastframe;
		newAnimation.m_TimeForFrame = timeperframe;

		newAnimation.m_CurrentFrame = firstframe;
		newAnimation.m_NextFrame = firstframe + 1;



		m_Animations.push_back(newAnimation);
	}

	VertexArrayObject::sptr m_vao;
	AData m_AnimData; //contains clip 1
	int Clip2ID;
	std::vector<Animation> m_Animations;

	float shaderBlend;
};