//
// Created by tiyst on 23/11/2019.
//

#ifndef SNAKERINO_GAME_HPP
#define SNAKERINO_GAME_HPP


class Game {

public:
	Game(ResourceLoader &rl, unsigned int fps, unsigned int width, unsigned int height);
	~Game();

	void run();


private:
    GameBoard* board;
    ResourceLoader &rl;
    unsigned const int fps, windowHeight, windowWidth;

	sf::RenderWindow renderWindow;
};


#endif //SNAKERINO_GAME_HPP
