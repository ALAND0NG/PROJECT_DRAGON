#pragma once

#include <Header/MeshBuilder.h>


class OBJLoader
{
public:
	static VertexArrayObject::sptr LoadFromFile(std::string filename);
private:
	OBJLoader() = default;
	~OBJLoader() = default;
};