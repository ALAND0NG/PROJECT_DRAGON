#include "Input.h"
#include "Camera.h"
#include "entt.hpp"

void Input::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	
	double lastX = xpos;
	double lastY = ypos;

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	


	//ProcessMouseMovement(xoffset, yoffset);

	
}


