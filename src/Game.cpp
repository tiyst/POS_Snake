//
// Created by tiyst on 23/11/2019.
//

#include "Game.hpp"


Game::Game(unsigned int fps, unsigned int width, unsigned int height)
        : rl(ResourceLoader::getInstance()), fps(fps), windowHeight(height), windowWidth(width) {
	rl.addTexture("Apple", "../res/Snake/apple.png");
    rl.addTexture("Snake", "../res/Snake/snake.jpg");

    board = new GameBoard();
    snake = new Snake(4, 15, 5);
    apple = new GameObject(0,0);
    apple->setTexture(rl.getTexture("Apple"));
    changeApplePosition();

    gameStarted = false;
	tickTimeDelay = 200; //TODO change after testing
	int windowSize = rl.getGridSize() * rl.getSquareSize();
    renderWindow.create(sf::VideoMode(windowSize, windowSize),"Snakerino");//, sf::Style::Fullscreen);
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
			    if (event.key.code == sf::Keyboard::Space) {
			    	startGame();
			    }
			    pollInput(event.key.code);
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				auto *circle = new sf::CircleShape(50.f); //This took fucking forever to implement
				circle->setRadius(70.f);
				circle->setFillColor(sf::Color::Blue);
				circle->setPosition(sf::Mouse::getPosition(renderWindow).x, sf::Mouse::getPosition(renderWindow).y);
				board->addDrawable(circle);
			}
		}
        sf::Time time = clock.getElapsedTime();
        if (gameStarted && time.asMilliseconds() > tickTimeDelay) {
            clock.restart();
            tick();
        }

		drawCycle();
	}
}

void Game::tick() {
	//TODO check for collision / enlarge snake when apple
	sf::Vector2i newPos = snake->getHeadCoordinates();
	std::vector<SnakePiece*> *pieces = snake->getSnake();

	if (newPos.x > rl.getGridSize() || newPos.y > rl.getGridSize()) {
		endGame();
		return;
	}

	for (int i = 1; i < pieces->size() - 1; i++) {
		SnakePiece *piece = pieces->at(i);
		if (newPos.x == piece->getCoordinates().x && newPos.y == piece->getCoordinates().y) {
			endGame();
			return;
		}
	}
	//TODO collision to custom walls

	if (gameStarted) {
        if (newPos == apple->getCoordinates()) {
            snake->addPiece();
            changeApplePosition();
        } else {
            snake->move();
        }
	}
}

void Game::pollInput(sf::Keyboard::Key key) {
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

void Game::startGame() {
	gameStarted = true;
	clock.restart();
}

void Game::endGame() {
	gameStarted = false;
	std::cout << "Game ended\n";
}

void Game::drawCycle() {
	renderWindow.clear();
	renderWindow.draw(*board);
    renderWindow.draw(*apple);
    renderWindow.draw(*snake);
	renderWindow.display();
}

void Game::changeApplePosition() {
    srand(time(nullptr));
	int x, y;
	x = rand() % rl.getGridSize();
	y = rand() % rl.getGridSize();

	//Checking if the apple is spawning on one of the snake pieces
	auto pieces = snake->getSnake();
	for (auto & piece : *pieces) {
		sf::Vector2i coord = piece->getCoordinates();
		if (coord.x == x && coord.y == y) {
			changeApplePosition();
			return;
		}
	}

    apple->changeCoordinates(x, y);
}

void Game::setTickTimeDelay(int delay) {
	tickTimeDelay = delay;
}
