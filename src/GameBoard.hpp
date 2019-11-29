//
// Created by tiyst on 16/11/2019.
//

#ifndef SNAKERINO_GAMEBOARD_HPP
#define SNAKERINO_GAMEBOARD_HPP

#include "Snake.cpp"
#include "GameGrid.cpp"

class GameBoard {
public:
	static const unsigned int GRID_SIZE = 20;
	GameBoard(ResourceLoader &rl);
	void initGameBoard();
	void addDrawable(sf::Drawable* drawable);
	void removeDrawable(int index);
	void removeDrawable(sf::Drawable* drawable);


	void pollInput(sf::Keyboard::Key key) {
        switch (key) {
            case sf::Keyboard::Up:
                break;
            case sf::Keyboard::Down:
                break;
            case sf::Keyboard::Right:
                break;
            case sf::Keyboard::Left:
                break;

            default: break;
        }
	}

	void drawBoard(sf::RenderWindow& target);

private:
    sf::Sprite gridSprite;

    std::vector<sf::Drawable*> drawables;
    void drawDrawables(sf::RenderWindow& target);
    void drawGrid(sf::RenderWindow& target);

    GameObject* grid[GRID_SIZE][GRID_SIZE];

};


#endif //SNAKERINO_GAMEBOARD_HPP
