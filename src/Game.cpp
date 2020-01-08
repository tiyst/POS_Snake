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
    snake = new Snake(4, 10, 5);
    apple = new GameObject(0,0);
    apple->setTexture(rl.getTexture("Apple"));
    apple->setOriginToCenter();


    int windowSize = rl.getGridSize() * rl.getSquareSize();
    renderWindow.create(sf::VideoMode(windowSize, windowSize),"Snakerino");//, sf::Style::Fullscreen);
    renderWindow.setFramerateLimit(fps);

    std::thread connectionThread(&Game::connect, this);
//	TODO addWall animation for waiting
    connectionThread.join();
    listening = true;
    listeningThread = std::thread(&Game::listen, this);

    if(isServer) {
        srand(time(nullptr));
        int x, y;
        for (int i = 0; i < rl.getGridSize() / 3; i++) {
            x = rand() % rl.getGridSize(), y = rand() % rl.getGridSize();
            addWall(sf::Vector2i(x, y));
            sendPacket(GAME_EFFECT::WALL, x, y);
        }
        changeApplePosition();
    }

    gameStarted = false;
	tickTimeDelay = 200; //TODO change after testing
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
			    if (event.key.code == sf::Keyboard::Space && !gameStarted) {
			    	startGame();
			    }
				pollKeyboardInput(event.key.code);
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				int x = sf::Mouse::getPosition(renderWindow).x;
				int y = sf::Mouse::getPosition(renderWindow).y;
				pollMouseInput(event.mouseButton.button, sf::Vector2i(x,y));
			}
		}
        sf::Time time = gameRateClock.getElapsedTime();
        if (gameStarted && time.asMilliseconds() > tickTimeDelay) {
            gameRateClock.restart();
            tick();
        }

		drawCycle();
	}
	endGame();
	listeningThread.join();
}

void Game::tick() {
	sf::Vector2i newPos = snake->getHeadCoordinates();
	std::vector<SnakePiece*> *pieces = snake->getSnakePieces();

	if (newPos.x > rl.getGridSize() || newPos.y > rl.getGridSize() ||
		newPos.x < 0 || newPos.y < 0) {
		endGame();
		return;
	}

	//Collision with snake itself
	for (int i = 1; i < pieces->size() - 1; i++) {
		SnakePiece *piece = pieces->at(i);
		if (newPos.x == piece->getCoordinates().x && newPos.y == piece->getCoordinates().y) {
			endGame();
			return;
		}
	}

	//Collision with custom walls
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
            sendPacket(GAME_EFFECT::SNAKE_GROW, 0, 0);
        } else {
            snake->move();
            int x = 0, y = 0;
            switch (snake->getDirection()) {
                case Snake::DIRECTION::UP: y++;
                    break;
                case Snake::DIRECTION::DOWN: y--;
                    break;
                case Snake::DIRECTION::RIGHT: x++;
                    break;
                case Snake::DIRECTION::LEFT: x--;
                    break;
            }
            sendPacket(GAME_EFFECT::SNAKE_MOVE,x,y);
        }
	}
}

void Game::pollKeyboardInput(sf::Keyboard::Key key) {
	if(isServer) {
        if (turningClock.getElapsedTime().asMilliseconds() < tickTimeDelay) {
            return; //To prevent turning snake inside itself
        }
        switch (key) {
            case sf::Keyboard::Up:
                snake->changeDirection(Snake::DIRECTION::UP);
                break;
            case sf::Keyboard::Down:
                snake->changeDirection(Snake::DIRECTION::DOWN);
                break;
            case sf::Keyboard::Right:
                snake->changeDirection(Snake::DIRECTION::RIGHT);
                break;
            case sf::Keyboard::Left:
                snake->changeDirection(Snake::DIRECTION::LEFT);
                break;

            default:
                break;
        }
        turningClock.restart();
    } else {
	    if (key == sf::Keyboard::B) {
            snake->switchInvisibility();
        }
	}
}

void Game::pollMouseInput(sf::Mouse::Button button, sf::Vector2i pos) {
	if (!isServer) {
        if (button == sf::Mouse::Left) {
            int x = pos.x / rl.getSquareSize(), y = pos.y / rl.getSquareSize();
            if (!isPositionTaken(x, y)) {
                addWall(sf::Vector2i(x, y));
                sendPacket(GAME_EFFECT::WALL, x, y);
            }
        }
    }
}

void Game::startGame() {
	if (!gameStarted && isServer) {
		gameStarted = true;
		gameRateClock.restart();
	}
}

void Game::endGame() {
    if (isServer) {
        gameStarted = false;
        snake->setInvisibility(false);

        //TODO draw gameover to window
        std::cout << "Game ended\n";
    }
    listening = false;
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
	auto pieces = snake->getSnakePieces();
	for (auto & piece : *pieces) {
		sf::Vector2i coord = piece->getCoordinates();
		if (coord.x == x && coord.y == y) {
			//TODO Still can crash, however the chance is greatly reduced
			//FIXME This causes crash (11)
			//If random coords are in snake this keeps calling itself,
			//filling the stack with function calls
			//either (x + rand()) % size (don't like this solution)
			//or rebuild how the numbers are generated
			x = (x + rand()) % rl.getGridSize();
//			changeApplePosition();
//			return;
		}
	}

	for(auto & wall : walls) {
		sf::Vector2i coord = wall->getCoordinates();
		if (coord.x == x && coord.y == y) {
			x = (x + rand()) % rl.getGridSize();
//			changeApplePosition();
//			return;
		}
	}
	int halfSize = rl.getSquareSize()/2;
    apple->changeCoordinates(x, y); //Has to be here for game to recognise where it is on gameboard
	apple->setPosition(x * rl.getSquareSize() + halfSize, y * rl.getSquareSize() + halfSize);
	sendPacket(GAME_EFFECT::APPLE, x, y);
}

void Game::setTickTimeDelay(int delay) {
	tickTimeDelay = delay;
}

void Game::addWall(sf::Vector2i pos) {
    if (!isPositionTaken(pos)) {
        GameObject *wall = new GameObject(pos);
        wall->setTexture(rl.getTexture("Wall"));
        walls.push_back(wall);
    }
}

bool Game::isPositionTaken(int x, int y) {
	return isPositionTaken(sf::Vector2i(x, y));
}

bool Game::isPositionTaken(sf::Vector2i posCoord) {
	sf::Vector2i applePos = apple->getCoordinates();
	if (applePos == posCoord) {
		return true;
	}

	for (auto & wall : walls) {
		if (wall->getCoordinates() == posCoord) {
			return true;
		}
	}

    return (applePos.x - 1 <= posCoord.x && posCoord.x <= applePos.x + 1) &&
           (applePos.y - 1 <= posCoord.y && posCoord.y <= applePos.y + 1);
}

void Game::connect() {
	std::string ipAddress;
	int port = rl.getPort();
	const int packetSize = rl.getPacketSize();

	char cs;
	std::cout << "Do you want to run as client (c) or server (s)?\n";
	std::cout << "Server controls the snake, others want him to crash\n";
	std::cin  >> cs;

	sf::Packet packet;
	if (cs == 'c') {
	    isServer = false;
		std::cout << "Insert server's IP address.\n";
		std::cin >> ipAddress;

		sf::Socket::Status status = socket.connect(ipAddress, port);
		if (status != sf::Socket::Done) {
		    std::cout << "Connection failed, please check the IP address and try again." << std::endl;
		}

		packet << "Hello World!";
        if (socket.send(packet) != sf::Socket::Done) {
			std::cout << "Error sending packet to server" << std::endl;
		}
	} else if (cs == 's') {
		// bind the listener to a port
		isServer = true;
        sf::TcpListener listener;
        if (listener.listen(port) != sf::Socket::Done) {
            std::cout << "Error while waiting for clients." << std::endl;
		}

		// accept a new connection
		if (listener.accept(socket) != sf::Socket::Done) {
            std::cout << "Error while accepting new connection." << std::endl;
		}
		std::cout << "Client connected with IP address: " << socket.getRemoteAddress().getPublicAddress() << std::endl;

		if (socket.receive(packet) != sf::Socket::Done) {
			// error...
		}

		std::string ret;
		packet >> ret;
		std::cout << "Data received: " << ret << std::endl;
	} else {
		std::cout << "Wrong input, try again." << std::endl;
		connect();
	}
}

void Game::sendPacket(GAME_EFFECT ef, int x, int y) {
	sf::Packet packet;
	packet << (int)ef << x << y;
	socket.send(packet);
}

void Game::receivePacket(sf::Packet& packet) {
	int x, y;
	int ef;
	packet >> ef >> x >> y;

	switch ((GAME_EFFECT) ef) {
	    case APPLE: moveApple(x, y);
	        break;
		case WALL: addWall(sf::Vector2i(x,y));
			break;
		case SPEED: triggerSpeed();
			break;
		case INVISIBILITY: triggerInvisibility();
			break;
	    case SNAKE_MOVE: moveSnake(x, y);
	        break;
	    case SNAKE_GROW: snake->addPiece(); //TODO is this right?
	        break;
		default:
			std::cout << "Unidentified effect received" << std::endl;
			break;
	}
}

void Game::triggerSpeed() {
	std::cout << "Triggering speed" << std::endl;
}


void Game::triggerInvisibility() {
	std::cout << "Triggering invis" << std::endl;
}

void Game::listen() {
    sf::Packet pck;
    while (listening) {
        if (socket.receive(pck) == sf::Socket::Done) {
            receivePacket(pck);
        }
    }
}

void Game::moveSnake(int x, int y) {
    if(x != 0) {
        if (x > 0) {
            snake->changeDirection(Snake::DIRECTION::RIGHT);
        } else {
            snake->changeDirection(Snake::DIRECTION::LEFT);
        }
    } else {
        if (y > 0) {
            snake->changeDirection(Snake::DIRECTION::UP);
        } else {
            snake->changeDirection(Snake::DIRECTION::DOWN);
        }
    }
    snake->move();
}

void Game::moveApple(int x, int y) {
    int halfSize = rl.getSquareSize()/2;
    apple->changeCoordinates(x, y); //Has to be here for game to recognise where it is on gameboard
    apple->setPosition(x * rl.getSquareSize() + halfSize, y * rl.getSquareSize() + halfSize);
}
