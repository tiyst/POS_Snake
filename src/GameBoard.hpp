//
// Created by tiyst on 16/11/2019.
//

#ifndef SNAKERINO_GAMEBOARD_HPP
#define SNAKERINO_GAMEBOARD_HPP

#include "Snake.cpp"
#include "GameGrid.cpp"

class GameBoard : public sf::Drawable {
public:
	static const unsigned int GRID_SIZE = 20;
	GameBoard(unsigned int fps, unsigned int width, unsigned int height);
	void initGameBoard();
	void drawBoard();
	void addDrawable(sf::Drawable* drawable);
	void removeDrawable(int index);
	void removeDrawable(sf::Drawable* drawable);

	bool isActive() {
		return window.isOpen();
	}

	sf::RenderWindow* getWindow() {
		return &window;
	}

private:
	unsigned const int windowWidth, windowHeight, fps;
	sf::RenderWindow window;
	sf::Sprite gridSprite;
//	int score; //Score should be in player class as it can be used as currency

	std::vector<sf::Drawable*> drawables;
	void drawDrawables();
	void drawGrid();

	GameGrid* gameGrid;
	GameObject* grid[GRID_SIZE][GRID_SIZE];
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {

	}
};


#endif //SNAKERINO_GAMEBOARD_HPP
