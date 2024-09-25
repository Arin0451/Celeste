#include "Player.hpp"

Player::Player(const sf::Texture& texture) : GameObject(texture), speed(200.0f), velocityY(0.0f), onGround(false) {
    sprite.setPosition(400.0f, 300.0f);  // Начальная позиция
    sprite.setScale(0.2f, 0.2f);
}

void Player::update(float deltaTime) {
    handleInput(deltaTime);  // Передаем deltaTime
    applyGravity(deltaTime, 500.0f);  // Применение гравитации
}

void Player::handleInput(float deltaTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sprite.move(-speed * deltaTime, 0.0f);  // Движение влево
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sprite.move(speed * deltaTime, 0.0f);  // Движение вправо
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround) {
        velocityY = -300.0f;  // Прыжок
        onGround = false;
    }
}

void Player::applyGravity(float deltaTime, float gravity) {
    if (!onGround) {
        velocityY += gravity * deltaTime;  // Применяем гравитацию
    }
    sprite.move(0.0f, velocityY * deltaTime);
}

void Player::checkCollision(const std::vector<sf::RectangleShape>& grounds) {
    onGround = false; // Сначала считаем, что игрок не на земле

    for (const auto& ground : grounds) {
        if (sprite.getGlobalBounds().intersects(ground.getGlobalBounds())) {
            onGround = true; // Игрок на земле
            velocityY = 0.0f; // Сброс вертикальной скорости

            // Устанавливаем позицию игрока на верхнюю грань объекта "пола"
            sprite.setPosition(sprite.getPosition().x, ground.getPosition().y - sprite.getGlobalBounds().height);
            break; // Выход из цикла, если нашли столкновение
        }
    }
}

