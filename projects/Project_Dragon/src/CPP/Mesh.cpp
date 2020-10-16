#include "Header/Mesh.h"

void Mesh::TestLoadFromFile()
{
	m_vao = NotObjLoader::LoadFromFile("Models/Sample.notobj");
}

void Mesh::LoadOBJ(std::string filename)
{
	m_vao = OBJLoader::LoadFromFile(filename);
}

VertexArrayObject::sptr Mesh::GetVao()
{
	return m_vao;
}

glm::mat4 Mesh::GetTransform()
{
	return m_transform;
}
