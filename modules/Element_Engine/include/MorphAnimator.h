#pragma once
//This is the ECS component that will handle animations, get updated through the AnimationSystem class
#include <VertexArrayObject.h>
#include <GLM/glm.hpp>
struct Frame
{
	VertexBuffer::sptr m_Pos;
	VertexBuffer::sptr m_Col;
	VertexBuffer::sptr m_Normal;
	VertexBuffer::sptr m_UV;
};

struct AData//animation data
{
	std::vector<Frame> m_Frames;//contains position,color,normal & uv. This class basically just exists to organize that and
	//send it to the shader to be LERP
	float t = 1.f;//passed into the shader
	float m_FrameDuration;//all frames have the same length
	std::vector<int> m_Index;//just in case you want to index one of many vectors
	int m_StartAt = 0;//first frame

};
//this is an object that has all the animation data
//anything that has to be animated will have this component
class MorphAnimator
{
public:
	
	MorphAnimator() //constructor
	{
		m_vao = VertexArrayObject::Create();
	}
	AData GetAnimData();
	//adds a frame to the animation
	void LoadFrame(std::string filePath, glm::vec4 color);

	void SetT(float newt);

	//Sends all the data to the vao
	void SendToVao();

	//this will update t, doesn't do the drawing
	void Update();

	void SetVAO(VertexArrayObject::sptr vao);
	VertexArrayObject::sptr GetVAO();

private:
	AData m_AnimData;
	VertexArrayObject::sptr m_vao;
};

