//
// Created by tiyst on 17/11/2019.
//

#include "Snake.hpp"

Snake::Snake(int length, int x, int y) {
    //todo
}

void Snake::move() {
	sf::Vector2i firstPiecePos = snakePieces.at(0)->getCoordinates();
	sf::Vector2i change(0,0);

	switch(direction) {
		case UP: change.x -= 1;
			break;
		case DOWN: change.x += 1;
			break;
		case RIGHT: change.y += 1;
			break;
		case LEFT: change.y -= 1;
			break;
	}
	snakePieces.at(snakePieces.size() - 1)->changeCoordinates(firstPiecePos + change);
}

void Snake::addPiece() {
	sf::Vector2i firstPiecePos = snakePieces.at(0)->getCoordinates();
	sf::Vector2i change(0,0);

	switch(direction) {
		case UP: change.x -= 1;
			break;
		case DOWN: change.x += 1;
			break;
		case RIGHT: change.y += 1;
			break;
		case LEFT: change.y -= 1;
			break;
	}
	auto* add = new SnakePiece(firstPiecePos + change);
	snakeLength++;
	snakePieces.insert(snakePieces.begin(),add); //TODO <- do this
}

void Snake::changeDirection(Snake::DIRECTION dir) {
	if (direction % 2 != dir % 2) {
		direction = dir;
	} else { //TODO remove this part in release
		std::cerr << "You can't change direction to opposite of the current one\n";
	}
}

