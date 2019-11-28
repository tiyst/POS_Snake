//
// Created by tiyst on 17/11/2019.
//

#include "GameObject.hpp"


GameObject::GameObject(int x, int y) {
	coordinates = sf::Vector2i(x,y);
}


GameObject::GameObject(sf::Vector2i cdr) {
	coordinates = cdr;
}

void GameObject::setHidden(bool hidden) {
	sprite.setColor(hidden ? sf::Color::Transparent : sf::Color::White);
}

void GameObject::setTexture(sf::Texture* txt) {
	texture = txt;
	sprite.setTexture(*texture);
}
