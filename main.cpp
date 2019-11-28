#include <SFML/Graphics.hpp>
#include "src/Utilities/ResourceLoader.h"
#include "src/GameBoard.cpp"
#include "src/Game.cpp"



int main() {
	ResourceLoader &rl = ResourceLoader::getInstance();
	rl.initResourceLoader();
	Game* game = new Game(rl);
	game->run();

	return 0;
}