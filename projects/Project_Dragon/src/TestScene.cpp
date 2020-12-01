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
	ECS::Get<PhysicsBody>(0).AddBody(15, btVector3(3, 10, 3), btVector3(1, 2, 1));
	ECS::Add<LightSource>(0);
	ECS::Get<PhysicsBody>(0).m_Entity = 0;
	ECS::Get<Player>(0).SetMovementSpeed(10.f);
	ECS::Get<Player>(0).Init();

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
	ECS::Add<Mesh>(2);
	ECS::Add<Transform>(2);
	ECS::Add<PhysicsBody>(2);
	ECS::Add<Enemy>(2);
	
	ECS::Get<MorphAnimator>(2).LoadFrame("models/animations/FIRE_ENEMY/FW_W_1.obj", glm::vec4(1, 1, 1, 1));
	ECS::Get<MorphAnimator>(2).LoadFrame("models/animations/FIRE_ENEMY/FW_W_2.obj", glm::vec4(1, 1, 1, 1));
	ECS::Get<MorphAnimator>(2).AddNewAnimation(0,1,1);
	ECS::Get<MorphAnimator>(2).SetActiveAnimation(0);
	
	ECS::Get<Mesh>(2).LoadOBJ("models/cube.obj", glm::vec4(1, 1, 1, 1));
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
	ECS::Get<Mesh>(3).LoadOBJ("models/cube.obj", glm::vec4(0, 1, 0, 1));
	ECS::Get<Material>(3) = AssetLoader::GetMatFromStr("StraightPathTexture");

	



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
	for (int i = 0; i < 5; i++) { //Creates a drunk walker of 25 length
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
				InstantiatingSystem::InitPrefab(2, glm::vec3(temp.x, temp.y - 8.2f, temp.z));
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
				InstantiatingSystem::InitPrefab(2, glm::vec3(temp.x, temp.y - 8.2f, temp.z));
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
void TestScene::Update()
{

	ECS::Get<Player>(0).DrawUI();

	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_I) == GLFW_PRESS)
	{
		//	ECS::Get<PhysicsBody>(3).GetBody()->setActivationState(1);
		ECS::Get<PhysicsBody>(3).SetLinearVelocity(btVector3(5, 0, 0));
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

	//lerp for light for algo demo

	float LightVal1 = 0.4;
	float LightVal2 = 1;
	bool isForward = true;

	if (t >= 1 && t > 0)
		isForward = false;
	if (t <= 0)
		isForward = true;

	if (isForward)
		t += Timer::dt;
	else
		t -= Timer::dt;

	std::cout << t << std::endl;

	ECS::Get<LightSource>(2).m_Diffuse.z = Interpolation::LERP(LightVal1, LightVal2, t);


}