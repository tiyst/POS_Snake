//
// Created by tiyst on 16/11/2019.
//

#ifndef SNAKERINO_SNAKE_HPP
#define SNAKERINO_SNAKE_HPP

#include "snakePiece.cpp"

class Snake {
public:
	enum DIRECTION {UP, RIGHT, LEFT, DOWN};
	void move();
	void addPiece();

private:
	DIRECTION direction;
	int length;
	std::vector<snakePiece> snakePieces;


};

#endif //SNAKERINO_SNAKE_HPP
