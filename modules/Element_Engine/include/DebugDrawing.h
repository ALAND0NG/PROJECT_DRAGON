
#pragma once
#include "Bullet/LinearMath/btIDebugDraw.h"
#include <glad/glad.h>
#include <GLM/glm.hpp>
#include <RenderingSystem.h>
//I very much stole this from stackoverflow/bullet form because I am lazy and not inteligent
//modified slightly to fit into this framework
//https://pybullet.org/Bullet/phpBB3/viewtopic.php?t=11517
class BulletDebugDrawer_OpenGL : public btIDebugDraw {
public:
	GLuint m_VBO, m_VAO;

	Shader::sptr lineShader;

	void Init()
	{
		lineShader = Shader::Create();
		lineShader->LoadShaderPartFromFile("shader/line_shader_vert.glsl", GL_VERTEX_SHADER);
		lineShader->LoadShaderPartFromFile("shader/line_shader_FRAG.glsl", GL_FRAGMENT_SHADER);
		lineShader->Link();
	}

	void SetMatrices(glm::mat4 pViewMatrix, glm::mat4 pProjectionMatrix)
	{
		lineShader->SetUniformMatrix("projection", pProjectionMatrix);
		lineShader->SetUniformMatrix("view", pViewMatrix);
	}

	virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
	{
		// Vertex data
		GLfloat points[12];

		points[0] = from.x();
		points[1] = from.y();
		points[2] = from.z();
		points[3] = color.x();
		points[4] = color.y();
		points[5] = color.z();

		points[6] = to.x();
		points[7] = to.y();
		points[8] = to.z();
		points[9] = color.x();
		points[10] = color.y();
		points[11] = color.z();

		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glBindVertexArray(0);

		glBindVertexArray(m_VAO);
		glDrawArrays(GL_LINES, 0, 2);
		glBindVertexArray(0);

	}
	virtual void drawContactPoint(const btVector3&, const btVector3&, btScalar, int, const btVector3&) {}
	virtual void reportErrorWarning(const char*) {}
	virtual void draw3dText(const btVector3&, const char*) {}
	virtual void setDebugMode(int p) {
		m = p;
	}
	int getDebugMode(void) const { return 3; }
	int m;
};
