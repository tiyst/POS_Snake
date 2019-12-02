//
// Created by tiyst on 16/11/2019.
//

#include "GameBoard.hpp"

GameBoard::GameBoard(ResourceLoader &rloader) : rl(rloader){
	initGameBoard();
}

void GameBoard::initGameBoard() {
	ResourceLoader &rl = ResourceLoader::getInstance();
	rl.addTexture("Snake", "../res/Snake/snake.jpg");
	rl.addTexture("gridSquare", "../res/Snake/gridSquare.jpg");

	sf::Texture* tx = rl.getTexture("gridSquare");

	gridTile = new SnakePiece(0, 0);
	gridTile->setTexture(tx);

//	for (auto & i : grid) { //TODO Is explicit pointing to nullptr necessary?
//		for (auto & j : i) {
//			j = nullptr;
//		}
//	}
}

void GameBoard::addDrawable(sf::Drawable *drawable) {
	drawables.push_back(drawable);
}

void GameBoard::removeDrawable(int index) {
	drawables.erase(drawables.begin() + index);
}

void GameBoard::removeDrawable(sf::Drawable *drawable) {
	for (int i = 0; i < drawables.size(); i++) {
		if (drawables.at(i) == drawable) {
			drawables.erase(drawables.begin() + i);
			return;
		}
	}
}

void GameBoard::pollInput(sf::Keyboard::Key key) {
	switch (key) {
		case sf::Keyboard::Up: snake->changeDirection(Snake::DIRECTION::UP);
			break;
		case sf::Keyboard::Down: snake->changeDirection(Snake::DIRECTION::DOWN);
			break;
		case sf::Keyboard::Right: snake->changeDirection(Snake::DIRECTION::RIGHT);
			break;
		case sf::Keyboard::Left: snake->changeDirection(Snake::DIRECTION::LEFT);
			break;

		default: break;
	}
}

void GameBoard::tick() {
	//TODO check for collision / enlarge snake when apple
	snake->move();
}

void GameBoard::drawGrid(sf::RenderTarget &target) const {
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
			gridTile->changeCoordinates(x,y);
			target.draw(*gridTile);
        }
    }
}

void GameBoard::drawDrawables(sf::RenderTarget& target) const {
    for (auto & drawable : drawables) {
        target.draw(*drawable);
    }
}

void GameBoard::drawSnake(sf::RenderTarget &target) const {
	target.draw(*snake);
}

void GameBoard::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	drawGrid(target);
	drawDrawables(target);
	drawSnake(target);
}


