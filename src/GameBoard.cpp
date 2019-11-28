//
// Created by tiyst on 16/11/2019.
//

#include "GameBoard.hpp"

GameBoard::GameBoard(unsigned int fps, unsigned int width, unsigned int height)
		: fps(fps), windowWidth(width), windowHeight(height) {
	initGameBoard();
}

void GameBoard::initGameBoard() {
	window.create(sf::VideoMode(windowWidth, windowHeight),"Snakerino");
	window.setFramerateLimit(fps);

	ResourceLoader &rl = ResourceLoader::getInstance();
	rl.initResourceLoader();
	rl.addTexture("Snake", "../res/Snake/snake.jpg");

	sf::Texture* tx = rl.addTexture("gridSquare", "../res/Snake/gridSquare.jpg");
	gridSprite.setTexture(*tx);

//	for (auto & i : grid) { //TODO Is explicit pointing to nullptr necessary?
//		for (auto & j : i) {
//			j = nullptr;
//		}
//	}
}

void GameBoard::drawBoard() {
	window.clear();
	drawGrid();
	drawDrawables();
	window.display();
}

void GameBoard::drawDrawables() {
	for (auto & drawable : drawables) {
		window.draw(*drawable);
	}
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

void GameBoard::drawGrid() {
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			gridSprite.setPosition(x*50, y*50);
			gridSprite.setScale(0.5,0.5);
			window.draw(gridSprite);

		}
	}

}


