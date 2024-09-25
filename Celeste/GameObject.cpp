#include "GameObject.hpp"

GameObject::GameObject(const sf::Texture& texture) {
    sprite.setTexture(texture);
}

sf::Sprite GameObject::getSprite() const {
    return sprite;
}
