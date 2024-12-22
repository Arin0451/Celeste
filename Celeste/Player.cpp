#include "Player.hpp"

Player::Player(const sf::Texture& texture) : GameObject(texture),
speed(350.0f),
velocityY(0.0f),
onGround(false),
jumpHeight(300.0f * 1.3f),     // Начальная сила прыжка
airControlSpeed(150.0f),       // Скорость движения в воздухе
gravity(980.0f * 2.5f),        // Сила гравитации
fastFallMultiplier(2.0f),      // Множитель для ускоренного падения
maxFallSpeed(1000.0f),         // Ограничение скорости падения
maxJumpTime(0.3f),             // Максимальное время для высокого прыжка
currentJumpTime(0.0f),         // Изначально время прыжка равно нулю
jumpPressed(false),
dashAvailable(true),           // Рывок доступен
dashSpeed(800.0f),             // Скорость рывка
dashTime(0.2f),                // Длительность рывка
currentDashTime(0.0f),
isDashing(false),
animation(texture, sf::Vector2u(13, 2), 0.04f), // Инициализация анимации
faceRight(true) {
    sprite.setPosition(400.0f, 300.0f);  // Начальная позиция
    sprite.setScale(4.0f, 4.0f);
    sf::FloatRect bounds = sprite.getGlobalBounds();
}

void Player::update(float deltaTime) {
    if (isDashing) {
        // Если в состоянии рывка
        currentDashTime += deltaTime;
        if (currentDashTime >= dashTime) {
            isDashing = false;
        }
        else {
            sprite.move(dashDirection * dashSpeed * deltaTime);
            return; // Прерываем дальнейшее обновление во время рывка
        }
    }
    handleInput(deltaTime);  // Передаем deltaTime
    applyGravity(deltaTime);  // Применение гравитации
    
}

void Player::handleInput(float deltaTime) {
    // Управление на земле и в воздухе
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sprite.move(-speed * (onGround ? 1 : 0.7f) * deltaTime, 0.0f);  // В воздухе скорость меньше
        faceRight = 0;
        if (onGround) {
            animation.update(deltaTime, faceRight);
            sprite.setTextureRect(animation.getUVRect());
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sprite.move(speed * (onGround ? 1 : 0.7f) * deltaTime, 0.0f);  // В воздухе скорость меньше
        faceRight = 1;
        if (onGround) {
            animation.update(deltaTime, faceRight);
            sprite.setTextureRect(animation.getUVRect());
        }
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (sf::Event::KeyReleased) {
            animation.setFrame(0);
            sprite.setTextureRect(animation.getUVRect());
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (sf::Event::KeyReleased) {
            animation.setFrame(0);
            sprite.setTextureRect(animation.getUVRect());
        }
    }

    // Прыжок
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (onGround && !jumpPressed) {  // Начало прыжка
            velocityY = -jumpHeight;  // Начальная сила прыжка
            onGround = false;
            jumpPressed = true;
            currentJumpTime = 0.0f;  // Сброс времени прыжка
            animation.setFrame(3);
        }
        // Если прыжок начался и клавиша удерживается
        if (jumpPressed && currentJumpTime < maxJumpTime) {
            currentJumpTime += deltaTime;  // Увеличиваем время удержания клавиши
            velocityY = -jumpHeight*1.1f;       // Продолжаем прыгать с начальной скоростью
        }
    }
    else {
        // Если игрок отпустил пробел, замедляем подъем (ускоряем гравитацию)
        if (jumpPressed && velocityY < 0) {
            velocityY += 300.0f *0.5f* deltaTime;  // Падение быстрее, если клавиша отпущена
        }
        jumpPressed = false;  // Клавиша отпущена
    }
    //if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) || ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))) {
    //    if (onGround) {
    //        velocityY = -jumpHeight;  // Начальная сила прыжка
    //        onGround = false;
    //        animation.setFrame(3);
    //    }
    //    jumpPressed = true;
    //}

     // Рывок
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && dashAvailable && !isDashing) {
        isDashing = true;
        dashAvailable = false;
        currentDashTime = 0.0f;

        dashDirection = { 0.0f, 0.0f };
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) dashDirection.y = -1.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) dashDirection.y = 1.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) dashDirection.x = -1.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) dashDirection.x = 1.0f;

        // Нормализация вектора
        float magnitude = std::sqrt(dashDirection.x * dashDirection.x + dashDirection.y * dashDirection.y);
        if (magnitude != 0.0f) {
            dashDirection /= magnitude;
        }
        else {
            dashDirection = { faceRight ? 1.0f : -1.0f, 0.0f }; // Рывок вперёд по умолчанию
        }
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
    onGround = false;
    for (const auto& ground : grounds) {
        if (sprite.getGlobalBounds().intersects(ground.getGlobalBounds())) {
            onGround = true;
            velocityY = 0.0f;
            dashAvailable = true; // Рывок восстанавливается при соприкосновении с землёй
            sprite.setPosition(sprite.getPosition().x, ground.getPosition().y - sprite.getGlobalBounds().height);
            break;
        }
    }
}

void Player::performDash(float deltaTime) {
    if (isDashing) {
        // Продолжаем рывок
        currentDashTime += deltaTime;

        if (currentDashTime >= dashTime) {
            isDashing = false;  // Завершаем рывок
            velocityY = 0;      // Сбрасываем вертикальную скорость
        }
        else {
            sprite.move(dashDirection * dashSpeed * deltaTime);
        }
    }
}
