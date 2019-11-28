//
// Created by tiyst on 17/11/2019.
//

#ifndef SNAKERINO_SNAKEPIECE_HPP
#define SNAKERINO_SNAKEPIECE_HPP

#include "GameObject.cpp"

class SnakePiece : public GameObject {
public:
	enum BODYPART {TAIL, BODY, HEAD}; //Can be used to change textures while rotating

	SnakePiece(int x, int y) : GameObject(x, y) { } ;
	SnakePiece(sf::Vector2i cdr) : GameObject(cdr) {}
	~SnakePiece() {};

	void setBodyPart(BODYPART bp) {
		bodyPart = bp;
	}

private:
	BODYPART bodyPart;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
//		sf::Vector2f pos = sf::Vector2f(coordinates.x, coordinates.y);
//		this->sprite.setPosition(50,50);
		target.draw(this->sprite);
	}
};


#endif //SNAKERINO_SNAKEPIECE_HPP
