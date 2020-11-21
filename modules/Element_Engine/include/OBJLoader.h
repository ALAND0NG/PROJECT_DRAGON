#pragma once

#include <MeshBuilder.h>
#include <GLM/glm.hpp>
#include <MorphAnimator.h>
class OBJLoader
{
public:
	static VertexArrayObject::sptr LoadFromFile(std::string filename, glm::vec4 col);
	static Frame LoadFrame(std::string filename, glm::vec4 );
private:
	OBJLoader() = default;
	~OBJLoader() = default;
};