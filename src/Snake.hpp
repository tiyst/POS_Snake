//
// Created by tiyst on 16/11/2019.
//

#ifndef SNAKERINO_SNAKE_HPP
#define SNAKERINO_SNAKE_HPP

#include "SnakePiece.cpp"
#include "GameBoard.hpp"

class Snake : public sf::Drawable {
public:
	enum DIRECTION { UP, RIGHT, DOWN, LEFT };
	enum STATUS { ALIVE, CRASHED, STOPPED };

	Snake(int length, int x, int y);
	~Snake() {};

	void move();
	void addPiece();
	void changeDirection(DIRECTION dir);

private:
	DIRECTION direction = DIRECTION::RIGHT; //default is right
	STATUS status = STATUS::STOPPED;

	int snakeLength;
	std::vector<SnakePiece*> snakePieces;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		for (int i = 0; i < snakePieces.size(); i++) {
			target.draw(*snakePieces.at(i), states);
		}
     }

};

#endif //SNAKERINO_SNAKE_HPP
