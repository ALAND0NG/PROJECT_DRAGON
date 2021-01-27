#include "IMGUIManager.h"
#include <AssetLoader.h>
#include <BackEnd.h>
std::vector<std::function<void()>> IMGUIManager::imGuiCallbacks;

void IMGUIManager::Init()
{
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();

	// Enable keyboard navigation
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	// Allow docking to our window
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	// Allow multiple viewports (so we can drag ImGui off our window)
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	// Allow our viewports to use transparent backbuffers
	io.ConfigFlags |= ImGuiConfigFlags_TransparentBackbuffers;

	// Set up the ImGui implementation for OpenGL
	ImGui_ImplGlfw_InitForOpenGL(BackEnd::m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 410");

	// Dark mode FTW
	ImGui::StyleColorsDark();

	// Get our imgui style
	ImGuiStyle& style = ImGui::GetStyle();
	//style.Alpha = 1.0f;
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 0.8f;
	}
}
int EntId = 0;
float Position[3];
void IMGUIManager::Update()
{
	// Implementation new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	// ImGui context new frame
	ImGui::NewFrame();


	//Im not even going to deny it, this sucks
	if (ImGui::Begin("Node Editor")) {

		//ImGui::ShowDemoWindow();
		ImGui::InputInt("Entity Number", &EntId);
		ImGui::InputFloat3("Position", Position, 0, 0);
		
		if (ImGui::Button("Apply Physics Body Transform"))
		{
			//apply the transform
			btTransform bodyTrns = ECS::Get<PhysicsBody>(EntId).GetBody()->getCenterOfMassTransform();
			bodyTrns.setOrigin(btVector3(Position[0], Position[1], Position[2]));
			ECS::Get<PhysicsBody>(EntId).GetBody()->setWorldTransform(bodyTrns);
		}
		if (ImGui::Button("Apply Transform (Position)"))
		{
			ECS::Get<Transform>(EntId).SetPosition(glm::vec3(Position[0], Position[1], Position[2]));
		}
		if (ImGui::Button("Create New Entity"))
		{
			int HighestEntity = ECS::GetSize();
			ECS::Create(HighestEntity);
			ECS::Add<Transform>(HighestEntity);
			ECS::Add<Material>(HighestEntity);
			ECS::Add<Mesh>(HighestEntity);
			ECS::Get<Mesh>(HighestEntity) = AssetLoader::GetMesh()[0];
			ECS::Get<Material>(HighestEntity) = AssetLoader::GetMat()[0];

		}

		if (ImGui::Button("Apply Scale"))
		{
			ECS::Get<Transform>(EntId).SetScale(glm::vec3(Position[0], Position[1], Position[2]));
		}




		//Button to save current scene starting from and including entity #2 since #0 & #1 are camera and plane
		if (ImGui::Button("Save Room"))
		{
			//Add implementation here
		}

		ImGui::End();
	}



	

	// Make sure ImGui knows how big our window is
	ImGuiIO& io = ImGui::GetIO();
	int width{ 0 }, height{ 0 };
	glfwGetWindowSize(BackEnd::m_Window, &width, &height);
	io.DisplaySize = ImVec2((float)width, (float)height);

	// Render all of our ImGui elements
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// If we have multiple viewports enabled (can drag into a new window)
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		// Update the windows that ImGui is using
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		// Restore our gl context
		glfwMakeContextCurrent(BackEnd::m_Window);
	}
}
