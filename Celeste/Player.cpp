#include "Player.hpp"

Player::Player(const sf::Texture& texture) : GameObject(texture),
speed(350.0f),
velocityY(0.0f),
onGround(false),
jumpHeight(600.0f),      // Начальная сила прыжка
airControlSpeed(150.0f), // Скорость движения в воздухе
gravity(980.0f),         // Сила гравитации
fastFallMultiplier(2.0f), // Множитель для ускоренного падения
maxFallSpeed(1000.0f),    // Ограничение скорости падения
jumpPressed(false),
animation(texture, sf::Vector2u(14, 2), 0.1f), // Инициализация анимации
faceRight(true) {
    sprite.setPosition(400.0f, 300.0f);  // Начальная позиция
    sprite.setScale(4.0f, 4.0f);
    sf::FloatRect bounds = sprite.getGlobalBounds();
    
}

void Player::update(float deltaTime) {
    handleInput(deltaTime);  // Передаем deltaTime
    applyGravity(deltaTime);  // Применение гравитации


    sprite.setTextureRect(animation.getUVRect());

}

void Player::handleInput(float deltaTime) {
    // Управление на земле и в воздухе
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sprite.move(-speed * (onGround ? 1 : 0.7f) * deltaTime, 0.0f);  // В воздухе скорость меньше
        faceRight = 0;
        animation.update(deltaTime, faceRight);
        sprite.setTextureRect(animation.getUVRect());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sprite.move(speed * (onGround ? 1 : 0.7f) * deltaTime, 0.0f);  // В воздухе скорость меньше
        faceRight = 1;
        animation.update(deltaTime, faceRight);
        sprite.setTextureRect(animation.getUVRect());
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
       // animation.resetFrame();
        sprite.setTextureRect(animation.getUVRect());
    }


    // Прыжок
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (onGround) {
            velocityY = -jumpHeight;  // Начальная сила прыжка
            onGround = false;
        }
        jumpPressed = true;
    }
    else {
        // Если игрок отпустил кнопку прыжка и еще в прыжке, уменьшаем вертикальную скорость
        if (jumpPressed && velocityY < 0) {
            velocityY += 300.0f * deltaTime;  // Меньше подъем, если отпустили кнопку
        }
        jumpPressed = false;
    }
}

void Player::applyGravity(float deltaTime) {
    if (!onGround) {
        velocityY += gravity * deltaTime;  // Применяем гравитацию

        // Ускоряем падение, если игрок падает
        if (velocityY > 0) {
            velocityY += gravity * (fastFallMultiplier - 1) * deltaTime;  // Ускоренное падение
        }

        // Ограничиваем максимальную скорость падения
        if (velocityY > maxFallSpeed) {
            velocityY = maxFallSpeed;
        }
    }
    sprite.move(0.0f, velocityY * deltaTime);
}

void Player::checkCollision(const std::vector<sf::RectangleShape>& grounds) {
    onGround = false; // Сначала считаем, что игрок не на земле

    for (const auto& ground : grounds) {
        if (sprite.getGlobalBounds().intersects(ground.getGlobalBounds())) {
            onGround = true; // Игрок на земле
            velocityY = 0.0f; // Сброс вертикальной скорости

            // Исправляем позицию игрока относительно "пола"
            sprite.setPosition(sprite.getPosition().x, ground.getPosition().y - sprite.getGlobalBounds().height);
            break; // Выходим после первого столкновения
        }
    }
}
