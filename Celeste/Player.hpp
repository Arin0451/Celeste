#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

class Player : public GameObject {
public:
    Player(const sf::Texture& texture);

    // ���������� ��������� ������
    void update(float deltaTime);

    // �������� ������
    void handleInput(float deltaTime);  // �������� deltaTime

    // ����������
    void applyGravity(float deltaTime, float gravity);

    // �������� ������������
    void checkCollision(const std::vector<sf::RectangleShape>& grounds);

private:
    float speed;      // �������� �������� ������
    float velocityY;  // ������������ �������� (��� ����������)
    bool onGround;    // ��������� �� ����� �� �����
};
