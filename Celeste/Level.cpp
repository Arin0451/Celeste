#include "Level.hpp"

Level::Level(const std::string& levelData, const sf::Texture& groundTexture) {
    createLevel(levelData, groundTexture);
}

void Level::createLevel(const std::string& levelData, const sf::Texture& groundTexture) {
    float blockWidth = 50.0f;
    float blockHeight = 50.0f;

    for (int y = 0; y < levelData.size(); y++) {
        char tile = levelData[y];

        if (tile == '#') {  // Если символ '#' - это стена/земля
            sf::RectangleShape block(sf::Vector2f(blockWidth, blockHeight));
            block.setTexture(&groundTexture);
            block.setPosition((y % 38) * blockWidth, (y / 38) * blockHeight); // Создание на основе координат
            grounds.push_back(block);
        }
    }
}

const std::vector<sf::RectangleShape>& Level::getGrounds() const {
    return grounds;
}

void Level::draw(sf::RenderWindow& window) {
    for (const auto& ground : grounds) {
        window.draw(ground);
    }
}
