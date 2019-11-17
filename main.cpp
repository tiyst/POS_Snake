#include <SFML/Graphics.hpp>
#include "Utilities/ResourceLoader.h"
#include "Game/gameBoard.cpp"


int main() {
	ResourceLoader rl = ResourceLoader::getResourceLoader();
	auto* board = new gameBoard(60, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	board->initGameBoard();
	sf::CircleShape shape(50.f);
	shape.setPosition(150, 150);
	board->addDrawable(&shape);

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

	return 0;
}