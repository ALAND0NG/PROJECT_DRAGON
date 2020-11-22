#include "MakePrefabHere_smile.h"
#include <bullet/btBulletDynamicsCommon.h>
#include <AssetLoader.h>

void PrefabMakeScene::InitScene()
{
	//Player Camera - - - Need This For A Game To Run
	m_sceneReg = new entt::registry;
	ECS::AttachRegistry(m_sceneReg);


	ECS::Create(0); //please please please always have camera be entity 0 it will break otherwise
	ECS::Add<Transform>(0);
	ECS::Add<PhysicsBody>(0);
	ECS::Add<Camera>(0);
	ECS::Get<Camera>(0).ResizeWindow(1920, 1080);
	ECS::Get<PhysicsBody>(0).AddBody(15, btVector3(3, 100, 3), btVector3(1, 2, 1));
	ECS::Add<LightSource>(0);
	ECS::Get<PhysicsBody>(0).m_Entity = 0;

	//plane so camera doesn't fall

	ECS::Create(1);
	ECS::Add<Mesh>(1);
	ECS::Add<Material>(1);
	ECS::Add<Transform>(1);
	ECS::Add<PhysicsBody>(1);
	ECS::Add<LightSource>(1);
	ECS::Get<Mesh>(1).LoadOBJ("models/plane.obj", glm::vec4(1, 1, 1, 1));
	ECS::Get<Transform>(1).SetScale(glm::vec3(10000.f, 1.f, 10000.f));
	ECS::Get<Material>(1).LoadDiffuseFromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(1).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(1).SetAll(1.f);
	ECS::Get<PhysicsBody>(1).AddBody(0.f, btVector3(0, 0, 0), btVector3(10000, 0, 100000));
	ECS::Get<PhysicsBody>(1).m_Entity = 1;

	//Enemy for animation test
	ECS::Create(2);
//	ECS::Add<Mesh>(2);
	ECS::Add<MorphAnimator>(2);
	ECS::Add<Material>(2);
	ECS::Add<Transform>(2);
	ECS::Get<Transform>(2).SetPosition(glm::vec3(1, 3, 1));
	ECS::Get<Transform>(2).SetScale(glm::vec3(5, 5, 5));
//	ECS::Get<Mesh>(2).LoadOBJ("models/anotherOne1.obj", glm::vec4(1, 1, 1, 1));
	ECS::Get<MorphAnimator>(2).LoadFrame("models/animations/FIRE_ENEMY/FE_WALK_1.obj", glm::vec4(1, 1, 1, 1));
	ECS::Get<MorphAnimator>(2).LoadFrame("models/animations/FIRE_ENEMY/FE_WALK_2.obj", glm::vec4(1, 1, 1, 1));
	ECS::Get<MorphAnimator>(2).AddNewAnimation(0,1,1,2);
	ECS::Get<MorphAnimator>(2).SetActiveAnimation(0);
	ECS::Get<Material>(2).LoadDiffuseFromFile("images/FE_TEXTURE.png");
	ECS::Get<Material>(2).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(2).SetAll(1.f);



#pragma region asset_loading
	/*
	For now I am not using prefabs/proper model loading, I am just trying to get something up and running
	Mesh pfb0;
	pfb0.LoadOBJ("models/StraightTrack.obj", glm::vec4(1, 1, 1, 1));
	AssetLoader::GetMesh().push_back(pfb0);

	Mesh pfb1;
	pfb1.LoadOBJ("models/SideTrack.obj", glm::vec4(1, 1, 1, 1));
	AssetLoader::GetMesh().push_back(pfb1);

	Mesh pfb2;
	pfb2.LoadOBJ("models/RightTurn.obj", glm::vec4(1, 1, 1, 1));
	AssetLoader::GetMesh().push_back(pfb2);

	Mesh pfb3;
	pfb3.LoadOBJ("models/RightOff.obj", glm::vec4(1, 1, 1, 1));
	AssetLoader::GetMesh().push_back(pfb3);

	Mesh pfb4;
	pfb4.LoadOBJ("models/LeftTurn.obj", glm::vec4(1, 1, 1, 1));
	AssetLoader::GetMesh().push_back(pfb4);

	Mesh pfb5;
	pfb5.LoadOBJ("models/LeftOff.obj", glm::vec4(1, 1, 1, 1));
	AssetLoader::GetMesh().push_back(pfb5);

	Material mat0;
	mat0.LoadDiffuseFromFile("images/Stone_001_Diffuse.png");
	mat0.LoadSpecularFromFile("images/Stone_001_Specular.png");
	mat0.SetAll(1.f);
	AssetLoader::GetMat().push_back(mat0);

#pragma endregion

	InstantiatingSystem::AddPrefab(new TestPrefab()); //prefab 0
	InstantiatingSystem::AddPrefab(new StraightTrack()); //prefab 1
	InstantiatingSystem::AddPrefab(new SideTrack()); //prefab 2
	InstantiatingSystem::AddPrefab(new RightTurn()); // prefab 3
	InstantiatingSystem::AddPrefab(new RightOff()); // prefab 4
	InstantiatingSystem::AddPrefab(new LeftTurn()); // prefab 5
	InstantiatingSystem::AddPrefab(new LeftOff()); // prefab 6
	*/
}

void PrefabMakeScene::Update()
{
	/*
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_I) == GLFW_PRESS)
	{
		//	ECS::Get<PhysicsBody>(3).GetBody()->setActivationState(1);
		ECS::Get<PhysicsBody>(3).SetLinearVelocity(btVector3(5, 0, 0));
	}

	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_E) == GLFW_PRESS)
	{

		InstantiatingSystem::InitPrefab(0, ECS::Get<Transform>(0).GetPosition());

		glm::vec3 f = ECS::Get<Camera>(0).GetForward() * 10.f;//agony
		ECS::Get<PhysicsBody>(ECS::GetSize() - 1).SetLinearVelocity(btVector3(f.x, f.y, f.z));

	}
	*/
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_F) == GLFW_PRESS)
	{
		glfwSetInputMode(BackEnd::m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_G) == GLFW_PRESS)
	{
		glfwSetInputMode(BackEnd::m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_MINUS) == GLFW_PRESS)
	{
		if (ECS::Get<MorphAnimator>(2).GetAnimData().t < 1.f)
		{
			float newT;
			newT = ECS::Get<MorphAnimator>(2).GetAnimData().t;
			newT += 1.f * Timer::dt;
			ECS::Get<MorphAnimator>(2).SetT(newT);
		}
		else {
			ECS::Get<MorphAnimator>(2).SetT(0.95f);
		}
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_EQUAL) == GLFW_PRESS)
	{
		if (ECS::Get<MorphAnimator>(2).GetAnimData().t > 0.f)
		{
			float newT;
			newT = ECS::Get<MorphAnimator>(2).GetAnimData().t;
			newT -= 1.f * Timer::dt;
			ECS::Get<MorphAnimator>(2).SetT(newT);
		}
		else {
			ECS::Get<MorphAnimator>(2).SetT(0.01f);
		}
	}


	//std::cout << ECS::Get<MorphAnimator>(2).GetAnimData().t << std::endl;
	
}
