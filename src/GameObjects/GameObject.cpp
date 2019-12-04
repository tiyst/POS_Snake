//
// Created by tiyst on 17/11/2019.
//

#include "GameObject.hpp"


GameObject::GameObject(int x, int y) : rl(ResourceLoader::getInstance()) {
	coordinates = sf::Vector2i(x,y);
	init();
}

GameObject::GameObject(sf::Vector2i cdr) : rl(ResourceLoader::getInstance())  {
	coordinates = cdr;
	init();
}

void GameObject::init() {
	changeCoordinates(coordinates);
	setTexture(rl.getDefaultTexture());
	setSize(rl.getSquareSize(), rl.getSquareSize());
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

void GameObject::setPosition(float x, float y) {
	sprite.setPosition(x,y);
}

void GameObject::setPosition(sf::Vector2f newPos) {
	setPosition(newPos.x, newPos.y);
}

void GameObject::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(sprite);
}
