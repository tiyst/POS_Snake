//
// Created by tiyst on 17/11/2019.
//

#ifndef SNAKERINO_SNAKEPIECE_HPP
#define SNAKERINO_SNAKEPIECE_HPP

#include "GameObject.cpp"

class SnakePiece : public GameObject {
public:
	enum BODYPART {TAIL, BODY, HEAD}; //Can be used to change textures while rotating

	SnakePiece(int x, int y) : GameObject(x, y) {
		init();
	}
	SnakePiece(sf::Vector2i cdr) : GameObject(cdr) {
		init();
	}
	~SnakePiece() {};

	void setBodyPart(BODYPART bp) {
		bodyPart = bp;
	}

private:
	BODYPART bodyPart;

	void init() {
		setTexture(rl.getTexture("Snake"));
		bodyPart = BODYPART::BODY;
	}
};


#endif //SNAKERINO_SNAKEPIECE_HPP
