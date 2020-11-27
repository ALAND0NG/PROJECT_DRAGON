#pragma once
#include <Mesh.h>
#include <Material.h>
static class AssetLoader
{
public:
	static void Init();
	static std::vector<Mesh>& GetMesh();
	static std::vector<Material>& GetMat();
	static Mesh& GetMeshFromStr(std::string name);
	static Material& GetMatFromStr(std::string name);

private:
	static std::vector<Mesh> m_Meshes;
	static std::vector<Material> m_Materials;
	static std::vector<std::string> m_MeshNames;
	static std::vector<std::string> m_MaterialNames;
};