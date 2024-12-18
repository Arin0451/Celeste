#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Animation.hpp"

class Player : public GameObject {
public:
    Player(const sf::Texture& texture);

    // ���������� ��������� ������
    void update(float deltaTime);

    // �������� ������
    void handleInput(float deltaTime);

    // ����������
    void applyGravity(float deltaTime);

    // �������� ������������
    void checkCollision(const std::vector<sf::RectangleShape>& grounds);

private:
    float speed;      // �������� �������� ������
    float velocityY;  // ������������ �������� (��� ����������)
    bool onGround;    // ��������� �� ����� �� �����
    bool jumpPressed; // ����������� ������� ������ ��� ���������� �������

    // ��� ����������� ������
    float jumpHeight;           // ������������ ������ ������
    float airControlSpeed;      // �������� ���������� ��������� � �������
    float gravity;              // ���� ����������
    float fastFallMultiplier;   // ��������� ��� ����������� �������
    float maxFallSpeed;         // ����������� ������������ �������� �������
    
    Animation animation; // ������ ��������
    bool faceRight;     // ����������� ������
};
