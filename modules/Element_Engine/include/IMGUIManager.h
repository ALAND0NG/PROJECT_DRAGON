#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "InputHelpers.h"
static class IMGUIManager
{
public:
	static void Init();
	static void Update();//more shit to throw in the backend :)
	static std::vector<std::function<void()>> imGuiCallbacks; //dont feel like GetSet everytime for this
private:
	
};