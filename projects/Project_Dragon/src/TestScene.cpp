#include <TestScene.h>
#include <bullet/btBulletDynamicsCommon.h>

void TestScene::InitScene()
{
	srand(time(NULL)); // This is needed for generating a new seed for randoms

	//Player Camera - - - Need This For A Game To Run
	m_sceneReg = new entt::registry;
	ECS::AttachRegistry(m_sceneReg);
	ECS::Create(0); //please please please always have camera be entity 0 it will break otherwise
	ECS::Add<Transform>(0);
	ECS::Get<Transform>(0).SetPosition(glm::vec3(2.f, 2.f, 0.f));
	ECS::Add<Camera>(0);
	ECS::Get<Camera>(0).ResizeWindow(1920, 1080);
	ECS::Add<LightSource>(0);

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

	ECS::Create(2);
	ECS::Add<Transform>(2);
	ECS::Add<LightSource>(2);
	ECS::Add<Parent>(2);
	ECS::Get<Parent>(2).SetParent(0);
	ECS::Get<Transform>(2).SetPosition(glm::vec3(0.f, 3.f, 0.f));

	ECS::Create(3);
	ECS::Add<Mesh>(3);
	ECS::Add<Material>(3);
	ECS::Add<Transform>(3);
	ECS::Add<PhysicsBody>(3);
	ECS::Get<Mesh>(3).LoadOBJ("models/cube.obj", glm::vec4(1, 1, 1, 1));
	ECS::Get<Material>(3).LoadDiffuseFromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(3).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(3).SetAll(1.f);
	ECS::Get<PhysicsBody>(3).AddBody(1.f, btVector3(0, 15, 0), btVector3(1, 1, 1));
	//ECS::Get<PhysicsBody>(3).m_BodyId = 0;

	ECS::Create(4);
	ECS::Add<Mesh>(4);
	ECS::Add<Material>(4);
	ECS::Add<Transform>(4);
	ECS::Add<PhysicsBody>(4);
	ECS::Get<Mesh>(4).LoadOBJ("models/cube.obj", glm::vec4(1, 1, 1, 1));
	ECS::Get<Material>(4).LoadDiffuseFromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(4).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(4).SetAll(1.f);
	ECS::Get<PhysicsBody>(4).AddBody(0.f, btVector3(0, 0, 0), btVector3(5, 1, 5));
	//ECS::Get<PhysicsBody>(4).m_BodyId = 1;

	IMGUIManager::imGuiCallbacks.push_back([&]()
		{
			static const char* items[]{ "0" };
			//We want to take all of our entities, and be able to manage their positions using this drop down menu
			static int SelectedItem = 0;
			if (ImGui::CollapsingHeader("Entity List"))
			{
				static const char* items[]{ "0" };
				//We want to take all of our entities, and be able to manage their positions using this drop down menu
				static int SelectedItem = 0;
				if (ImGui::CollapsingHeader("Entity List"))
				{
					//ImGui::ListBox("list",&SelectedItem,items,IM_ARRAYSIZE(items));
					ImGui::Combo("List box", &SelectedItem, items, IM_ARRAYSIZE(items));
				}
			}
		});

	InstantiatingSystem::AddPrefab(new TestPrefab()); //prefab 0
	InstantiatingSystem::AddPrefab(new StraightTrack()); //prefab 1

	//WORLD GENERATOR - - - WIP

	std::vector<glm::vec3> worldGenHold; // list of vectors to hold the positon of the nodes
	std::vector<char> worldGenTags;
	char nodeNameHold = 's';
	for (int i = 0; i < 25; i++) { //Creates a drunk walker of 25 length
		worldGenHold.push_back(ECS::Get<Transform>(1).GetPosition()); //pushes a new node into the list
		switch (rand() % 4) //switch statement to move the drunk walker around
		{
		case 0:
			if (nodeNameHold != 'l') {
				ECS::Get<Transform>(1).SetPosition(glm::vec3(ECS::Get<Transform>(1).GetPosition().x, ECS::Get<Transform>(1).GetPosition().y, ECS::Get<Transform>(1).GetPosition().z + 40.f));
				nodeNameHold = 'r';
				break;
			}
		case 1:
			if (nodeNameHold != 'r') {
				ECS::Get<Transform>(1).SetPosition(glm::vec3(ECS::Get<Transform>(1).GetPosition().x, ECS::Get<Transform>(1).GetPosition().y, ECS::Get<Transform>(1).GetPosition().z - 40.f));
				nodeNameHold = 'l';
				break;
			}
		default:
			ECS::Get<Transform>(1).SetPosition(glm::vec3(ECS::Get<Transform>(1).GetPosition().x + 40.f, ECS::Get<Transform>(1).GetPosition().y, ECS::Get<Transform>(1).GetPosition().z));
			nodeNameHold = 's';
			break;
		}
		worldGenTags.push_back(nodeNameHold); // pushes a new nametag into the list
	}

	for (int i = 0; i < worldGenHold.size(); i++) {
		switch (worldGenTags[i])
		{
		case 's':
			//Instantiate Straight Tile
			InstantiatingSystem::InitPrefab(1, worldGenHold[i]);
			break;
		case 'r':
			//Instantiate Right Line
			InstantiatingSystem::InitPrefab(0, worldGenHold[i]);
			break;
		case 'l':
			//Instantiate Left Line
			InstantiatingSystem::InitPrefab(0, worldGenHold[i]);
			break;
		default:
			break;
		}
	}
	//WORLD GENERATOR - - - WIP
}

void TestScene::Update()
{
}