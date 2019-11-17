//
// Created by tiyst on 16/11/2019.
//

#include "gameBoard.hpp"

gameBoard::gameBoard(unsigned int fps, unsigned int width, unsigned int height)
		: fps(fps), windowHeight(height), windowWidth(width) {

}

void gameBoard::initGameBoard() {
	window.create(sf::VideoMode(windowWidth, windowHeight),"Snakerino");
	window.setFramerateLimit(fps);

	for (auto & i : grid) {
		for (auto & j : i) {
			j = nullptr;
		}
	}
}

void gameBoard::drawBoard() {
	window.clear();
	drawDrawables();
	window.display();
}

void gameBoard::drawDrawables() {
	for (auto & drawable : drawables) {
		window.draw(*drawable);
	}
}

void gameBoard::addDrawable(sf::Drawable *drawable) {
	drawables.push_back(drawable);
}

