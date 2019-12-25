//
// Created by tiyst on 23/11/2019.
//

#include "Game.hpp"


Game::Game(unsigned int fps, unsigned int width, unsigned int height)
        : rl(ResourceLoader::getInstance()), fps(fps), windowHeight(height), windowWidth(width) {
	rl.addTexture("Apple", "../res/Snake/apple.png");
    rl.addTexture("Snake", "../res/Snake/snake.jpg");
    rl.addTexture("Wall",  "../res/Snake/brickWall.jpg");

    board = new GameBoard();
    snake = new Snake(4, 15, 5);
    apple = new GameObject(0,0);
    apple->setTexture(rl.getTexture("Apple"));
    apple->setOriginToCenter();
    changeApplePosition();

	GameObject* wall = new GameObject(3,5);
	GameObject* wall1 = new GameObject(8,2);
	GameObject* wall2 = new GameObject(11,12);
	wall->setTexture(rl.getTexture("Wall"));
	wall1->setTexture(rl.getTexture("Wall"));
	wall2->setTexture(rl.getTexture("Wall"));
    walls.push_back(wall);
    walls.push_back(wall1);
    walls.push_back(wall2);

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

	if (newPos.x > rl.getGridSize() || newPos.y > rl.getGridSize() ||
		newPos.x < 0 || newPos.y < 0) {
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
	for (int j = 0; j < walls.size(); j++) {
		sf::Vector2i wall = walls[j]->getCoordinates();
		if (newPos.x == wall.x && newPos.y == wall.y) { //FIXME Why does this enter?
			std::cout << "Collided with custom wall" << std::endl;
			endGame();
			return;
		}
	}

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
		case sf::Keyboard::Up:    snake->changeDirection(Snake::DIRECTION::UP);
			break;
		case sf::Keyboard::Down:  snake->changeDirection(Snake::DIRECTION::DOWN);
			break;
		case sf::Keyboard::Right: snake->changeDirection(Snake::DIRECTION::RIGHT);
			break;
		case sf::Keyboard::Left:  snake->changeDirection(Snake::DIRECTION::LEFT);
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
	//TODO draw gameover to window
	std::cout << "Game ended\n";
}

void Game::drawCycle() {
	renderWindow.clear();
	renderWindow.draw(*board);
    renderWindow.draw(*apple);
    renderWindow.draw(*snake);
	for (auto & wall : walls) {
		renderWindow.draw(*wall);
	}
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
			//FIXME This causes crash (11)
			//If random coords are in snake this keeps calling itself,
			//filling the stack with function calls
			//either (x + rand()) % size (don't like this solution)
			//or rebuild how the numbers are generated
			changeApplePosition();
			return;
		}
	}

	for(auto & wall : walls) {
		sf::Vector2i coord = wall->getCoordinates();
		if (coord.x == x && coord.y == y) {
			changeApplePosition();
			return;
		}
	}
	int halfSize = rl.getSquareSize()/2;
    apple->changeCoordinates(x, y); //Has to be here for game to recognise where it is on gameboard
	apple->setPosition(x * rl.getSquareSize() + halfSize, y * rl.getSquareSize() + halfSize);
}

void Game::setTickTimeDelay(int delay) {
	tickTimeDelay = delay;
}

void Game::addWall(GameObject *wall) {
	walls.push_back(wall);
}
