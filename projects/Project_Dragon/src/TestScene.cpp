#include <TestScene.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <AssetLoader.h>
#include <Interpolation.h>
#include <SpriteRendering.h>

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
	ECS::Get<LightSource>(0).m_Ambient = glm::vec3(0.1, 1, 0.1);
	ECS::Get<PhysicsBody>(0).m_Entity = 0;
	ECS::Get<Player>(0).SetMovementSpeed(10.f);


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




	//Enemy for animation test
	ECS::Create(2);
	ECS::Add<MorphAnimator>(2);
	ECS::Add<LightSource>(2);
	ECS::Get<LightSource>(2).m_Diffuse = glm::vec3(1, 0, 0);
	ECS::Get<LightSource>(2).m_Ambient = glm::vec3(1, 0, 0);
	ECS::Add<Material>(2);
	ECS::Add<Transform>(2);
	ECS::Add<PhysicsBody>(2);
	ECS::Add<Enemy>(2);
	for (int i = 1; i <= 8; i++)
	{
		std::string fileName = "models/animations/FIRE_ENEMY/FW_W_";
		ECS::Get<MorphAnimator>(2).LoadFrame(fileName + std::to_string(i) + ".obj", glm::vec4(1, 1, 1, 1));
	}
	
	ECS::Get<MorphAnimator>(2).AddNewAnimation(0,7,1);
	ECS::Get<MorphAnimator>(2).SetActiveAnimation(0);
	
	//ECS::Get<Mesh>(2).LoadOBJ("models/cube.obj", glm::vec4(1, 1, 1, 1));
	ECS::Get<Material>(2).LoadDiffuseFromFile("images/FE_TEXTURE.png");
	ECS::Get<Material>(2).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(2).SetAll(1.f);
	ECS::Get<PhysicsBody>(2).AddBody(10, btVector3(1, 5, 1), btVector3(3, 3, 3));
	ECS::Get<PhysicsBody>(2).SetUserData(5);
	ECS::Get<PhysicsBody>(2).SetUserData2(2);//this basically keeps track of what entity this is, used in order to keep track of which enemy is which
	ECS::Get<PhysicsBody>(2).m_Entity = 2;

	//to help debug the ray cast
	ECS::Create(3);
	ECS::Add<Mesh>(3);
	ECS::Add<Material>(3);
	ECS::Add<Transform>(3);
	ECS::Add<LightSource>(3);
	ECS::Get<Transform>(3).SetPosition(glm::vec3(0, 5, 0));
	ECS::Get<Transform>(3).SetScale(glm::vec3(1.f, 1.f, 1.f));
	ECS::Get<Mesh>(3).LoadOBJ("models/other/ice_projectile.obj", glm::vec4(0, 1, 0, 1));
	ECS::Get<Material>(3).LoadDiffuseFromFile("images/ice_tex.png");
	ECS::Get<Material>(3).LoadSpecularFromFile("images/ice_tex.png");
	ECS::Get<Material>(3).SetAll(1.f);



	//hand
	ECS::Create(4);
	ECS::Add<Mesh>(4);
	ECS::Add<Material>(4);
	ECS::Add<Transform>(4);
	ECS::Add<LightSource>(4);
	ECS::Add<Parent>(4);
	ECS::Get<Parent>(4).SetParent(0);
	ECS::Get<Transform>(4).SetPosition(glm::vec3(0, 5, 0));
	ECS::Get<Transform>(4).SetScale(glm::vec3(1.f, 1.f, 1.f));
	ECS::Get<Mesh>(4).LoadOBJ("models/hand.obj", glm::vec4(0, 1, 0, 1));
	ECS::Get<Material>(4).LoadDiffuseFromFile("images/handtexture.png");
	ECS::Get<Material>(4).LoadSpecularFromFile("images/handtexture.png");
	ECS::Get<Material>(4).SetAll(0.1f);

	//Wall to prevent player from walking off the end
	ECS::Create(5);
	ECS::Add<Mesh>(5);
	ECS::Add<Material>(5);
	ECS::Add<Transform>(5);
	ECS::Add<PhysicsBody>(5);
	ECS::Get<Transform>(5).SetPosition(glm::vec3(-10, 0, 5));
	ECS::Get<Transform>(5).SetRotation(glm::vec3(0, 0, 1), glm::radians(90.f));
	ECS::Get<Transform>(5).SetScale(glm::vec3(10.f, 1.f, 25.f));
	ECS::Get<Mesh>(5).LoadOBJ("models/other/plane.obj", glm::vec4(0, 1, 0, 1));
	ECS::Get<Material>(5).LoadDiffuseFromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(5).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(5).SetAll(0.1f);
	ECS::Get<PhysicsBody>(5).AddBody(0.f, btVector3(-10, 0, 5), btVector3(1.f, 25.f, 25.f));




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
	for (int i = 0; i < 25; i++) { //Creates a drunk walker of 25 length
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
}

//please change this later
int projId = 0;
float t = 0;
bool isForward = true;
void TestScene::Update()
{
	
	//output an FPS
	std::cout << 1/ Timer::dt << std::endl;

	ECS::Get<Player>(0).Update();

	//lerp for light for algo demo

	float LightVal1 = 0.4;
	float LightVal2 = 1;


	if (t >= 1 && t > 0)
		isForward = false;
	if (t <= 0)
		isForward = true;

	if (isForward)
		t += Timer::dt;
	else
		t -= Timer::dt;


	ECS::Get<LightSource>(2).m_Diffuse.z = Interpolation::LERP(LightVal1, LightVal2, t);


}