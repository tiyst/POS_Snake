//
// Created by tiyst on 16/11/2019.
//

#ifndef SNAKERINO_GAMEBOARD_HPP
#define SNAKERINO_GAMEBOARD_HPP

#include "Snake.cpp"

class GameBoard : public sf::Drawable {
public:
	static const unsigned int GRID_SIZE = 20;
	GameBoard(ResourceLoader &rloader);
	void initGameBoard();
	void addDrawable(sf::Drawable* drawable);
	void removeDrawable(int index);
	void removeDrawable(sf::Drawable* drawable);

	void setSnake(Snake* snek) {
		snake = snek;
	}

	void pollInput(sf::Keyboard::Key key);
	void tick();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


private:
    SnakePiece* gridTile; // TODO make grid a gameObject?? maybe
	Snake* snake;
	ResourceLoader &rl;


    std::vector<sf::Drawable*> drawables;
    void drawDrawables(sf::RenderTarget& target) const;
    void drawGrid(sf::RenderTarget& target) const;
    void drawSnake(sf::RenderTarget& target) const;

    GameObject* grid[GRID_SIZE][GRID_SIZE];

};


#endif //SNAKERINO_GAMEBOARD_HPP
