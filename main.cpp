#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <thread>
#include "src/Utilities/ResourceLoader.h"
#include "src/GameBoard.cpp"
#include "src/Game.cpp"


std::string ipAddress;
const unsigned int port = 10001;

void* connect();

int main() {

    //TODO Connection and choose to be snek or not snek

    std::thread connectionThread(connect);
    connectionThread.join();

    ResourceLoader &rl = ResourceLoader::getInstance();
    Game* game = new Game(60, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	game->run();

	return 0;
}


void* connect() {
	char cs;

    std::cout << "Do you want to run as client (c) or server (s)?\n";
    std::cin  >> cs;

	if (cs == 'c') {
		std::cout << "Insert server's IP address.\n";
		std::cin >> ipAddress;

		sf::TcpSocket socket;
		sf::Socket::Status status = socket.connect(ipAddress, port);
		if (status != sf::Socket::Done) {
			// error...
		}
		char data[32] = "Hello World!";

		if (socket.send(data, 32) != sf::Socket::Done) {
			// error...
		}
	} else if (cs == 's'){
		sf::TcpListener listener;

		// bind the listener to a port
		if (listener.listen(port) != sf::Socket::Done) {
			// error...
		}

		// accept a new connection
		sf::TcpSocket socket;
		if (listener.accept(socket) != sf::Socket::Done) {
			// error...
		}

		char data[100];
		std::size_t received;

		if (socket.receive(data, 100, received) != sf::Socket::Done)
		{
			// error...
		}
		std::cout << "Received " << received << " bytes" << std::endl;


	} else {
		connect();
	}
}
