//
// Created by tiyst on 16/11/2019.
//

#ifndef SNAKERINO_GAMEBOARD_HPP
#define SNAKERINO_GAMEBOARD_HPP

#include "Snake.cpp"

class gameBoard {
private:
	static int const GRID_SIZE = 20;
	unsigned const int windowWidth, windowHeight, fps;
	sf::RenderWindow window;


//	int score; //Score should be in player class as it can be used as currency

	std::vector<sf::Drawable*> drawables;
	void drawDrawables();


	GameObject* grid[GRID_SIZE][GRID_SIZE];

public:
	gameBoard(unsigned int fps, unsigned int width, unsigned int height);
	void initGameBoard();
	void drawBoard();
	void addDrawable(sf::Drawable* drawable);


	bool isActive() {
		return window.isOpen();
	}

	sf::RenderWindow* getWindow() {
		return &window;
	}

};


#endif //SNAKERINO_GAMEBOARD_HPP
