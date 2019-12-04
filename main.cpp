#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <thread>
#include "src/Utilities/ResourceLoader.h"
#include "src/GameBoard.cpp"
#include "src/Game.cpp"

void* connect();

int main() {

    //TODO Connection and choose to be snek or not snek
    const unsigned int port = 10001;

    std::thread connectionThread(connect);
    connectionThread.join();

    ResourceLoader &rl = ResourceLoader::getInstance();
    rl.initResourceLoader();
    Game* game = new Game(rl, 60, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	game->run();

	return 0;
}


void* connect() {
    char cs;
    std::cout << "Do you want to run as client (c) or server (s)?\n";
    std::cin  >> cs;

}
