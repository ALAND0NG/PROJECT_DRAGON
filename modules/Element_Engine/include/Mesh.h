#pragma once
//This is the ECS component that will handle meshes
//just cleaner than using the Meshbuilder/meshfactory
//Nowhere close to done
#include <MeshBuilder.h>
#include <MeshFactory.h>
#include <VertexArrayObject.h>
#include <NotObjLoader.h>
#include <OBJLoader.h>
#include <string>
class Mesh
{
public:
	void TestLoadFromFile();

	void LoadOBJ(std::string filename,glm::vec4 col);
	
	void SetVAO(VertexArrayObject::sptr vao)
	{
		m_vao = vao;
	}

	VertexArrayObject::sptr GetVAO();

private:
	VertexArrayObject::sptr m_vao = VertexArrayObject::Create();
};