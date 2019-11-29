//
// Created by tiyst on 17/11/2019.
//

#ifndef SNAKERINO_GAMEOBJECT_HPP
#define SNAKERINO_GAMEOBJECT_HPP


class GameObject : public sf::Drawable {

public:
	GameObject(int x, int y);
	GameObject(sf::Vector2i cdr);
	virtual ~GameObject() {} ;


	void changeCoordinates(sf::Vector2i cdr) {
		coordinates = cdr;
		sprite.setPosition(cdr.x, cdr.y);
	}

	void changeCoordinates(int x, int y) {
		changeCoordinates(sf::Vector2i(x,y));
	}

	sf::Vector2i getCoordinates() {
		return coordinates;
	}

	void setSize(int x, int y);
	void setSize(sf::Vector2f newSize);
	void setHidden(bool hidden);
	void setTexture(sf::Texture* txt);

protected:
	sf::Vector2i coordinates;
	sf::Texture* texture;
	sf::Sprite sprite;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {

	}
};


#endif //SNAKERINO_GAMEOBJECT_HPP
