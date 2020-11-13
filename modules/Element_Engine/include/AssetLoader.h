#pragma once
#include <Mesh.h>
#include <Material.h>
static class AssetLoader
{
public:
	static std::vector<Mesh>& GetMesh();
	static std::vector<Material>& GetMat();
private:
	static std::vector<Mesh> m_Meshes; //k basically just fucking memorize it im not making a full system to track this shit
	static std::vector<Material> m_Materials;
};