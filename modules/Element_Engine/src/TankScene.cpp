/*
#include <TankScene.h>

#include <PhysicsSystem.h>

void TankScene::InitScene()
{
	m_sceneReg = new entt::registry;

	ECS::AttachRegistry(m_sceneReg);

	ECS::Create(0); //please please please always have camera be entity 0 it will break otherwise
	ECS::Add<Transform>(0);
	ECS::Add<Camera>(0);
	ECS::Get<Transform>(0).SetPosition(glm::vec3(0.f, 25.f, 0.f));

	ECS::Get<Camera>(0).ResizeWindow(1920, 1080);

	Mesh cube; //in order to only load it once
	cube.LoadOBJ("models/Cube.obj", glm::vec4(1.f, 1.f, 1.f, 1.f));

	Mesh bullet;
	bullet.LoadOBJ("models/TankShell.obj", glm::vec4(1.f,1.f,1.f,1.f)); //model source: https://skfb.ly/6RHs7

	Mesh tank;
	tank.LoadOBJ("models/Tank_Fixed.obj", glm::vec4(1.f,1.f,1.f,1.f)); //player 1 tank, model from: https://skfb.ly/6WnNQ

	ECS::Create(1);//Player 1 tank
	ECS::Add<Transform>(1);
	ECS::Add<TankData>(1);
	ECS::Add<Mesh>(1);
	ECS::Add<Material>(1);
	ECS::Add<PhysicsBody>(1);
	ECS::Add<LightSource>(1);
	ECS::Get<TankData>(1).AttachBullet(4); //Attaches entity 4 to be the bullet to this tank
	ECS::Get<TankData>(1).AttachTank(1);
	ECS::Get<Transform>(1).SetPosition(glm::vec3(-10.f, 2.f, -15.f));
	ECS::Get<Transform>(1).SetScale(glm::vec3(1.f,1.f,1.f));
	ECS::Get<Transform>(1).SetRotation(glm::vec3(0.f,1.f,0.f), glm::radians(180.f));
	ECS::Get<Mesh>(1).SetVAO(tank.GetVAO());
	ECS::Get<Material>(1).LoadDiffuseFromFile("images/red.jpg");
	ECS::Get<Material>(1).LoadDiffuse2FromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(1).LoadSpecularFromFile("images/sample_spec.png");
	ECS::Get<Material>(1).Tex1Str = 1.f;
	ECS::Get<Material>(1).Tex2Str = 0.f;
	ECS::Get<Material>(1).SetAll(1.f);
	ECS::Get<PhysicsBody>(1).SetGravity(-10.f);
	ECS::Get<PhysicsBody>(1).SetBox(ECS::Get<Transform>(1).GetPosition(), 2, 2, 2);
	ECS::Get<PhysicsBody>(1).SetBodyType(1);
	ECS::Get<PhysicsBody>(1).SetFriction(0.8f);
	ECS::Get<PhysicsBody>(1).SetMass(1.f);
	ECS::Get<PhysicsBody>(1).SetGravityScale(0.f);

	

	ECS::Create(2);//Player 2 tank
	ECS::Add<Transform>(2);
	ECS::Add<TankData>(2);
	ECS::Add<Mesh>(2);
	ECS::Add<Material>(2);
	ECS::Add<PhysicsBody>(2);
	ECS::Add<LightSource>(2);
	ECS::Get<TankData>(2).AttachBullet(5); //Attaches entity 4 to be the bullet to this tank
	ECS::Get<TankData>(2).AttachTank(2);
	ECS::Get<Transform>(2).SetPosition(glm::vec3(10.f, 2.f, 10.f));
	ECS::Get<Transform>(2).SetRotation(glm::vec3(0.f, 1.f, 0.f), glm::radians(180.f));
	ECS::Get<Transform>(2).SetScale(glm::vec3(1.f, 1.f, 1.f));
	ECS::Get<Mesh>(2).SetVAO(tank.GetVAO());
	ECS::Get<Material>(2).LoadDiffuseFromFile("images/green.png");
	ECS::Get<Material>(2).LoadDiffuse2FromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(2).LoadSpecularFromFile("images/sample_spec.png");
	ECS::Get<Material>(2).Tex1Str = 1.f;
	ECS::Get<Material>(2).Tex2Str = 0.f;
	ECS::Get<Material>(2).SetAll(1.f);
	ECS::Get<PhysicsBody>(2).SetGravity(-10.f);
	ECS::Get<PhysicsBody>(2).SetBox(ECS::Get<Transform>(1).GetPosition(), 2, 2, 2);
	ECS::Get<PhysicsBody>(2).SetBodyType(1);
	ECS::Get<PhysicsBody>(2).SetFriction(0.8f);
	ECS::Get<PhysicsBody>(2).SetMass(1.f);
	ECS::Get<PhysicsBody>(2).SetGravityScale(0.f);

	ECS::Create(3);//plane for the tanks to be on
	ECS::Add<Transform>(3);
	ECS::Add<TankData>(3);
	ECS::Add<Mesh>(3);
	ECS::Add<Material>(3);
	ECS::Add<PhysicsBody>(3);	
	ECS::Get<Transform>(3).SetPosition(glm::vec3(0.f, 0.f, 0.f));
	ECS::Get<Transform>(3).SetScale(glm::vec3(35.f, 1.f, 60.f));
	ECS::Get<Mesh>(3).LoadOBJ("models/plane.obj", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	ECS::Get<Material>(3).LoadDiffuseFromFile("images/sample.png");
	ECS::Get<Material>(3).LoadDiffuse2FromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(3).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(3).Tex1Str = 0.f;
	ECS::Get<Material>(3).Tex2Str = 1.f;
	ECS::Get<Material>(3).SetAll(0.f);
	ECS::Get<PhysicsBody>(3).SetGravity(10.f);
	ECS::Get<PhysicsBody>(3).SetBox(ECS::Get<Transform>(1).GetPosition(), 2, 2, 2);
	ECS::Get<PhysicsBody>(3).SetBodyType(1);
	ECS::Get<PhysicsBody>(3).SetFriction(0.f);
	ECS::Get<PhysicsBody>(3).SetMass(1.f);
	ECS::Get<PhysicsBody>(3).SetGravityScale(0.f);

	ECS::Create(4);//Player 1 Bullet
	ECS::Add<Transform>(4);
	ECS::Add<TankData>(4);
	ECS::Add<Mesh>(4);
	ECS::Add<Material>(4);
	ECS::Add<PhysicsBody>(4);
	ECS::Add<LightSource>(4);
	ECS::Get<Transform>(4).SetPosition(glm::vec3(10.f, -2.f, 0.f));
	ECS::Get<Transform>(4).SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	ECS::Get<Mesh>(4).SetVAO(bullet.GetVAO());
	ECS::Get<Material>(4).LoadDiffuseFromFile("images/red.jpg");
	ECS::Get<Material>(4).LoadDiffuse2FromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(4).LoadSpecularFromFile("images/sample_spec.png");
	ECS::Get<Material>(4).Tex1Str = 1.f;
	ECS::Get<Material>(4).Tex2Str = 0.f;
	ECS::Get<Material>(4).SetAll(1.f);
	ECS::Get<PhysicsBody>(4).SetGravity(0.f);
	ECS::Get<PhysicsBody>(4).SetBox(ECS::Get<Transform>(4).GetPosition(), 1, 1, 1);
	ECS::Get<PhysicsBody>(4).SetBodyType(1);
	ECS::Get<PhysicsBody>(4).SetFriction(0.0f);
	ECS::Get<PhysicsBody>(4).SetMass(0.01f);
	ECS::Get<PhysicsBody>(4).SetGravityScale(0.f);

	ECS::Create(5);//Player 2 Bullet
	ECS::Add<Transform>(5);
	ECS::Add<TankData>(5);
	ECS::Add<Mesh>(5);
	ECS::Add<Material>(5);
	ECS::Add<PhysicsBody>(5);
	ECS::Add<LightSource>(5);
	ECS::Get<Transform>(5).SetPosition(glm::vec3(-10.f, -2.f, 0.f));
	ECS::Get<Transform>(5).SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	ECS::Get<Mesh>(5).SetVAO(bullet.GetVAO());
	ECS::Get<Material>(5).LoadDiffuseFromFile("images/green.png");
	ECS::Get<Material>(5).LoadDiffuse2FromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(5).LoadSpecularFromFile("images/green.png");
	ECS::Get<Material>(5).Tex1Str = 1.f;
	ECS::Get<Material>(5).Tex2Str = 0.f;
	ECS::Get<Material>(5).SetAll(1.f);
	ECS::Get<PhysicsBody>(5).SetGravity(0.f);
	ECS::Get<PhysicsBody>(5).SetBox(ECS::Get<Transform>(4).GetPosition(), 1, 1, 1);
	ECS::Get<PhysicsBody>(5).SetBodyType(1);
	ECS::Get<PhysicsBody>(5).SetFriction(0.0f);
	ECS::Get<PhysicsBody>(5).SetMass(0.01f);
	ECS::Get<PhysicsBody>(5).SetGravityScale(0.f);

#pragma region Walls
	ECS::Create(6); //wall
	ECS::Add<Transform>(6);
	ECS::Add<Mesh>(6);
	ECS::Add<Material>(6);
	ECS::Add<PhysicsBody>(6);
	ECS::Get<Transform>(6).SetPosition(glm::vec3(27.f, 2.f, 0.f));
	ECS::Get<Transform>(6).SetScale(glm::vec3(1.f, 1.f, 60.f));
	ECS::Get<Mesh>(6).LoadOBJ("models/cube.obj", glm::vec4(1.f,1.f,1.f,1.f));
	ECS::Get<Material>(6).LoadDiffuseFromFile("images/sample.png");
	ECS::Get<Material>(6).LoadDiffuse2FromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(6).LoadSpecularFromFile("images/sample_spec.png");
	ECS::Get<Material>(6).Tex1Str = 0.f;
	ECS::Get<Material>(6).Tex2Str = 1.f;
	ECS::Get<Material>(6).SetAll(1.f);
	ECS::Get<PhysicsBody>(6).SetBox(ECS::Get<Transform>(6).GetPosition(), 2, 2, 120);
	ECS::Get<PhysicsBody>(6).SetBodyType(0);
	ECS::Get<PhysicsBody>(6).SetFriction(0.0f);
	ECS::Get<PhysicsBody>(6).SetMass(0.01f);
	ECS::Get<PhysicsBody>(6).SetGravityScale(0.f);

	ECS::Create(7); //wall
	ECS::Add<Transform>(7);
	ECS::Add<Mesh>(7);
	ECS::Add<Material>(7);
	ECS::Add<PhysicsBody>(7);
	ECS::Get<Transform>(7).SetPosition(glm::vec3(0.f, 2.f, 50.f));
	ECS::Get<Transform>(7).SetScale(glm::vec3(25.f, 1.f, 1.f));
	ECS::Get<Mesh>(7).LoadOBJ("models/cube.obj", glm::vec4(1.f, 1.f, 1.f, 1.f));
	ECS::Get<Material>(7).LoadDiffuseFromFile("images/sample.png");
	ECS::Get<Material>(7).LoadDiffuse2FromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(7).LoadSpecularFromFile("images/sample_spec.png");
	ECS::Get<Material>(7).Tex1Str = 0.f;
	ECS::Get<Material>(7).Tex2Str = 1.f;
	ECS::Get<Material>(7).SetAll(1.f);
	ECS::Get<PhysicsBody>(7).SetBox(ECS::Get<Transform>(7).GetPosition(), 54, 2, 2); //todo fix
	ECS::Get<PhysicsBody>(7).SetBodyType(0);
	ECS::Get<PhysicsBody>(7).SetFriction(0.0f);
	ECS::Get<PhysicsBody>(7).SetMass(0.01f);
	ECS::Get<PhysicsBody>(7).SetGravityScale(0.f);

	ECS::Create(8); //wall
	ECS::Add<Transform>(8);
	ECS::Add<Mesh>(8);
	ECS::Add<Material>(8);
	ECS::Add<PhysicsBody>(8);
	ECS::Get<Transform>(8).SetPosition(glm::vec3(-27.f, 2.f, 0.f));
	ECS::Get<Transform>(8).SetScale(glm::vec3(1.f, 1.f, 60.f));
	ECS::Get<Mesh>(8).LoadOBJ("models/cube.obj", glm::vec4(1.f, 1.f, 1.f, 1.f));
	ECS::Get<Material>(8).LoadDiffuseFromFile("images/sample.png");
	ECS::Get<Material>(8).LoadDiffuse2FromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(8).LoadSpecularFromFile("images/sample_spec.png");
	ECS::Get<Material>(8).Tex1Str = 0.f;
	ECS::Get<Material>(8).Tex2Str = 1.f;
	ECS::Get<Material>(8).SetAll(1.f);
	ECS::Get<PhysicsBody>(8).SetBox(ECS::Get<Transform>(8).GetPosition(), 2, 2, 120); //todo fix
	ECS::Get<PhysicsBody>(8).SetBodyType(0);
	ECS::Get<PhysicsBody>(8).SetFriction(0.0f);
	ECS::Get<PhysicsBody>(8).SetMass(0.01f);
	ECS::Get<PhysicsBody>(8).SetGravityScale(0.f);

	ECS::Create(9); //wall
	ECS::Add<Transform>(9);
	ECS::Add<Mesh>(9);
	ECS::Add<Material>(9);
	ECS::Add<PhysicsBody>(9);
	ECS::Get<Transform>(9).SetPosition(glm::vec3(0.f, 2.f, -50.f));
	ECS::Get<Transform>(9).SetScale(glm::vec3(25.f, 1.f, 1.f));
	ECS::Get<Mesh>(9).LoadOBJ("models/cube.obj", glm::vec4(1.f, 1.f, 1.f, 1.f));
	ECS::Get<Material>(9).LoadDiffuseFromFile("images/sample.png");
	ECS::Get<Material>(9).LoadDiffuse2FromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(9).LoadSpecularFromFile("images/sample_spec.png");
	ECS::Get<Material>(9).Tex1Str = 0.f;
	ECS::Get<Material>(9).Tex2Str = 1.f;
	ECS::Get<Material>(9).SetAll(1.f);
	ECS::Get<PhysicsBody>(9).SetBox(ECS::Get<Transform>(9).GetPosition(), 54, 2, 2); //todo fix
	ECS::Get<PhysicsBody>(9).SetBodyType(0);
	ECS::Get<PhysicsBody>(9).SetFriction(0.0f);
	ECS::Get<PhysicsBody>(9).SetMass(0.01f);
	ECS::Get<PhysicsBody>(9).SetGravityScale(0.f);
#pragma endregion

	ECS::Create(10); //center obstacle
	ECS::Add<Transform>(10);
	ECS::Add<Mesh>(10);
	ECS::Add<Material>(10);
	ECS::Add<PhysicsBody>(10);
	ECS::Get<Transform>(10).SetPosition(glm::vec3(10.f, 2.f, 0.f));
	ECS::Get<Transform>(10).SetScale(glm::vec3(4.f, 1.f, 4.f));
	ECS::Get<Mesh>(10).SetVAO(cube.GetVAO());
	ECS::Get<Material>(10).LoadDiffuseFromFile("images/sample.png");
	ECS::Get<Material>(10).LoadDiffuse2FromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(10).LoadSpecularFromFile("images/sample_spec.png");
	ECS::Get<Material>(10).Tex1Str = 0.f;
	ECS::Get<Material>(10).Tex2Str = 1.f;
	ECS::Get<Material>(10).SetAll(1.f);
	ECS::Get<PhysicsBody>(10).SetBox(ECS::Get<Transform>(10).GetPosition(), 8, 2, 8);
	ECS::Get<PhysicsBody>(10).SetBodyType(0);
	ECS::Get<PhysicsBody>(10).SetFriction(0.0f);
	ECS::Get<PhysicsBody>(10).SetMass(0.01f);
	ECS::Get<PhysicsBody>(10).SetGravityScale(0.f);

	ECS::Create(11); //center obstacle
	ECS::Add<Transform>(11);
	ECS::Add<Mesh>(11);
	ECS::Add<Material>(11);
	ECS::Add<PhysicsBody>(11);
	ECS::Get<Transform>(11).SetPosition(glm::vec3(-10.f, 2.f, -5.f));
	ECS::Get<Transform>(11).SetScale(glm::vec3(4.f, 1.f, 4.f));
	ECS::Get<Mesh>(11).SetVAO(cube.GetVAO());
	ECS::Get<Material>(11).LoadDiffuseFromFile("images/sample.png");
	ECS::Get<Material>(11).LoadDiffuse2FromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(11).LoadSpecularFromFile("images/sample_spec.png");
	ECS::Get<Material>(11).Tex1Str = 0.f;
	ECS::Get<Material>(11).Tex2Str = 1.f;
	ECS::Get<Material>(11).SetAll(1.f);
	ECS::Get<PhysicsBody>(11).SetBox(ECS::Get<Transform>(10).GetPosition(), 8, 2, 8);
	ECS::Get<PhysicsBody>(11).SetBodyType(0);
	ECS::Get<PhysicsBody>(11).SetFriction(0.0f);
	ECS::Get<PhysicsBody>(11).SetMass(0.01f);
	ECS::Get<PhysicsBody>(11).SetGravityScale(0.f);

	
	
}
bool Moving = false;
bool Rotating = false;
bool Moving2 = false;
bool Rotating2 = false;
void TankScene::Update()
{

#pragma region P1Controls
	//print score
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_P) == GLFW_PRESS)
	{
		std::cout << "Player 1 score: " << P1Score << "\nPlayer 2 Score: " << P2Score << std::endl;
	}

	
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (!Rotating)
			ECS::Get<PhysicsBody>(1).ApplyForce(ECS::Get<TankData>(1).GetForward() * 10.f);

		Moving = true;

	}

	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_W) == GLFW_RELEASE)
		Moving = false;
	
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (!Rotating)
			ECS::Get<PhysicsBody>(1).ApplyForce(-ECS::Get<TankData>(1).GetForward() * 10.f);

		Moving = true;
	}
	
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_S) == GLFW_RELEASE)
		Moving = false;

	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_E) == GLFW_PRESS) //shoot : )
	{
		if (!ECS::Get<TankData>(1).m_BulletShot)
		{
			ECS::Get<Transform>(4).SetPosition(ECS::Get<Transform>(1).GetPosition() + ECS::Get<TankData>(1).GetForward() * 2.f);
			ECS::Get<PhysicsBody>(4).SetVelocity(ECS::Get<TankData>(1).GetForward() * 20.f);
			ECS::Get<TankData>(1).m_BulletShot = true;
		}
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		if (!Moving)
		ECS::Get<TankData>(1).Rotate(180 * Timer::dt);
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_A) == GLFW_RELEASE)
		Rotating = false;

	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		if(!Moving)
		ECS::Get<TankData>(1).Rotate(-180 * Timer::dt);
	}

	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_D) == GLFW_RELEASE)
		Rotating = false;

#pragma endregion
	
#pragma region P2Controls
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_I) == GLFW_PRESS)
	{
		if (!Rotating2)
			ECS::Get<PhysicsBody>(2).ApplyForce(ECS::Get<TankData>(2).GetForward() * 10.f);

		Moving2 = true;

	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_I) == GLFW_RELEASE)
		Moving2 = false;

	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_K) == GLFW_PRESS)
	{
		if (!Rotating2)
			ECS::Get<PhysicsBody>(2).ApplyForce(-ECS::Get<TankData>(2).GetForward() * 10.f);

		Moving2 = true;
	}

	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_K) == GLFW_RELEASE)
		Moving2 = false;

	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_O) == GLFW_PRESS) //shoot : )
	{

		if (!ECS::Get<TankData>(2).m_BulletShot)
		{
			ECS::Get<Transform>(5).SetPosition(ECS::Get<Transform>(2).GetPosition() + ECS::Get<TankData>(2).GetForward() * 2.f);
			ECS::Get<PhysicsBody>(5).SetVelocity(ECS::Get<TankData>(2).GetForward() * 20.f);
			ECS::Get<TankData>(2).m_BulletShot = true;
		}
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_J) == GLFW_PRESS)
	{
		if (!Moving2)
			ECS::Get<TankData>(2).Rotate(180 * Timer::dt);
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_J) == GLFW_RELEASE)
		Rotating2 = false;

	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_L) == GLFW_PRESS)
	{
		if (!Moving2)
			ECS::Get<TankData>(2).Rotate(-180 * Timer::dt);
	}

	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_L) == GLFW_RELEASE)
		Rotating2 = false;

	

#pragma endregion

//Since collision is buggy for now, walls won't be done through AABB since they don't move

#pragma region OutsideWall
	//for tanks
	if (ECS::Get<Transform>(1).GetPosition().z > 48)
		ECS::Get<Transform>(1).SetPosition(glm::vec3(ECS::Get<Transform>(1).GetPosition().x, 2.f, 48.f));
	if (ECS::Get<Transform>(2).GetPosition().z > 48)
		ECS::Get<Transform>(2).SetPosition(glm::vec3(ECS::Get<Transform>(2).GetPosition().x, 2.f, 48.f));
	if (ECS::Get<Transform>(1).GetPosition().z < -48)
		ECS::Get<Transform>(1).SetPosition(glm::vec3(ECS::Get<Transform>(1).GetPosition().x, 2.f, -48.f));
	if (ECS::Get<Transform>(2).GetPosition().z < -48)
		ECS::Get<Transform>(2).SetPosition(glm::vec3(ECS::Get<Transform>(2).GetPosition().x, 2.f, -48.f));
	if (ECS::Get<Transform>(1).GetPosition().x > 25)
		ECS::Get<Transform>(1).SetPosition(glm::vec3(25, 2, ECS::Get<Transform>(1).GetPosition().z));
	if (ECS::Get<Transform>(2).GetPosition().x > 25)
		ECS::Get<Transform>(2).SetPosition(glm::vec3(25, 2, ECS::Get<Transform>(2).GetPosition().z));
	if (ECS::Get<Transform>(1).GetPosition().x < -25)
		ECS::Get<Transform>(1).SetPosition(glm::vec3(-25, 2, ECS::Get<Transform>(1).GetPosition().z));
	if (ECS::Get<Transform>(2).GetPosition().x < -25)
		ECS::Get<Transform>(2).SetPosition(glm::vec3(-25, 2, ECS::Get<Transform>(2).GetPosition().z));
	//for bullets
	if (ECS::Get<Transform>(4).GetPosition().z > 48)
	{
		glm::vec3 velocity = glm::vec3(ECS::Get<PhysicsBody>(4).GetVelocity());
		velocity.z = -velocity.z;
		ECS::Get<PhysicsBody>(4).SetVelocity(velocity);
		ECS::Get<TankData>(1).m_BounceCount++;
	}
	if (ECS::Get<Transform>(5).GetPosition().z > 48)
	{
		glm::vec3 velocity = glm::vec3(ECS::Get<PhysicsBody>(5).GetVelocity());
		velocity.z = -velocity.z;
		ECS::Get<PhysicsBody>(5).SetVelocity(velocity);
		ECS::Get<TankData>(2).m_BounceCount++;
	}
	if (ECS::Get<Transform>(4).GetPosition().z < -48)
	{
		glm::vec3 velocity = glm::vec3(ECS::Get<PhysicsBody>(4).GetVelocity());
		velocity.z = -velocity.z;
		ECS::Get<PhysicsBody>(4).SetVelocity(velocity);
		ECS::Get<TankData>(1).m_BounceCount++;
	}
	if (ECS::Get<Transform>(5).GetPosition().z < -48)
	{
		glm::vec3 velocity = glm::vec3(ECS::Get<PhysicsBody>(5).GetVelocity());
		velocity.z = -velocity.z;
		ECS::Get<PhysicsBody>(5).SetVelocity(velocity);
		ECS::Get<TankData>(2).m_BounceCount++;
	}
	if (ECS::Get<Transform>(4).GetPosition().x > 25)
	{
		glm::vec3 velocity = glm::vec3(ECS::Get<PhysicsBody>(4).GetVelocity());
		velocity.x = -velocity.x;
		ECS::Get<PhysicsBody>(4).SetVelocity(velocity);
		ECS::Get<TankData>(1).m_BounceCount++;
	}
	if (ECS::Get<Transform>(5).GetPosition().x > 25)
	{
		glm::vec3 velocity = glm::vec3(ECS::Get<PhysicsBody>(5).GetVelocity());
		velocity.x = -velocity.x;
		ECS::Get<PhysicsBody>(5).SetVelocity(velocity);
		ECS::Get<TankData>(2).m_BounceCount++;
	}
	if (ECS::Get<Transform>(4).GetPosition().x < -25)
	{
		glm::vec3 velocity = glm::vec3(ECS::Get<PhysicsBody>(4).GetVelocity());
		velocity.x = -velocity.x;
		ECS::Get<PhysicsBody>(4).SetVelocity(velocity);
		ECS::Get<TankData>(1).m_BounceCount++;
	}
	if (ECS::Get<Transform>(5).GetPosition().x < -25)
	{
		glm::vec3 velocity = glm::vec3(ECS::Get<PhysicsBody>(5).GetVelocity());
		velocity.x = -velocity.x;
		ECS::Get<PhysicsBody>(5).SetVelocity(velocity);
		ECS::Get<TankData>(2).m_BounceCount++;
	}


#pragma endregion

#pragma region InsideWalls
	PhysicsBody tank1 = ECS::Get<PhysicsBody>(1);
	PhysicsBody tank2 = ECS::Get<PhysicsBody>(2);

	//for tanks
	if (PhysicsSystem::AABB(tank1, ECS::Get<PhysicsBody>(10)))
	{
		//tank 1 colliding with inside wall
		ECS::Get<Transform>(1).SetPosition(-ECS::Get<PhysicsBody>(1).GetVelocity() * 0.1f + ECS::Get<PhysicsBody>(1).GetPosition());
		
	
		
	}

	//for tanks
	if (PhysicsSystem::AABB(ECS::Get<PhysicsBody>(1), ECS::Get<PhysicsBody>(11)))
	{
		//tank 1 colliding with a wall
		ECS::Get<Transform>(1).SetPosition(-ECS::Get<PhysicsBody>(1).GetVelocity() * 0.1f + ECS::Get<PhysicsBody>(1).GetPosition());
	}

	//for tanks
	if (PhysicsSystem::AABB(tank2, ECS::Get<PhysicsBody>(10)))
	{
		//tank 1 colliding with inside wall
		ECS::Get<Transform>(2).SetPosition(-ECS::Get<PhysicsBody>(2).GetVelocity() * 0.1f + ECS::Get<PhysicsBody>(2).GetPosition());
		

	}

	//for tanks
	if (PhysicsSystem::AABB(ECS::Get<PhysicsBody>(2), ECS::Get<PhysicsBody>(11)))
	{
		//tank 1 colliding with a wall
		ECS::Get<Transform>(2).SetPosition(-ECS::Get<PhysicsBody>(2).GetVelocity() * 0.1f + ECS::Get<PhysicsBody>(2).GetPosition());
	}
	bool didCollide = false;
	//for tanks
	if (PhysicsSystem::AABB(ECS::Get<PhysicsBody>(4), ECS::Get<PhysicsBody>(10)))
	{
		//bullet 1 colliding with a wall
		glm::vec3 velocity = ECS::Get<PhysicsBody>(4).GetVelocity();
		glm::vec3 position = ECS::Get<Transform>(4).GetPosition();
		if (position.x > 6 && position.x < 14 && position.z <= 4.1f) //right wall
		{
			velocity = ECS::Get<PhysicsBody>(4).GetVelocity();
			velocity.z = -velocity.z;
		
		}
		if (position.x > 6 && position.x < 14 && position.z <= -4.1f) //left wall
		{
			velocity = ECS::Get<PhysicsBody>(4).GetVelocity();
			
			velocity.x = -velocity.x;		
		}
		if (position.z > -4 && position.z < 4.f && position.x >= 6.1f)
		{
			velocity = ECS::Get<PhysicsBody>(4).GetVelocity();
			
			velocity.x = -velocity.x;
		}
		if (position.z > -4 && position.z < 4.f && position.x >= 14.1f)
		{
			velocity = ECS::Get<PhysicsBody>(4).GetVelocity();
			
			velocity.z = -velocity.z;
		}
		
		didCollide = true;
		//std::cout << didCollide;
		ECS::Get<PhysicsBody>(4).SetVelocity(velocity);
	}
	

	
	//for tanks
	
	if (PhysicsSystem::AABB(ECS::Get<PhysicsBody>(4), ECS::Get<PhysicsBody>(11)))
	{//bullet 1 colliding with a wall
		glm::vec3 velocity = ECS::Get<PhysicsBody>(4).GetVelocity();
		glm::vec3 position = ECS::Get<Transform>(4).GetPosition();
		
		if (position.x > -6 && position.x < -14 && position.z <= -9.1f) //left wall
		{
			velocity = ECS::Get<PhysicsBody>(4).GetVelocity();
			velocity.x = -velocity.x;
		
		}
		else if (position.z > -9 && position.z < -1.f && position.x >= -6.1f)
		{
			velocity = ECS::Get<PhysicsBody>(4).GetVelocity();
			velocity.x = -velocity.x;
			
		}
		else if (position.z > -9 && position.z < -1.f && position.x >= -14.1f)
		{
			velocity = ECS::Get<PhysicsBody>(4).GetVelocity();
			velocity.z = -velocity.z;
		}
		else if (position.x > -6 && position.x < -14 && position.z <= -1.1f) //right wall
		{
			velocity = ECS::Get<PhysicsBody>(4).GetVelocity();

			velocity.z = -velocity.z;
		}

		ECS::Get<PhysicsBody>(4).SetVelocity(velocity);
	}

	if (PhysicsSystem::AABB(ECS::Get<PhysicsBody>(5), ECS::Get<PhysicsBody>(10)))
	{
		//bullet 1 colliding with a wall
		glm::vec3 velocity = ECS::Get<PhysicsBody>(5).GetVelocity();
		glm::vec3 position = ECS::Get<Transform>(5).GetPosition();
		if (position.x > 6 && position.x < 14 && position.z <= 4.1f) //right wall
		{
			velocity = ECS::Get<PhysicsBody>(5).GetVelocity();
			velocity.z = -velocity.z;
		}
		if (position.x > 6 && position.x < 14 && position.z <= -4.1f) //left wall
		{
			velocity = ECS::Get<PhysicsBody>(5).GetVelocity();
			velocity.x = -velocity.x;
		}
		if (position.z > -4 && position.z < 4.f && position.x >= 6.1f)
		{
			velocity = ECS::Get<PhysicsBody>(5).GetVelocity();
			velocity.x = -velocity.x;
		}
		if (position.z > -4 && position.z < 4.f && position.x >= 14.1f)
		{
			velocity = ECS::Get<PhysicsBody>(5).GetVelocity();
			velocity.z = -velocity.z;
		}

		ECS::Get<PhysicsBody>(5).SetVelocity(velocity);
	}

	if (PhysicsSystem::AABB(ECS::Get<PhysicsBody>(5), ECS::Get<PhysicsBody>(11)))
	{//bullet 1 colliding with a wall
		glm::vec3 velocity = ECS::Get<PhysicsBody>(5).GetVelocity();
		glm::vec3 position = ECS::Get<Transform>(5).GetPosition();

		if (position.x > -6 && position.x < -14 && position.z <= -9.1f) //left wall
		{
			velocity = ECS::Get<PhysicsBody>(5).GetVelocity();
			velocity.x = -velocity.x;

		}
		else if (position.z > -9 && position.z < -1.f && position.x >= -6.1f)
		{
			velocity = ECS::Get<PhysicsBody>(5).GetVelocity();
			velocity.x = -velocity.x;

		}
		else if (position.z > -9 && position.z < -1.f && position.x >= -14.1f)
		{
			velocity = ECS::Get<PhysicsBody>(5).GetVelocity();
			velocity.z = -velocity.z;
		}
		else if (position.x > -6 && position.x < -14 && position.z <= -1.1f) //right wall
		{
			velocity = ECS::Get<PhysicsBody>(5).GetVelocity();

			velocity.z = -velocity.z;
		}

		ECS::Get<PhysicsBody>(5).SetVelocity(velocity);
	}
	
	if (PhysicsSystem::AABB(ECS::Get<PhysicsBody>(1), ECS::Get<PhysicsBody>(2))) //tank collide with eachother
	{
		ECS::Get<Transform>(1).SetPosition(-ECS::Get<PhysicsBody>(1).GetVelocity() * 0.1f + ECS::Get<PhysicsBody>(1).GetPosition());
		ECS::Get<Transform>(2).SetPosition(-ECS::Get<PhysicsBody>(2).GetVelocity() * 0.1f + ECS::Get<PhysicsBody>(2).GetPosition());
	}

	int EntIds[8] = {4,1,4,2,5,1,5,2};
	//need 4 1, 4 2, 5 1, 5 2
	for (int i = 0; i < 8; i = i + 2)
	{
		if (PhysicsSystem::AABB(ECS::Get<PhysicsBody>(EntIds[i]), ECS::Get<PhysicsBody>(EntIds[i + 1])))
		{
			if (EntIds[i + 1] == 1)
			{
				ECS::Get<Transform>(1).SetPosition(glm::vec3(-10.f, 2.f, -15.f));
				P2Score++;
			}
			else if (EntIds[i + 1] == 2)
			{
				ECS::Get<Transform>(2).SetPosition(glm::vec3(10.f, 2.f, 15.f));
				P1Score++;
			}
		}
	}

	if (PhysicsSystem::AABB(ECS::Get<PhysicsBody>(4), ECS::Get<PhysicsBody>(5)))
	{
		
		//basically for some reason it doesn't let you shoot after the bullets collide but I can detect if they work
		//I am opting to give both players a point when this happens :)
		P1Score++;
		P2Score++;
	}

	if (ECS::Get<TankData>(1).m_BounceCount > 2)
	{
		ECS::Get<Transform>(4).SetPosition(glm::vec3(0.f, 100.f, 0.f));
		ECS::Get<TankData>(1).m_BulletShot = false;
		ECS::Get<TankData>(1).m_BounceCount = 0;
	}

	if (ECS::Get<TankData>(2).m_BounceCount > 2)
	{
		ECS::Get<Transform>(5).SetPosition(glm::vec3(0.f, 100.f, 0.f));
		ECS::Get<TankData>(2).m_BulletShot = false;
		ECS::Get<TankData>(2).m_BounceCount = 0;
	}

	

#pragma endregion

	
}
*/