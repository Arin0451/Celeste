#include "Player.hpp"

Player::Player(const sf::Texture& texture) : GameObject(texture), speed(200.0f), velocityY(0.0f), onGround(false) {
    sprite.setPosition(400.0f, 300.0f);  // ��������� �������
    sprite.setScale(0.2f, 0.2f);
}

void Player::update(float deltaTime) {
    handleInput(deltaTime);  // �������� deltaTime
    applyGravity(deltaTime, 500.0f);  // ���������� ����������
}

void Player::handleInput(float deltaTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sprite.move(-speed * deltaTime, 0.0f);  // �������� �����
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sprite.move(speed * deltaTime, 0.0f);  // �������� ������
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround) {
        velocityY = -300.0f;  // ������
        onGround = false;
    }
}

void Player::applyGravity(float deltaTime, float gravity) {
    if (!onGround) {
        velocityY += gravity * deltaTime;  // ��������� ����������
    }
    sprite.move(0.0f, velocityY * deltaTime);
}

void Player::checkCollision(const std::vector<sf::RectangleShape>& grounds) {
    onGround = false; // ������� �������, ��� ����� �� �� �����

    for (const auto& ground : grounds) {
        if (sprite.getGlobalBounds().intersects(ground.getGlobalBounds())) {
            onGround = true; // ����� �� �����
            velocityY = 0.0f; // ����� ������������ ��������

            // ������������� ������� ������ �� ������� ����� ������� "����"
            sprite.setPosition(sprite.getPosition().x, ground.getPosition().y - sprite.getGlobalBounds().height);
            break; // ����� �� �����, ���� ����� ������������
        }
    }
}

