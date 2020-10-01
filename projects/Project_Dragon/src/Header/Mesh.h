/*
#include "ECS.h"
#include "BackEnd.h"
#include "GLM/glm.hpp"
#include "VertexBuffer.h"
#include "VertexArrayObject.h"
#include "Shader.h"
#include "IBuffer.h"
#include "IndexBuffer.h"

#include <string>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class Mesh
{
public:
	Mesh();
	~Mesh();

	bool LoadFromFile(const std::string& file);

	void Unload();

	unsigned int GetNumFaces() const;
	unsigned int GetNumVertices() const;

	//Opengl buffers & objects
	VertexBuffer* VBO_Vertices = new VertexBuffer();
	VertexBuffer* VBO_UV = new VertexBuffer();
	VertexBuffer* VBO_NORMALS = new VertexBuffer();
	VertexArrayObject* VAO = new VertexArrayObject();

private:
};
*/