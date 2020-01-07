#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <thread>
#include "src/Utilities/ResourceLoader.h"
#include "src/GameBoard.cpp"
#include "src/Game.cpp"

//debug includes
//#include <filesystem>
//namespace fs = std::__fs::filesystem;

void* connect();

int main() {
	//debugging why resources aren't loaded
//	std::cout << "Current path is " << fs::current_path() << '\n';

    Game* game = new Game(60);
	game->run();

	return 0;
}