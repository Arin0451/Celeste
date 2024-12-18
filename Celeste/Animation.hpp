#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
public:
    Animation(const sf::Texture& texture, const sf::Vector2u& frameCount, float switchTime);

    void update(float deltaTime, bool faceRight);
    void setRow(unsigned int row);
    void manualFrame(int column);
    const sf::IntRect& getUVRect() const;

private:
    sf::Vector2u frameCount; // ���������� ������ (�������, ������)
    sf::Vector2u currentFrame; // ������� ����
    float switchTime; // ����� ����� �������
    float totalTime; // ����� ����� ��� ����� ������

    sf::IntRect uvRect; // ���������� �������� ����� � ��������
    unsigned int row; // ������� ������ (����������� ��������)
};
