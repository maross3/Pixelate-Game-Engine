#include <iostream>
#include <SDL.h>
#include <imgui/imgui.h>
#include <sol/sol.hpp>

#include "Game/Game.h"

int main(int argc, char* argv[])
{
	Game game;
	game.Initialize();
	game.Run();
	game.Destroy();

	return 0;
}
