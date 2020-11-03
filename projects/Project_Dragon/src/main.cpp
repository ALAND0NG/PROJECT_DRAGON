#include <ElementEngine.h>

int main()
{
	Game game;

	game.AddScene(new TankScene());

	game.InitGame(0);

	return 0;
}