//
// Created by tiyst on 23/11/2019.
//

#include "Game.hpp"


Game::Game(unsigned int fps)
        : rl(ResourceLoader::getInstance()), fps(fps){
	rl.addTexture("Apple", "../res/Snake/apple.png");
    rl.addTexture("Snake", "../res/Snake/snake.jpg");
    rl.addTexture("Wall",  "../res/Snake/brickWall.jpg");

    board = new GameBoard();
    snake = new Snake(4, 15, 5);
    apple = new GameObject(0,0);
    apple->setTexture(rl.getTexture("Apple"));
    apple->setOriginToCenter();
    changeApplePosition();

    //Testing Data might be randomised for n walls after
    addWall(sf::Vector2i(3,5));
    addWall(sf::Vector2i(8,2));
    addWall(sf::Vector2i(11,13));

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
				pollKeyboardInput(event.key.code);
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				int x = sf::Mouse::getPosition(renderWindow).x;
				int y = sf::Mouse::getPosition(renderWindow).y;
				pollMouseInput(event.mouseButton.button, sf::Vector2i(x,y));
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

	for (int j = 0; j < walls.size(); j++) {
		sf::Vector2i wall = walls[j]->getCoordinates();
		if (newPos.x == wall.x && newPos.y == wall.y) {
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

void Game::pollKeyboardInput(sf::Keyboard::Key key) {
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

void Game::pollMouseInput(sf::Mouse::Button button, sf::Vector2i pos) {
	if(button == sf::Mouse::Left) {
		//TODO if wall isn't there yet
		int x = pos.x / rl.getSquareSize(), y = pos.y / rl.getSquareSize();
		addWall(sf::Vector2i(x,y));
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

void Game::addWall(sf::Vector2i pos) {
	//TODO If not on apple or other wall
	GameObject* wall = new GameObject(pos);
	wall->setTexture(rl.getTexture("Wall"));
	walls.push_back(wall);
}
