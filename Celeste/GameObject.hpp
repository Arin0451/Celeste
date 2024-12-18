#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
public:
    GameObject(const sf::Texture& texture);

    virtual void update(float deltaTime) = 0; // ����� ����������� ������� ����������

    sf::Sprite getSprite() const;

protected:
    sf::Sprite sprite; // ������ �������
};
