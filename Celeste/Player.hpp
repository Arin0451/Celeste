#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Animation.hpp"

class Player : public GameObject {
public:
    Player(const sf::Texture& texture);

    // Обновление состояния игрока
    void update(float deltaTime);

    // Движение игрока
    void handleInput(float deltaTime);

    // Гравитация
    void applyGravity(float deltaTime);

    // Проверка столкновений
    void checkCollision(const std::vector<sf::RectangleShape>& grounds);

private:
    float speed;      // Скорость движения игрока
    float velocityY;  // Вертикальная скорость (для гравитации)
    bool onGround;    // Находится ли игрок на земле
    bool jumpPressed; // Отслеживает нажатие прыжка для управления прыжком

    // Для улучшенного прыжка
    float jumpHeight;           // Максимальная высота прыжка
    float airControlSpeed;      // Скорость управления движением в воздухе
    float gravity;              // Сила гравитации
    float fastFallMultiplier;   // Множитель для ускоренного падения
    float maxFallSpeed;         // Ограничение максимальной скорости падения
    
    Animation animation; // Объект анимации
    bool faceRight;     // Направление игрока
};
