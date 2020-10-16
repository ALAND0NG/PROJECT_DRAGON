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

	VertexArrayObject::sptr GetVao();
	glm::mat4 GetTransform();
private:
	VertexArrayObject::sptr m_vao = VertexArrayObject::Create();
	glm::mat4 m_transform = glm::mat4(1.0f);
};