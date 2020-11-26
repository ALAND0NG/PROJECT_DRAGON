#include "AnimationBlender.h"
#include <Timer.h>
#include <iostream>
void Blender::SendToVao()
{

	//Get our indexes from our animation Data
	int F1 = m_Animations[m_AnimData.m_ActiveAnimation].m_CurrentFrame;
	int F2 = m_Animations[m_AnimData.m_ActiveAnimation].m_NextFrame;
	int F3 = m_Animations[Clip2ID].m_CurrentFrame;
	int F4 = m_Animations[Clip2ID].m_NextFrame;

	uint32_t slot = 0;
	m_vao->AddVertexBuffer(m_AnimData.m_Frames[F1].m_Pos, { BufferAttribute(slot, 3,
	GL_FLOAT, false, NULL,NULL) });

	slot = 1;
	m_vao->AddVertexBuffer(m_AnimData.m_Frames[F1].m_Col, { BufferAttribute(slot, 3,
	GL_FLOAT, false, NULL,NULL) });

	slot = 2;
	m_vao->AddVertexBuffer(m_AnimData.m_Frames[F1].m_Normal, { BufferAttribute(slot, 3,
	GL_FLOAT, false, NULL,NULL) });

	slot = 3;
	m_vao->AddVertexBuffer(m_AnimData.m_Frames[F1].m_UV, { BufferAttribute(slot, 2,
	GL_FLOAT, false, NULL,NULL) });

	slot = 4;
	m_vao->AddVertexBuffer(m_AnimData.m_Frames[F2].m_Pos, { BufferAttribute(slot, 3,
	GL_FLOAT, false, NULL,NULL) });

	slot = 5;
	m_vao->AddVertexBuffer(m_AnimData.m_Frames[F2].m_Col, { BufferAttribute(slot, 3,
	GL_FLOAT, false,NULL,NULL) });

	slot = 6;
	m_vao->AddVertexBuffer(m_AnimData.m_Frames[F2].m_Normal, { BufferAttribute(slot,  3,
	GL_FLOAT, false, NULL,NULL) });

	slot = 8;
	m_vao->AddVertexBuffer(m_AnimData.m_Frames[F3].m_Pos, { BufferAttribute(slot, 3,
	GL_FLOAT, false, NULL,NULL) });

	slot = 9;
	m_vao->AddVertexBuffer(m_AnimData.m_Frames[F3].m_Col, { BufferAttribute(slot, 3,
	GL_FLOAT, false,NULL,NULL) });

	slot = 10;
	m_vao->AddVertexBuffer(m_AnimData.m_Frames[F3].m_Normal, { BufferAttribute(slot,  3,
	GL_FLOAT, false, NULL,NULL) });

	slot = 12;
	m_vao->AddVertexBuffer(m_AnimData.m_Frames[F4].m_Pos, { BufferAttribute(slot, 3,
	GL_FLOAT, false, NULL,NULL) });

	slot = 13;
	m_vao->AddVertexBuffer(m_AnimData.m_Frames[F4].m_Col, { BufferAttribute(slot, 3,
	GL_FLOAT, false,NULL,NULL) });

	slot = 14;
	m_vao->AddVertexBuffer(m_AnimData.m_Frames[F4].m_Normal, { BufferAttribute(slot,  3,
	GL_FLOAT, false, NULL,NULL) });



}

void Blender::Update()
{
	m_AnimData.t += Timer::dt * m_Animations[m_AnimData.m_ActiveAnimation].m_TimeForFrame;


	if (m_AnimData.t >= 1.f)
	{
		m_Animations[m_AnimData.m_ActiveAnimation].m_ShouldSwitchFrames = true; //for the vao update


		//updates our frames

		int newCurFrame = m_Animations[m_AnimData.m_ActiveAnimation].m_NextFrame;
		int newNextFrame = m_Animations[m_AnimData.m_ActiveAnimation].m_NextFrame + 1;
		if (newNextFrame > m_Animations[m_AnimData.m_ActiveAnimation].m_LastFrame)
		{
			newNextFrame = m_Animations[m_AnimData.m_ActiveAnimation].m_FirstFrame;
		}
		if (newCurFrame > m_Animations[m_AnimData.m_ActiveAnimation].m_LastFrame)
			newCurFrame = m_Animations[m_AnimData.m_ActiveAnimation].m_FirstFrame;

		m_Animations[m_AnimData.m_ActiveAnimation].m_CurrentFrame = newCurFrame;
		m_Animations[m_AnimData.m_ActiveAnimation].m_NextFrame = newNextFrame;

		//resets timers
		m_AnimData.t = 0.f;
		m_Animations[m_AnimData.m_ActiveAnimation].m_Timer = 0.f;

		std::cout << "Switched Frames to: " << m_Animations[m_AnimData.m_ActiveAnimation].m_CurrentFrame << "&" << m_Animations[m_AnimData.m_ActiveAnimation].m_NextFrame
			<< std::endl;

		m_Animations[m_AnimData.m_ActiveAnimation].m_ShouldSwitchFrames = true; //for the vao update


		//updates our frames

		 newCurFrame = m_Animations[Clip2ID].m_NextFrame;
		 newNextFrame = m_Animations[Clip2ID].m_NextFrame + 1;
		if (newNextFrame > m_Animations[Clip2ID].m_LastFrame)
		{
			newNextFrame = m_Animations[Clip2ID].m_FirstFrame;
		}
		if (newCurFrame > m_Animations[Clip2ID].m_LastFrame)
			newCurFrame = m_Animations[Clip2ID].m_FirstFrame;

		m_Animations[Clip2ID].m_CurrentFrame = newCurFrame;
		m_Animations[Clip2ID].m_NextFrame = newNextFrame;

		m_Animations[Clip2ID].m_Timer = 0.f;
	}
}
