#include <TestScene.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <AssetLoader.h>

void TestScene::InitScene()
{
	srand(time(NULL)); // This is needed for generating a new seed for randoms

	//Player Camera - - - Need This For A Game To Run
	m_sceneReg = new entt::registry;
	ECS::AttachRegistry(m_sceneReg);
	
	ECS::Create(0); //please please please always have camera be entity 0 it will break otherwise
	ECS::Add<Transform>(0);
	ECS::Add<PhysicsBody>(0);  
	ECS::Add<Camera>(0);
	ECS::Add<Player>(0);
	ECS::Get<Camera>(0).ResizeWindow(1920, 1080);
	ECS::Get<PhysicsBody>(0).AddBody(15, btVector3(3, 10, 3), btVector3(1,2,1));
	ECS::Add<LightSource>(0);
	ECS::Get<PhysicsBody>(0).m_Entity = 0;

	//Drunk Walker - - - Important For World Generation
	ECS::Create(1);
	ECS::Add<Transform>(1);
	ECS::Get<Transform>(1).SetPosition(glm::vec3(3.f, 0.f, 3.f));
	ECS::Add<Mesh>(1);
	ECS::Get<Mesh>(1).LoadOBJ("Models/cube.obj", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	ECS::Add<Material>(1);
	ECS::Get<Material>(1).LoadDiffuseFromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(1).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(1).SetAll(1.f);

	/*
	//Test Enemy
	ECS::Create(2);
	ECS::Add<Mesh>(2);
	//ECS::Add<MorphAnimator>(2);
	ECS::Add<Material>(2);

	
	ECS::Add<Transform>(2);
	ECS::Add<LightSource>(2);
	ECS::Get<Transform>(2).SetPosition(glm::vec3(0, 5, 0));
	ECS::Get<Transform>(2).SetScale(glm::vec3(1.f, 1.f, 1.f));
	ECS::Get<Mesh>(2).LoadOBJ("models/cube.obj", glm::vec4(1, 0, 0, 1));
	ECS::Get<Material>(2).LoadDiffuseFromFile("images/FE_TEXTURE.png");
	ECS::Get<Material>(2).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(2).SetAll(1.f);
	
	*/
	//Enemy for animation test
	ECS::Create(2);
	//ECS::Add<Mesh>(2);
	ECS::Add<MorphAnimator>(2);
	ECS::Add<LightSource>(2);
	ECS::Add<Material>(2);
	ECS::Add<Transform>(2);
	ECS::Add<PhysicsBody>(2);
	ECS::Add<Enemy>(2);
	ECS::Get<Transform>(2).SetPosition(glm::vec3(1, 3, 1));
	ECS::Get<Transform>(2).SetScale(glm::vec3(0.5, 0.5, 0.5));
	for (int i = 1; i <= 8; i++)
	{
		std::string path;
		path = "models/animations/FIRE_ENEMY/FE_WALK_" + std::to_string(i);
		path += ".obj";
		ECS::Get<MorphAnimator>(2).LoadFrame(path, glm::vec4(0.1 * i, 0.2 * i, 0.3 * i, 1));
		std::cout << "added frame " << i << std::endl;
	}
	
	for (int i = 1; i <= 8; i++)
	{
		std::string path;
		path = "models/animations/FIRE_ENEMY/FE_H_" + std::to_string(i);
		path += ".obj";
		ECS::Get<MorphAnimator>(2).LoadFrame(path, glm::vec4(0.1 * i, 0.2 * i, 0.3 * i, 1));
		std::cout << "added frame " << i << std::endl;
	}

	for (int i = 1; i <= 3; i++)
	{
		std::string path;
		path = "models/animations/FIRE_ENEMY/FE_D_" + std::to_string(i);
		path += ".obj";
		ECS::Get<MorphAnimator>(2).LoadFrame(path, glm::vec4(0.1 * i, 0.2 * i, 0.3 * i, 1));
		std::cout << "added frame " << i << std::endl;
	}
	ECS::Get<MorphAnimator>(2).AddNewAnimation(0, 7, 0.1);
	//ECS::Get<MorphAnimator>(2).AddNewAnimation(8, 15, 2);
	//ECS::Get<MorphAnimator>(2).AddNewAnimation(16, 18, 1);
	ECS::Get<MorphAnimator>(2).SetActiveAnimation(0);
	ECS::Get<Material>(2).LoadDiffuseFromFile("images/FE_TEXTURE.png");
	ECS::Get<Material>(2).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(2).SetAll(1.f);
	ECS::Get<PhysicsBody>(2).AddBody(10, btVector3(0, 5, 0), btVector3(2, 2, 2));
	ECS::Get<PhysicsBody>(2).SetUserData(5);
	ECS::Get<PhysicsBody>(2).SetUserData2(2);//this basically keeps track of what entity this is, used in order to keep track of which enemy is which


	//to help debug the ray cast
	ECS::Create(3);
	ECS::Add<Mesh>(3);
	ECS::Add<Material>(3);
	ECS::Add<Transform>(3);
	ECS::Add<LightSource>(3);
	ECS::Get<Transform>(3).SetPosition(glm::vec3(0, 5, 0));
	ECS::Get<Transform>(3).SetScale(glm::vec3(1.f, 1.f, 1.f));
	ECS::Get<Mesh>(3).LoadOBJ("models/cube.obj", glm::vec4(0, 1, 0, 1));
	ECS::Get<Material>(3).LoadDiffuseFromFile("images/FE_TEXTURE.png");
	ECS::Get<Material>(3).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(3).SetAll(1.f);


	


	





#pragma region asset_loading

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

	//WORLD GENERATOR - - - WIP
	bool isForward = true, isRight = false, isLeft = false;
	InstantiatingSystem::InitPrefab(1, ECS::Get<Transform>(1).GetPosition()); //Creates a block on spawn for the player
	for (int i = 0; i < 10; i++) { //Creates a drunk walker of 25 length
		if (isForward) {
			for (int i = 0; i < rand() % 3 + 1; i++) {
				ECS::Get<Transform>(1).SetPosition(glm::vec3(
					ECS::Get<Transform>(1).GetPosition().x + 40.f,
					ECS::Get<Transform>(1).GetPosition().y,
					ECS::Get<Transform>(1).GetPosition().z));
				InstantiatingSystem::InitPrefab(1, ECS::Get<Transform>(1).GetPosition());
			}
			isForward = false;
			int temp = rand() % 2;
			if (temp == 0) {
				isRight = true;
			}
			else {
				isLeft = true;
			}
		}
		else if (isRight) {
			ECS::Get<Transform>(1).SetPosition(glm::vec3(
				ECS::Get<Transform>(1).GetPosition().x + 40.f,
				ECS::Get<Transform>(1).GetPosition().y,
				ECS::Get<Transform>(1).GetPosition().z));
			InstantiatingSystem::InitPrefab(4, ECS::Get<Transform>(1).GetPosition()); // Right Off
			for (int i = 0; i < rand() % 3 + 1; i++) {
				ECS::Get<Transform>(1).SetPosition(glm::vec3(
					ECS::Get<Transform>(1).GetPosition().x,
					ECS::Get<Transform>(1).GetPosition().y,
					ECS::Get<Transform>(1).GetPosition().z + 40.f));
				InstantiatingSystem::InitPrefab(2, ECS::Get<Transform>(1).GetPosition());
			}
			isRight = false;
			isForward = true;
			ECS::Get<Transform>(1).SetPosition(glm::vec3(
				ECS::Get<Transform>(1).GetPosition().x,
				ECS::Get<Transform>(1).GetPosition().y,
				ECS::Get<Transform>(1).GetPosition().z + 40.f));
			InstantiatingSystem::InitPrefab(5, ECS::Get<Transform>(1).GetPosition()); // Left Turn
		}
		else if (isLeft) {
			ECS::Get<Transform>(1).SetPosition(glm::vec3(
				ECS::Get<Transform>(1).GetPosition().x + 40.f,
				ECS::Get<Transform>(1).GetPosition().y,
				ECS::Get<Transform>(1).GetPosition().z));
			InstantiatingSystem::InitPrefab(6, ECS::Get<Transform>(1).GetPosition()); // Left Off
			for (int i = 0; i < rand() % 3 + 1; i++) {
				ECS::Get<Transform>(1).SetPosition(glm::vec3(
					ECS::Get<Transform>(1).GetPosition().x,
					ECS::Get<Transform>(1).GetPosition().y,
					ECS::Get<Transform>(1).GetPosition().z - 40.f));
				InstantiatingSystem::InitPrefab(2, ECS::Get<Transform>(1).GetPosition());
			}
			isLeft = false;
			isForward = true;
			ECS::Get<Transform>(1).SetPosition(glm::vec3(
				ECS::Get<Transform>(1).GetPosition().x,
				ECS::Get<Transform>(1).GetPosition().y,
				ECS::Get<Transform>(1).GetPosition().z - 40.f));
			InstantiatingSystem::InitPrefab(3, ECS::Get<Transform>(1).GetPosition()); // Right Turn
		}
	}
	//WORLD GENERATOR - - - WIP
}

//please change this later
int projId = 0;

void TestScene::Update()
{
	


	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_I) == GLFW_PRESS)
	{
	//	ECS::Get<PhysicsBody>(3).GetBody()->setActivationState(1);
		ECS::Get<PhysicsBody>(3).SetLinearVelocity(btVector3(5, 0, 0));
	}

	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_E) == GLFW_PRESS)
	{
		
		InstantiatingSystem::InitPrefab(0, ECS::Get<Transform>(0).GetPosition());

		glm::vec3 f = ECS::Get<Camera>(0).GetForward() * 10.f;//agony
		ECS::Get<PhysicsBody>(ECS::GetSize()-1).SetLinearVelocity(btVector3(f.x,f.y,f.z));

	}

	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_F) == GLFW_PRESS)
	{
		glfwSetInputMode(BackEnd::m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_G) == GLFW_PRESS)
	{
		glfwSetInputMode(BackEnd::m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (ECS::Get<Enemy>(2).m_hp <= 0)
	{
		ECS::Get<Enemy>(2).m_hp = 3;
		btTransform transform;
		transform = ECS::Get<PhysicsBody>(2).GetBody()->getCenterOfMassTransform();
		transform.setOrigin(btVector3(0, 10, 0));
		ECS::Get<PhysicsBody>(2).GetBody()->setCenterOfMassTransform(transform);
	}

	ECS::Get<Player>(0).Update();
}