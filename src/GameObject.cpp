//
// Created by tiyst on 17/11/2019.
//

#include "GameObject.hpp"


GameObject::GameObject(int x, int y) {
	coordinates = sf::Vector2i(x,y);
	ResourceLoader &rl = ResourceLoader::getInstance();
	setTexture(rl.getDefaultTexture());
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

void GameObject::setSize(sf::Vector2f newSize) {
    setSize(newSize.x, newSize.y);
}

void GameObject::setSize(int x, int y) {
    sf::Vector2f oldSize = sf::Vector2f(
            sprite.getTexture()->getSize().x * sprite.getScale().x,
            sprite.getTexture()->getSize().y * sprite.getScale().y);
    sprite.setScale(x / oldSize.x , y / oldSize.y);
}
