//
// Created by tiyst on 02/12/2019.
//

#ifndef SNAKERINO_APPLE_HPP
#define SNAKERINO_APPLE_HPP


class Apple : public GameObject {

public:
	Apple(int x, int y) : GameObject(x, y) {
		initApple();
	}

	Apple(sf::Vector2i vec) : GameObject(vec) {
		initApple();
	}


private:


	void initApple() {
		rl.addTexture("Apple", "../res/Snake/apple.jpg");
	}
};


#endif //SNAKERINO_APPLE_HPP
