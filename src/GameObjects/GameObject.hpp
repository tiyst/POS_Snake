//
// Created by tiyst on 17/11/2019.
//

#ifndef SNAKERINO_GAMEOBJECT_HPP
#define SNAKERINO_GAMEOBJECT_HPP


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Audio.hpp>

class GameObject : public sf::Drawable {

public:
	GameObject(int x, int y);
	GameObject(sf::Vector2i cdr);
	virtual ~GameObject() {} ;


	void changeCoordinates(sf::Vector2i cdr) {
		coordinates = cdr;
		int x = cdr.x * rl.getSquareSize() + rl.getWindowOffset(),
			y = cdr.y * rl.getSquareSize() + rl.getWindowOffset();
		sprite.setPosition((float)x, (float)y);
	}

	void changeCoordinates(int x, int y) {
		changeCoordinates(sf::Vector2i(x,y));
	}

	sf::Vector2i getCoordinates() {
		return coordinates;
	}

	void setSize(int x, int y);
	void setSize(sf::Vector2f newSize);

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f newPos);

	void setOrigin(float x, float y);
	void setOriginToCenter();

	void setHidden(bool hidden);
	void setTexture(sf::Texture* txt);

	bool isClickedOn(sf::Vector2i coords);

protected:
	sf::Vector2i coordinates;
	sf::Texture* texture;
	sf::Sprite sprite;
	ResourceLoader &rl;

	void init();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif //SNAKERINO_GAMEOBJECT_HPP
