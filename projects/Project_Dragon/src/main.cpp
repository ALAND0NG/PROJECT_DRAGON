#include <ElementEngine.h>
#include <TestScene.h>
#include <MakePrefabHere_smile.h>
int main()
{
	Game game;
	game.AddScene(new TestScene());
	game.AddScene(new PrefabMakeScene());
	game.InitGame(1);
	return 0;
}