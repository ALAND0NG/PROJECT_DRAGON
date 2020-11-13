#include <AssetLoader.h>
std::vector<Mesh> AssetLoader::m_Meshes;
std::vector<Material> AssetLoader::m_Materials;

std::vector<Mesh>& AssetLoader::GetMesh()
{
	return m_Meshes;
}

std::vector<Material>& AssetLoader::GetMat()
{
	return m_Materials;
	// TODO: insert return statement here
}
