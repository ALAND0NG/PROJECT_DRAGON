#include "Game.h"
#include "Shader.h"


#include "GLM/glm.hpp"

Game game;

int main()
{
	game.Init();

	game.Update(); //begins the update, this function has a loop that runs while game is open

	return 0;
}

