#include <ElementEngine.h>
#include <TestScene.h>
int main()
{
	Game game;
	game.AddScene(new TestScene());
	game.InitGame(0);
	return 0;
}