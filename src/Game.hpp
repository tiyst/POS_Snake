//
// Created by tiyst on 23/11/2019.
//

#ifndef SNAKERINO_GAME_HPP
#define SNAKERINO_GAME_HPP

#include "Network/effectPacket.hpp"
#include <thread>

class Game {

public:
	enum GAMESTATE {
		NOT_STARTED,
		IN_PROGRESS,
		FINISHED
	};

	//IDs of game effects (easy to parse out of packet)
	enum GAME_EFFECT {
	    APPLE = 100,
		WALL = 101,
		SPEED = 102,
		INVISIBILITY = 103,
		SNAKE_MOVE = 104
	};

	Game(unsigned int fps);
	~Game();

	void run();

private:
	ResourceLoader &rl;
	GameBoard* board;
    Snake* snake;
    GameObject* apple;
    std::vector<GameObject*> walls;

    //"Delays" input so the snake won't be able to turn inside itself
	sf::Clock turningClock;
	sf::Clock gameRateClock;
	bool gameStarted, isSpedUp, isInvisible, isServer;
    int tickTimeDelay;
    unsigned const int fps;

	sf::RenderWindow renderWindow;

	//networking
	sf::TcpSocket socket;
	std::thread listeningThread;

	void tick();
	void pollKeyboardInput(sf::Keyboard::Key key);
	void pollMouseInput(sf::Mouse::Button button, sf::Vector2i pos);
	void startGame();
	void endGame();
	void drawCycle();
	void changeApplePosition();

	void addWall(sf::Vector2i pos);
	void triggerSpeed();
	void triggerInvisibility();

	bool isPositionTaken(int x, int y);
	bool isPositionTaken(sf::Vector2i posCoord);

	void setTickTimeDelay(int delay);

	void connect();
	void sendPacket(GAME_EFFECT ef, int x, int y);
	void receivePacket(sf::Packet& packet);
	void moveSnake();
	void moveApple();

	void listen();
};


#endif //SNAKERINO_GAME_HPP
