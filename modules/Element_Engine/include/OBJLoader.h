#pragma once

#include <MeshBuilder.h>
#include <GLM/glm.hpp>

class OBJLoader
{
public:
	static VertexArrayObject::sptr LoadFromFile(std::string filename, glm::vec4 col);
private:
	OBJLoader() = default;
	~OBJLoader() = default;
};