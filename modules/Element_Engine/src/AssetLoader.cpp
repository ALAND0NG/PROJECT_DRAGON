#include <AssetLoader.h>
std::vector<Mesh> AssetLoader::m_Meshes;
std::vector<Material> AssetLoader::m_Materials;
std::vector<std::string> AssetLoader::m_MaterialNames;
std::vector<std::string> AssetLoader::m_MeshNames;
std::vector<MorphAnimator> AssetLoader::m_AnimatedModels;

void AssetLoader::Init() //doing it manually because, actually I don't know why
{
	
	Mesh pfb0;
	pfb0.LoadOBJ("models/Straight_Nodes/StraightTrack.obj", glm::vec4(1, 1, 1, 1));
	AssetLoader::GetMesh().push_back(pfb0);
	AssetLoader::m_MeshNames.push_back("StraightTrack");

	Mesh pfb1;
	pfb1.LoadOBJ("models/other/SideTrack.obj", glm::vec4(1, 1, 1, 1));
	AssetLoader::GetMesh().push_back(pfb1);
	AssetLoader::m_MeshNames.push_back("SideTrack");

	Mesh pfb2; //
	pfb2.LoadOBJ("models/RightTurn_Nodes/RightTurn.obj", glm::vec4(1, 1, 1, 1));
	AssetLoader::GetMesh().push_back(pfb2);
	AssetLoader::m_MeshNames.push_back("RightTurn");

	Mesh pfb3;
	pfb3.LoadOBJ("models/RightOff_Nodes/RightOff.obj", glm::vec4(1, 1, 1, 1));
	AssetLoader::GetMesh().push_back(pfb3);
	AssetLoader::m_MeshNames.push_back("RightOff");

	Mesh pfb4;
	pfb4.LoadOBJ("models/LeftTurn_Nodes/LeftTurn.obj", glm::vec4(1, 1, 1, 1));
	AssetLoader::GetMesh().push_back(pfb4);
	AssetLoader::m_MeshNames.push_back("LeftTurn");

	Mesh pfb5;
	pfb5.LoadOBJ("models/LeftOff_Nodes/LeftOff.obj", glm::vec4(1, 1, 1, 1));
	AssetLoader::GetMesh().push_back(pfb5);
	AssetLoader::m_MeshNames.push_back("LeftOff");

	Material mat0;
	mat0.LoadDiffuseFromFile("images/STR_HW_T.png");
	mat0.LoadSpecularFromFile("images/Stone_001_Specular.png");
	mat0.SetAll(1.f);
	AssetLoader::GetMat().push_back(mat0);
	AssetLoader::m_MaterialNames.push_back("StraightPathTexture");

	Material mat1;
	mat1.LoadDiffuseFromFile("images/FE_TEXTURE.png");
	mat1.LoadSpecularFromFile("images/Stone_001_Specular.png");
	mat1.SetAll(1);
	AssetLoader::GetMat().push_back(mat1);
	AssetLoader::m_MaterialNames.push_back("FireEnemyTex");

	MorphAnimator mrph1;
	for (int i = 1; i <= 2; i++)
	{
		std::string fileName = "models/animations/FIRE_ENEMY/FW_W_";
		mrph1.LoadFrame(fileName + std::to_string(i) + ".obj", glm::vec4(1, 1, 1, 1));
	}
	mrph1.AddNewAnimation(0, 1, 2);
	mrph1.SetActiveAnimation(0);
	m_AnimatedModels.push_back(mrph1);
	
}

std::vector<Mesh>& AssetLoader::GetMesh()
{
	return m_Meshes;
}

std::vector<Material>& AssetLoader::GetMat()
{
	return m_Materials;
	// TODO: insert return statement here
}

std::vector<MorphAnimator>& AssetLoader::GetMorph()
{
	return m_AnimatedModels;
}

Mesh& AssetLoader::GetMeshFromStr(std::string name)
{
	// TODO: insert return statement here
	for (int i = 0; i < m_Meshes.size(); i++)
	{
		if (name == m_MeshNames[i])
		{
			return m_Meshes[i];
		}
	}
	return m_Meshes[0];

}

Material& AssetLoader::GetMatFromStr(std::string name)
{
	// TODO: insert return statement here

	for (int i = 0; i < m_Materials.size(); i++)
	{
		if (name == m_MaterialNames[i])
		{
			return m_Materials[i];
		}
	}
	return m_Materials[0];
}
