//This is the ECS component that will handle meshes
//just cleaner than using the Meshbuilder/meshfactory
//Nowhere close to done
#include <Header/MeshBuilder.h>
#include <Header/MeshFactory.h>
#include <Header/VertexArrayObject.h>
#include <Header/NotObjLoader.h>
#include <Header/OBJLoader.h>
#include <string>
class Mesh
{
public:
	void TestLoadFromFile();

	void LoadOBJ(std::string filename);

	void SetRotation(glm::vec3 axis, float amount)
	{
		m_transform = glm::rotate(m_transform, amount, axis);
	}

	void SetPos(glm::vec3 pos)
	{
		m_transform = glm::translate(m_transform, pos);
	}
	
	void SetVAO(VertexArrayObject::sptr vao)
	{
		m_vao = vao;
	}

	VertexArrayObject::sptr GetVao();
	glm::mat4 GetTransform()
	{
		return m_transform;
	}
private:
	VertexArrayObject::sptr m_vao = VertexArrayObject::Create();
	glm::mat4 m_transform = glm::mat4(1.0f);
};