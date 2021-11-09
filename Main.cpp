//
// main.cpp
//	Entry point of trip-game
//

#include "game.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	return Game::Instance()->Run();
}
