#include <MorphAnimator.h>
#include <OBJLoader.h>
AData MorphAnimator::GetAnimData()
{
	return m_AnimData;
}

void MorphAnimator::LoadFrame(std::string filePath, glm::vec4 color)
{
	m_AnimData.m_Frames.push_back(OBJLoader::LoadFrame(filePath, color));
}

void MorphAnimator::SendToVao()
{
	m_vao = VertexArrayObject::Create();

	uint32_t slot = 0;
	m_vao->AddVertexBuffer(m_AnimData.m_Frames[0].m_Pos, { BufferAttribute(slot, 3,
		GL_FLOAT, false, GLsizei(0),size_t(0)) });
	
	slot = 1;
	m_vao->AddVertexBuffer(m_AnimData.m_Frames[0].m_Col, { BufferAttribute(slot, 3,
	GL_FLOAT, false, GLsizei(0),size_t(0)) });

	slot = 2;
	m_vao->AddVertexBuffer(m_AnimData.m_Frames[0].m_Normal, { BufferAttribute(slot, 3,
	GL_FLOAT, false, GLsizei(0),size_t(0)) });

	slot = 3;
	m_vao->AddVertexBuffer(m_AnimData.m_Frames[0].m_UV, { BufferAttribute(slot, 2,
	GL_FLOAT, false, GLsizei(0),size_t(0)) });
	
	slot = 4;
	m_vao->AddVertexBuffer(m_AnimData.m_Frames[1].m_Pos, { BufferAttribute(slot, 3,
		GL_FLOAT, false, GLsizei(0),size_t(0)) });

	slot = 5;
	m_vao->AddVertexBuffer(m_AnimData.m_Frames[1].m_Col, { BufferAttribute(slot, 3,
	GL_FLOAT, false, GLsizei(0),size_t(0)) });

	slot = 6;
	m_vao->AddVertexBuffer(m_AnimData.m_Frames[1].m_Normal, { BufferAttribute(slot,  3,
	GL_FLOAT, false, GLsizei(0),size_t(0)) });

	slot = 7;
	m_vao->AddVertexBuffer(m_AnimData.m_Frames[1].m_UV, { BufferAttribute(slot, 2,
	GL_FLOAT, false, GLsizei(0),size_t(0)) });

}

void MorphAnimator::Update()
{
}

void MorphAnimator::SetVAO(VertexArrayObject::sptr vao)
{
	m_vao = vao;
}

VertexArrayObject::sptr MorphAnimator::GetVAO()
{
	return m_vao;
}

void MorphAnimator::SetT(float newt)
{
	m_AnimData.t = newt;
}