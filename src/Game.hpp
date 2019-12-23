//
// Created by tiyst on 23/11/2019.
//

#ifndef SNAKERINO_GAME_HPP
#define SNAKERINO_GAME_HPP


class Game {

public:
	Game(unsigned int fps, unsigned int width, unsigned int height);
	~Game();

	void run();

private:
	ResourceLoader &rl;
	GameBoard* board;
    Snake* snake;
    GameObject* apple;

    sf::Clock clock;
    bool gameStarted;
    int tickTimeDelay;
    unsigned const int fps, windowHeight, windowWidth;

	sf::RenderWindow renderWindow;

	void tick();
	void pollInput(sf::Keyboard::Key key);
	void startGame();
	void endGame();
	void drawCycle();
	void changeApplePosition();

	void setTickTimeDelay(int delay);
};


#endif //SNAKERINO_GAME_HPP
