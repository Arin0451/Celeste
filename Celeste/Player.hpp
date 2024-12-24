#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Animation.hpp"
#include "Spikes.hpp"
#include "Strawberry.hpp"


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

    void performDash(float deltaTime);

    void checkCollisionWithSpikes(const std::vector<Spikes>& spikes);

    void respawn(const sf::Vector2f& spawnPoint);

    void checkCollisionWithStrawberries(const std::vector<Strawberry>& strawberries);

private:
    float speed;      // Скорость движения игрока
    float velocityY;  // Вертикальная скорость (для гравитации)
    bool onGround;    // Находится ли игрок на земле
    bool jumpPressed; // Отслеживает нажатие прыжка для управления прыжком
    float maxJumpTime;  // Максимальное время удержания прыжка
    float currentJumpTime;  // Текущее время удержания клавиши

    // Для улучшенного прыжка
    float jumpHeight;           // Максимальная высота прыжка
    float airControlSpeed;      // Скорость управления движением в воздухе
    float gravity;              // Сила гравитации
    float fastFallMultiplier;   // Множитель для ускоренного падения
    float maxFallSpeed;         // Ограничение максимальной скорости падения
    
    Animation animation; // Объект анимации
    bool faceRight;     // Направление игрока

    bool dashAvailable;      // Доступность рывка
    float dashSpeed;         // Скорость рывка
    sf::Vector2f dashDirection; // Направление рывка
    float dashTime;          // Длительность рывка
    float currentDashTime;   // Текущее время рывка
    bool isDashing;          // Выполняется ли рыво

    sf::Vector2f spawnPoint;
};
