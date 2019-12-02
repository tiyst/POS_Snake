//
// Created by tiyst on 23/11/2019.
//

#include "Game.hpp"


Game::Game(ResourceLoader &rl, unsigned int fps, unsigned int width, unsigned int height)
        : rl(rl), fps(fps), windowHeight(height), windowWidth(width) {
	board = new GameBoard(rl);
	Snake* snake = new Snake(4, 15, 5);
	board->setSnake(snake);


	gameStarted = false;
	tickTimeDelay = 500;
    renderWindow.create(sf::VideoMode(windowWidth, windowHeight),"Snakerino");//, sf::Style::Fullscreen);
    renderWindow.setFramerateLimit(fps);
}


void Game::run() {
	while (renderWindow.isOpen()) {
		sf::Event event;
		sf::Time time = clock.getElapsedTime();
		if (gameStarted && time.asMilliseconds() > tickTimeDelay) {
			clock.restart();
			board->tick();
		}
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
                renderWindow.close();
			}
			if (event.type == sf::Event::KeyPressed) {
			    if (event.key.code == sf::Keyboard::Escape) {
                    renderWindow.close();
			    }
			    if (event.key.code == sf::Keyboard::Space) {
			    	startGame();
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
		renderWindow.draw(*board);
		renderWindow.display();
	}
}

void Game::startGame() {
	gameStarted = true;
	clock.restart();
}

void Game::endGame() {
	gameStarted = false;
}
