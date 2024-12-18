#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
public:
    Animation(const sf::Texture& texture, const sf::Vector2u& frameCount, float switchTime);

    void update(float deltaTime, bool faceRight);
    void resetFrame();

    const sf::IntRect& getUVRect() const;

private:
    sf::Vector2u frameCount; // Количество кадров (колонки, строки)
    sf::Vector2u currentFrame; // Текущий кадр
    float switchTime; // Время между кадрами
    float totalTime; // Общее время для смены кадров

    sf::IntRect uvRect; // Координаты текущего кадра в текстуре
    unsigned int row; // Текущая строка (направление анимации)
};
