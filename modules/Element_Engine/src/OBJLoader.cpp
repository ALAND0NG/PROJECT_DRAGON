#include "OBJLoader.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <GLM/glm.hpp>
#include <VertexTypes.h>
#include <algorithm>

// Borrowed from https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
#pragma region String Trimming

// trim from start (in place)
static inline void ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
		}));
}

// trim from end (in place)
static inline void rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s) {
	ltrim(s);
	rtrim(s);
}

#pragma endregion 


VertexArrayObject::sptr OBJLoader::LoadFromFile(std::string filename, glm::vec4 col)
{

	std::vector<glm::vec3> vertex_position;

	std::vector<glm::vec2> vertex_texture;

	std::vector<glm::vec3> vertex_normal;

	// Array for F
	std::vector<GLint> Pos_Ind;
	std::vector<GLint> Tex_Ind;
	std::vector<GLint> Norm_Ind;

	//std::vector<float> vertices;
	std::stringstream ss;			//http://www.cplusplus.com/reference/sstream/stringstream/
	glm::vec3 tempVec3;
	glm::vec2 tempVec2;

	int tempInt;

	// Open our file in binary mode
	std::ifstream file;
	file.open(filename, std::ios::binary);

	// If our file fails to open, we will throw an error
	if (!file) {
		throw std::runtime_error("Failed to open file");
	}

	MeshBuilder<VertexPosNormTexCol> mesh;
	std::string line = "";
	std::string prefix = "";

	// Iterate as long as there is content to read
	while (std::getline(file, line))
	{
		trim(line);
		ss = std::stringstream(line);
		ss >> prefix;

		if (prefix == "#")
		{
			// Comment, no-op
		}
		else if (prefix == "o")
		{
			// Comment, no-op
		}
		else if (prefix == "v") //vertex pos.
		{
			ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
			vertex_position.push_back(tempVec3);
		}
		else if (prefix == "vt")
		{
			ss >> tempVec2.x >> tempVec2.y;
			vertex_texture.push_back(tempVec2);
		}
		else if (prefix == "vn")
		{
			ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
			vertex_normal.push_back(tempVec3);
		}
		else if (prefix == "f")
		{
			int counter = 0;
			while (ss >> tempInt)
			{
				if (counter == 0)
				{
					Pos_Ind.push_back(tempInt);
				}
				if (counter == 1)
				{
					Tex_Ind.push_back(tempInt);
				}
				if (counter == 2)
				{
					Norm_Ind.push_back(tempInt);
				}

				if (ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					++counter;
					ss.ignore(1, ' ');
				}
				if (counter > 2)
				{
					counter = 0;
				}

			}
		}
	}
	for (unsigned int i = 0; i < Pos_Ind.size(); i++)
	{
		//glm::vec4 col(0.5f, 1.f, 1.f, 1.f);
		mesh.AddVertex(vertex_position[Pos_Ind[i] - 1], vertex_normal[Norm_Ind[i] - 1], vertex_texture[Tex_Ind[i] - 1], col);
	}

	return mesh.Bake();
	



}

Frame OBJLoader::LoadFrame(std::string filename, glm::vec4 col)
{
	std::vector<glm::vec3> vertex_position;

	std::vector<glm::vec2> vertex_texture;

	std::vector<glm::vec3> vertex_normal;

	// Array for F
	std::vector<GLint> Pos_Ind;
	std::vector<GLint> Tex_Ind;
	std::vector<GLint> Norm_Ind;

	//std::vector<float> vertices;
	std::stringstream ss;			//http://www.cplusplus.com/reference/sstream/stringstream/
	glm::vec3 tempVec3;
	glm::vec2 tempVec2;

	int tempInt;

	// Open our file in binary mode
	std::ifstream file;
	file.open(filename, std::ios::binary);

	// If our file fails to open, we will throw an error
	if (!file) {
		throw std::runtime_error("Failed to open file");
	}

	std::string line = "";
	std::string prefix = "";

	Frame frame;

	// Iterate as long as there is content to read
	while (std::getline(file, line))
	{
		trim(line);
		ss = std::stringstream(line);
		ss >> prefix;

		if (prefix == "#")
		{
			// Comment, no-op
		}
		else if (prefix == "o")
		{
			// Comment, no-op
		}
		else if (prefix == "v") //vertex pos.
		{
			ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
			vertex_position.push_back(tempVec3);
		}
		else if (prefix == "vt")
		{
			ss >> tempVec2.x >> tempVec2.y;
			vertex_texture.push_back(tempVec2);
		}
		else if (prefix == "vn")
		{
			ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
			vertex_normal.push_back(tempVec3);
		}
		else if (prefix == "f")
		{
			int counter = 0;
			while (ss >> tempInt)
			{
				if (counter == 0)
				{
					Pos_Ind.push_back(tempInt);
				}
				if (counter == 1)
				{
					Tex_Ind.push_back(tempInt);
				}
				if (counter == 2)
				{
					Norm_Ind.push_back(tempInt);
				}

				if (ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					++counter;
					ss.ignore(1, ' ');
				}
				if (counter > 2)
				{
					counter = 0;
				}

			}
		}
	}
	
	const int possize = Pos_Ind.size() * 3; //since we are loading vec3, we need 3x for floats
	const int colSize = Pos_Ind.size() * 4;;
	const int normsize = possize;
	const int uvsize = Tex_Ind.size() * 2;
	
	//this actually hurts
	//vbo needs a float array, managing an array is more annoying than a vector
	//im lazy so I am adding to a vector then pushing to an array which is more work
	//but im also dumb and this is easier
	float** posarr = new float* [possize];
	std::vector<float> positions;

	float** colarr = new float* [colSize];
	std::vector<float> colors;

	float** normarr = new float* [normsize];
	std::vector<float> normals;

	float** uvarr = new float* [uvsize];
	std::vector<float> uvs;
	
	//writes all data loaded from our obj into vectors
	for (int i = 0; i < Pos_Ind.size(); i++)
	{
		positions.push_back(vertex_position[Pos_Ind[i] - 1].x);
	
		positions.push_back(vertex_position[Pos_Ind[i] - 1].y);
			
		positions.push_back(vertex_position[Pos_Ind[i] - 1].z);

	}
	for (int i = 0; i < Pos_Ind.size(); i++)
	{
		colors.push_back(col.x);
		colors.push_back(col.y);
		colors.push_back(col.z);
		colors.push_back(col.a);
	}
	for (int i = 0; i < Norm_Ind.size(); i++)
	{
		normals.push_back(vertex_normal[Norm_Ind[i] - 1].x);
		normals.push_back(vertex_normal[Norm_Ind[i] - 1].y);
		normals.push_back(vertex_normal[Norm_Ind[i] - 1].z);
	}
	for (int i = 0; i < Tex_Ind.size(); i++)
	{
		uvs.push_back(vertex_texture[Tex_Ind[i] - 1].x);
		uvs.push_back(vertex_texture[Tex_Ind[i] - 1].y);
	}
	//takes vectors and writes them into arrays before we can pass them into a VBO
	for (int i = 0; i < positions.size(); i++)
	{
		posarr[i] = &positions[i];//:)
	}
	for (int i = 0; i < colors.size(); i++)
	{
		colarr[i] = &colors[i];
	}
	for (int i = 0; i < normals.size(); i++)
	{
		normarr[i] = &normals[i];
	}
	for (int i = 0; i < uvs.size(); i++)
	{
		uvarr[i] = &uvs[i];
	}

	frame.m_Pos = VertexBuffer::Create();
	frame.m_Col = VertexBuffer::Create();
	frame.m_Normal = VertexBuffer::Create();
	frame.m_UV = VertexBuffer::Create();

	//loads our arrays into data for a frame
	frame.m_Pos->LoadData(posarr,sizeof(posarr), possize);
	frame.m_Col->LoadData(colarr, sizeof(colarr), colSize);
	frame.m_Normal->LoadData(normarr,sizeof(normarr), normsize);
	frame.m_UV->LoadData(uvarr, sizeof(uvarr),uvsize);

	return frame;
	
}
