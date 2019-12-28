//
// Created by tiyst on 23/11/2019.
//

#ifndef SNAKERINO_GAME_HPP
#define SNAKERINO_GAME_HPP


class Game {

public:
	enum GAMESTATE {
		NOT_STARTED,
		IN_PROGRESS,
		FINISHED
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

    sf::Clock clock;
    bool gameStarted;
    int tickTimeDelay;
    unsigned const int fps;

	sf::RenderWindow renderWindow;

	void tick();
	void pollKeyboardInput(sf::Keyboard::Key key);
	void pollMouseInput(sf::Mouse::Button button, sf::Vector2i pos);
	void startGame();
	void endGame();
	void drawCycle();
	void changeApplePosition();

	void addWall(sf::Vector2i pos);

	bool isPositionTaken(int x, int y);
	bool isPositionTaken(sf::Vector2i posCoord);

	void setTickTimeDelay(int delay);
};


#endif //SNAKERINO_GAME_HPP
