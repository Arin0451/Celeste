#include "GameObject.hpp"

GameObject::GameObject(const sf::Texture& texture) {
    sprite.setTexture(texture);
}

sf::Sprite GameObject::getSprite() const {
    return sprite;
}



//ладно вернемся к анимациям
//я хочу чтобы кадры менялись так  представь квадрат
//и в этот квадрат попал первый кадр и когда надо ему поменяться он сдвигается на этот квадрат