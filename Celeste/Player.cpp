#include "Player.hpp"

Player::Player(const sf::Texture& texture) : GameObject(texture),
speed(350.0f),
velocityY(0.0f),
onGround(false),
jumpHeight(600.0f),      // ��������� ���� ������
airControlSpeed(150.0f), // �������� �������� � �������
gravity(980.0f),         // ���� ����������
fastFallMultiplier(2.0f), // ��������� ��� ����������� �������
maxFallSpeed(1000.0f),    // ����������� �������� �������
jumpPressed(false),
animation(texture, sf::Vector2u(14, 2), 0.1f), // ������������� ��������
faceRight(true) {
    sprite.setPosition(400.0f, 300.0f);  // ��������� �������
    sprite.setScale(4.0f, 4.0f);
    sf::FloatRect bounds = sprite.getGlobalBounds();
    
}

void Player::update(float deltaTime) {
    handleInput(deltaTime);  // �������� deltaTime
    applyGravity(deltaTime);  // ���������� ����������


    sprite.setTextureRect(animation.getUVRect());

}

void Player::handleInput(float deltaTime) {
    // ���������� �� ����� � � �������
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sprite.move(-speed * (onGround ? 1 : 0.7f) * deltaTime, 0.0f);  // � ������� �������� ������
        faceRight = 0;
        animation.update(deltaTime, faceRight);
        sprite.setTextureRect(animation.getUVRect());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sprite.move(speed * (onGround ? 1 : 0.7f) * deltaTime, 0.0f);  // � ������� �������� ������
        faceRight = 1;
        animation.update(deltaTime, faceRight);
        sprite.setTextureRect(animation.getUVRect());
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
       // animation.resetFrame();
        sprite.setTextureRect(animation.getUVRect());
    }


    // ������
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (onGround) {
            velocityY = -jumpHeight;  // ��������� ���� ������
            onGround = false;
        }
        jumpPressed = true;
    }
    else {
        // ���� ����� �������� ������ ������ � ��� � ������, ��������� ������������ ��������
        if (jumpPressed && velocityY < 0) {
            velocityY += 300.0f * deltaTime;  // ������ ������, ���� ��������� ������
        }
        jumpPressed = false;
    }
}

void Player::applyGravity(float deltaTime) {
    if (!onGround) {
        velocityY += gravity * deltaTime;  // ��������� ����������

        // �������� �������, ���� ����� ������
        if (velocityY > 0) {
            velocityY += gravity * (fastFallMultiplier - 1) * deltaTime;  // ���������� �������
        }

        // ������������ ������������ �������� �������
        if (velocityY > maxFallSpeed) {
            velocityY = maxFallSpeed;
        }
    }
    sprite.move(0.0f, velocityY * deltaTime);
}

void Player::checkCollision(const std::vector<sf::RectangleShape>& grounds) {
    onGround = false; // ������� �������, ��� ����� �� �� �����

    for (const auto& ground : grounds) {
        if (sprite.getGlobalBounds().intersects(ground.getGlobalBounds())) {
            onGround = true; // ����� �� �����
            velocityY = 0.0f; // ����� ������������ ��������

            // ���������� ������� ������ ������������ "����"
            sprite.setPosition(sprite.getPosition().x, ground.getPosition().y - sprite.getGlobalBounds().height);
            break; // ������� ����� ������� ������������
        }
    }
}
