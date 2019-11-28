//
// Created by tiyst on 23/11/2019.
//

#include "Game.hpp"


Game::Game(ResourceLoader &rl) : rl(rl) {
	board = new GameBoard(60, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	Snake* snake = new Snake(4, 5, 5);
	board->addDrawable(snake);
}


void Game::run() {
	while (board->isActive()) {
		sf::Event event;
		while (board->getWindow()->pollEvent(event)) {
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				board->getWindow()->close();
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				auto *circle = new sf::CircleShape(50.f); //This took fucking forever to implement
				circle->setRadius(70.f);
				circle->setFillColor(sf::Color::Blue);
				circle->setPosition(sf::Mouse::getPosition(*board->getWindow()).x, sf::Mouse::getPosition(*board->getWindow()).y);
				board->addDrawable(circle);
			}
		}

		board->drawBoard();
	}
}
