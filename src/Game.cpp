//
// Created by tiyst on 23/11/2019.
//

#include "Game.hpp"


Game::Game(ResourceLoader &rl, unsigned int fps, unsigned int width, unsigned int height)
        : rl(rl), fps(fps), windowHeight(height), windowWidth(width) {
	board = new GameBoard(rl);
	Snake* snake = new Snake(4, 5, 5);
	board->addDrawable(snake);

    renderWindow.create(sf::VideoMode(windowWidth, windowHeight),"Snakerino");
    renderWindow.setFramerateLimit(fps);
}


void Game::run() {
	while (renderWindow.isOpen()) {
		sf::Event event;
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
                renderWindow.close();
			}
			if (event.type == sf::Event::KeyPressed) {
			    if (event.key.code == sf::Keyboard::Escape) {
                    renderWindow.close();
			    }
			    board->pollInput(event.key.code);
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				auto *circle = new sf::CircleShape(50.f); //This took fucking forever to implement
				circle->setRadius(70.f);
				circle->setFillColor(sf::Color::Blue);
				circle->setPosition(sf::Mouse::getPosition(renderWindow).x, sf::Mouse::getPosition(renderWindow).y);
				board->addDrawable(circle);
			}
		}

		renderWindow.clear();
		board->drawBoard(renderWindow);
		renderWindow.display();
	}
}
