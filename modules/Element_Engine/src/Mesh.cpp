#include "Mesh.h"

void Mesh::TestLoadFromFile()
{
	m_vao = NotObjLoader::LoadFromFile("Models/Sample.notobj");
}

void Mesh::LoadOBJ(std::string filename, glm::vec4 col)
{
	m_vao = OBJLoader::LoadFromFile(filename, col);  
	
}

VertexArrayObject::sptr Mesh::GetVAO()
{
	return m_vao;
}




