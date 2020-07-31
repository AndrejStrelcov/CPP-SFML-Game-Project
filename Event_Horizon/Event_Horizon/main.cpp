#include <iostream>
#include <time.h>
#include "game.h"

using namespace sf;

int main()
{
	//Randomizer
	srand(static_cast<unsigned>(time(0)));

	//Start
	Game game;
	game.run();

	//End
	return 0;
}