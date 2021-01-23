
#include <ElementEngine.h>
#include <TestScene.h>
#include <MakePrefabHere_smile.h>
int main()
{
	Game game;
	game.AddScene(new Game_Scene());
	//game.AddScene(new PrefabMakeScene());
	game.InitGame(0);
	return 0;
}