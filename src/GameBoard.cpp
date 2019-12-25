//
// Created by tiyst on 16/11/2019.
//

#include "GameBoard.hpp"

GameBoard::GameBoard() : rl(ResourceLoader::getInstance()) {
	initGameBoard();
}

void GameBoard::initGameBoard() {
	ResourceLoader &rl = ResourceLoader::getInstance();

	rl.addTexture("gridSquare", "../res/Snake/gridSquare.jpg");
	gridTile = new SnakePiece(0, 0);
	gridTile->setTexture(rl.getTexture("gridSquare"));
	gridTile->setSize(rl.getSquareSize(),rl.getSquareSize());

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

void GameBoard::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	drawGrid(target);
	drawDrawables(target);
}


