//
// Created by tiyst on 17/11/2019.
//

#include "Snake.hpp"

Snake::Snake(int length, int x, int y) {
	snakeLength = length;
	for (int i = 0; i < length; ++i) {
		snakePieces.push_back(new SnakePiece(x--,y));
	}
	direction = DIRECTION::RIGHT;
}

void Snake::move() {
	sf::Vector2i firstPiecePos = snakePieces.at(0)->getCoordinates();
	sf::Vector2i change(0,0);

	switch(direction) {
		case UP: change.y -= 1;
			break;
		case DOWN: change.y += 1;
			break;
		case RIGHT: change.x += 1;
			break;
		case LEFT: change.x -= 1;
			break;
	}
	SnakePiece *piece = snakePieces.at(snakePieces.size()-1);
	snakePieces.erase(snakePieces.begin() + (snakePieces.size()-1));
	piece->changeCoordinates(firstPiecePos + change);
	snakePieces.insert(snakePieces.begin(), piece);
}

void Snake::addPiece() {
	sf::Vector2i firstPiecePos = snakePieces.at(0)->getCoordinates();
	sf::Vector2i change(0,0);

	switch(direction) {
		case UP: change.y -= 1;
			std::cout << "Moving up\n";
			break;
		case DOWN: change.y += 1;
			std::cout << "Moving up\n";
			break;
		case RIGHT: change.x += 1;
			std::cout << "Moving up\n";
			break;
		case LEFT: change.x -= 1;
			std::cout << "Moving up\n";
			break;
	}
	auto* add = new SnakePiece(firstPiecePos + change);
	snakeLength++;
	snakePieces.insert(snakePieces.begin(), add);
}

void Snake::changeDirection(Snake::DIRECTION dir) {
	if (direction % 2 != dir % 2) { //I'm really proud about this tbh
		direction = dir;
	} else { //TODO remove this part in release
		std::cout << "You can't change direction to opposite of the current one\n";
	}
}

void Snake::changeStatus(Snake::STATUS stat) {
	status = stat;
}

sf::Vector2i Snake::getHeadCoordinates() {
	return snakePieces.at(0)->getCoordinates();
}

