//
// Created by tiyst on 16/11/2019.
//

#include "GameBoard.hpp"

GameBoard::GameBoard(ResourceLoader &rl) {
	initGameBoard();
}

void GameBoard::initGameBoard() {
	ResourceLoader &rl = ResourceLoader::getInstance();
	rl.addTexture("Snake", "../res/Snake/snake.jpg");

	sf::Texture* tx = rl.addTexture("gridSquare", "../res/Snake/gridSquare.jpg");
	gridSprite.setTexture(*tx);

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

void GameBoard::drawGrid(sf::RenderWindow &target) {
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            gridSprite.setPosition(x*50, y*50);
            gridSprite.setScale(0.5,0.5);
            target.draw(gridSprite);
        }
    }
}

void GameBoard::drawDrawables(sf::RenderWindow& target) {
    for (auto & drawable : drawables) {
        target.draw(*drawable);
    }
}

void GameBoard::drawBoard(sf::RenderWindow &target) {
    drawGrid(target);
    drawDrawables(target);
}


