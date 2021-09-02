#include <Windows.h>
#include "Enemy.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

#if _DEBUG
int main()
#else
INT WinMain(HINSTANCE, HINSTANCE, PSTR, INT)
#endif
{
	Game game;
	game.run(game);
	
	return 0;
}
