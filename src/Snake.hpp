//
// Created by tiyst on 16/11/2019.
//

#ifndef SNAKERINO_SNAKE_HPP
#define SNAKERINO_SNAKE_HPP

#include "GameObjects/SnakePiece.cpp"
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
	void changeStatus(STATUS stat);
	void triggerInvis();
	std::vector<SnakePiece*>* getSnake();
	sf::Vector2i getHeadCoordinates();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		if (!invisible) {
			for (auto snakePiece : snakePieces) {
				target.draw(*snakePiece, states);
			}
		}
	}

private:
	DIRECTION direction = DIRECTION::RIGHT; //default is right
	STATUS status = STATUS::STOPPED;

	int snakeLength;
	bool invisible;
	std::vector<SnakePiece*> snakePieces;

};

#endif //SNAKERINO_SNAKE_HPP
