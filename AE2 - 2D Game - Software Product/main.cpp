#undef main
#include <SDL.h>
#include "Game.h"

int main(int argc, char* argv[])
{
	Game* game;
	
	do
	{
		game = new Game();
		if (nullptr == game) return -1;
		game->Update();
	} while (game->m_replayGame);

	delete game;
	game = nullptr;

	return 0;
}
