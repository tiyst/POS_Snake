#include <SFML/Graphics.hpp>
#include "src/Utilities/ResourceLoader.h"
#include "src/GameBoard.cpp"
#include "src/Game.cpp"

int main() {
	ResourceLoader &rl = ResourceLoader::getInstance();
	rl.initResourceLoader();
	Game* game = new Game(rl, 60, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	game->run();

	return 0;
}