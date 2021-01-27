
#include <ElementEngine.h>
#include <TestScene.h>
#include <MakePrefabHere_smile.h>
#include <MainMenu.h>
#include <DeathScreen.h>
int main()
{
	Game game;
	game.AddScene(new MainMenu());
	game.AddScene(new Game_Scene());
	game.AddScene(new DeathScreen());
	game.AddScene(new PrefabMakeScene());
	game.m_SceneIndex = 0;
	game.InitGame(0);
	return 0;
}