#include "Player.hpp"

Player::Player(const sf::Texture& texture) : GameObject(texture),
speed(400.0f),
velocityY(0.0f),
onGround(false),
jumpHeight(300.0f * 1.3f),     // Начальная сила прыжка
airControlSpeed(400.0f),       // Скорость движения в воздухе
gravity(980.0f * 2.5f),        // Сила гравитации
fastFallMultiplier(1.5f),      // Множитель для ускоренного падения
maxFallSpeed(1000.0f),         // Ограничение скорости падения
maxJumpTime(0.3f),             // Максимальное время для высокого прыжка
currentJumpTime(0.0f),         // Изначально время прыжка равно нулю
jumpPressed(false),
dashAvailable(true),           // Рывок доступен
dashSpeed(1100.0f),             // Скорость рывка
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
        velocityY += gravity * deltaTime*0.8;  // Применяем гравитацию

        // Ограничиваем максимальную скорость падения
        if (velocityY > maxFallSpeed) {
            velocityY = maxFallSpeed;
        }
    }
    sprite.move(0.0f, velocityY * deltaTime);
}


void Player::checkCollision(const std::vector<sf::RectangleShape>& grounds) {
    sf::FloatRect playerBounds = sprite.getGlobalBounds();
    onGround = false;  // Изначально считаем, что игрок не на земле

    sf::Vector2f newPosition = sprite.getPosition();

    // Горизонтальные коллизии
    for (const auto& ground : grounds) {
        sf::FloatRect groundBounds = ground.getGlobalBounds();

        if (playerBounds.intersects(groundBounds)) {
            // Движение вправо
            if (velocityY == 0 && sprite.getPosition().x + playerBounds.width > groundBounds.left &&
                sprite.getPosition().x < groundBounds.left && velocityY == 0) {
                newPosition.x = groundBounds.left - playerBounds.width;  // Останавливаемся перед препятствием
            }
            // Движение влево
            if (velocityY == 0 && sprite.getPosition().x < groundBounds.left + groundBounds.width &&
                sprite.getPosition().x > groundBounds.left && velocityY == 0) {
                newPosition.x = groundBounds.left + groundBounds.width;  // Останавливаемся с другой стороны препятствия
            }
        }
    }

    // Вертикальные коллизии
    for (const auto& ground : grounds) {
        sf::FloatRect groundBounds = ground.getGlobalBounds();

        if (playerBounds.intersects(groundBounds)) {
            // Если игрок падает сверху на платформу
            if (velocityY > 0 && playerBounds.top + playerBounds.height <= groundBounds.top + 10.0f) {
                onGround = true;
                dashAvailable = true;  // Восстанавливаем рывок при соприкосновении с землёй
                velocityY = 0.0f;  // Сбрасываем скорость падения
                newPosition.y = groundBounds.top - playerBounds.height;  // Ставим игрока на платформу
            }
            // Если игрок прыгает и ударяется в нижнюю часть платформы
            else if (velocityY < 0 && playerBounds.top >= groundBounds.top + groundBounds.height - 10.0f) {
                velocityY = 0.0f;  // Останавливаем движение вверх
                newPosition.y = groundBounds.top + groundBounds.height;  // Ставим игрока под платформу
            }
        }
    }

    // Обновляем позицию персонажа только после завершения всех проверок
    sprite.setPosition(newPosition);
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

void Player::respawn(const sf::Vector2f& spawnPoint) {
    sprite.setPosition(spawnPoint);
    velocityY = 0.0f;
    onGround = true;
    dashAvailable = true;
    isDashing = false;
    currentDashTime = 0.0f;
    currentJumpTime = 0.0f;
    jumpPressed = false;
}

bool Player::checkCollisionWithStrawberry(const std::vector<sf::RectangleShape>& strawberries) {
    for (const auto& strawberry : strawberries) {
        if (sprite.getGlobalBounds().intersects(strawberry.getGlobalBounds())) {
            return true; // Если игрок столкнулся с клубничкой
        }
    }
    return false; // Если нет столкновения
}