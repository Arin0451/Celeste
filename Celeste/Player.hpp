#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

class Player : public GameObject {
public:
    Player(const sf::Texture& texture);

    // Обновление состояния игрока
    void update(float deltaTime);

    // Движение игрока
    void handleInput(float deltaTime);  // Передаем deltaTime

    // Гравитация
    void applyGravity(float deltaTime, float gravity);

    // Проверка столкновений
    void checkCollision(const std::vector<sf::RectangleShape>& grounds);

private:
    float speed;      // Скорость движения игрока
    float velocityY;  // Вертикальная скорость (для гравитации)
    bool onGround;    // Находится ли игрок на земле
};
