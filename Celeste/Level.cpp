#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Player.hpp"

// �������� ������ �� ������ �����
void loadLevel(const std::vector<std::string>& level,
    std::vector<sf::RectangleShape>& grounds,
    Player& player) {
    const float TILE_SIZE = 50.0f; // ������ ����� ������

    for (size_t y = 0; y < level.size(); ++y) {
        for (size_t x = 0; x < level[y].size(); ++x) {
            char tile = level[y][x];

            if (tile == '#') { // ����� ��� ���������
                sf::RectangleShape ground(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                ground.setFillColor(sf::Color::Black);
                ground.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                grounds.push_back(ground);
            }
            else if (tile == 'P') { // ��������� ������� ������
                player.getSprite().setPosition(x * TILE_SIZE, y * TILE_SIZE);
            }
        }
    }
}
