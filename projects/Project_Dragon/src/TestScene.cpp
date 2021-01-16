#include <TestScene.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <AssetLoader.h>
#include <Interpolation.h>
#include <SpriteRendering.h>
#include <AudioEngine.h>

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
	ECS::Get<PhysicsBody>(0).AddBody(100, btVector3(3, 10, 3), btVector3(1, 2, 1), 3.0f);
	ECS::Add<LightSource>(0);
	ECS::Get<LightSource>(0).m_Ambient = glm::vec3(1, 1, 1);
	ECS::Get<PhysicsBody>(0).m_Entity = 0;
	ECS::Get<Player>(0).SetMovementSpeed(10.f);
	ECS::Add<UI>(0);
	ECS::Get<UI>(0).mesh.LoadOBJ("models/other/plane.obj", glm::vec4(1, 1, 1, 1));
	ECS::Get<UI>(0).material.LoadDiffuseFromFile("images/HP_FULL.png");
	ECS::Get<UI>(0).material.LoadSpecularFromFile("images/UIGood.png");
	ECS::Get<UI>(0).material.SetAll(1.f);
	//Drunk Walker - - - Important For World Generation
	ECS::Create(1);
	ECS::Add<Transform>(1);
	ECS::Get<Transform>(1).SetPosition(glm::vec3(3.f, 0.f, 3.f));
	ECS::Add<Mesh>(1);
	ECS::Get<Mesh>(1).LoadOBJ("Models/other/cube.obj", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	ECS::Add<Material>(1);
	ECS::Get<Material>(1).LoadDiffuseFromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(1).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(1).SetAll(1.f);

	//Enemy for animation test


	//to help debug the ray cast
	ECS::Create(2);
	ECS::Add<Mesh>(2);
	ECS::Add<Material>(2);
	ECS::Add<Transform>(2);
	ECS::Add<LightSource>(2);
	ECS::Get<LightSource>(2).m_Diffuse = glm::vec3(0, 0.01, 1);
	ECS::Get<Transform>(2).SetPosition(glm::vec3(0, 5, 0));
	ECS::Get<Transform>(2).SetScale(glm::vec3(2.f, 2.f, 2.f));
	ECS::Get<Mesh>(2).LoadOBJ("models/other/ice_projectile.obj", glm::vec4(0, 1, 0, 1));
	ECS::Get<Material>(2).LoadDiffuseFromFile("images/ice_tex.png");
	ECS::Get<Material>(2).LoadSpecularFromFile("images/ice_tex.png");
	ECS::Get<Material>(2).SetAll(1.f);




	//Wall to prevent player from walking off the end
	ECS::Create(3);
	ECS::Add<Mesh>(3);
	ECS::Add<Material>(3);
	ECS::Add<Transform>(3);
	ECS::Add<PhysicsBody>(3);
	ECS::Get<Transform>(3).SetPosition(glm::vec3(-10, 0, 5));
	ECS::Get<Transform>(3).SetRotation(glm::vec3(0, 0, 1), glm::radians(90.f));
	ECS::Get<Transform>(3).SetScale(glm::vec3(10.f, 1.f, 25.f));
	ECS::Get<Mesh>(3).LoadOBJ("models/other/plane.obj", glm::vec4(0, 1, 0, 1));
	ECS::Get<Material>(3).LoadDiffuseFromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(3).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(3).SetAll(0.1f);
	ECS::Get<PhysicsBody>(3).AddBody(0.f, btVector3(-10, 0, 5), btVector3(1.f, 25.f, 25.f));


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
	for (int i = 0; i < 15; i++) { //Creates a drunk walker of 25 length
		if (isForward) {
			for (int i = 0; i < rand() % 3 + 1; i++) {
				ECS::Get<Transform>(1).SetPosition(glm::vec3(
					ECS::Get<Transform>(1).GetPosition().x + 40.f,
					ECS::Get<Transform>(1).GetPosition().y,
					ECS::Get<Transform>(1).GetPosition().z));
				glm::vec3 temp;
				temp = ECS::Get<Transform>(1).GetPosition();

				InstantiatingSystem::InitPrefab(1, glm::vec3(temp.x, temp.y, temp.z));
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
				glm::vec3 temp = ECS::Get<Transform>(1).GetPosition();
				InstantiatingSystem::InitPrefab(2, glm::vec3(temp.x, temp.y - 8.25f, temp.z));
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
				glm::vec3 temp = ECS::Get<Transform>(1).GetPosition();
				InstantiatingSystem::InitPrefab(2, glm::vec3(temp.x, temp.y - 8.25f, temp.z));
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

	/*
	//music
	Sound2D _Music("sounds/song.mp3", "group1");
	_Music.setLoopCount(1000);
	_Music.play();
	*/
	//test the file loader
	InstantiatingSystem::LoadPrefabFromFile(ECS::GetSize(), glm::vec3(0, 10, 0), "prefabs/test_file.bit");


}

//please change this later
int projId = 0;

void TestScene::Update()
{
	
	ECS::Get<Player>(0).Update();

}