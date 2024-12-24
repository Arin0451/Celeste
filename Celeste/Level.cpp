#include "Level.hpp"

Level::Level(const std::string& levelData, const sf::Texture& groundTexture, const sf::Texture& wallTexture) {
    createLevel(levelData, groundTexture, wallTexture );
}

void Level::createLevel(const std::string& levelData, const sf::Texture& groundTexture, const sf::Texture& wallTexture) {
    float blockWidth = 50.0f;
    float blockHeight = 50.0f;

    for (int y = 0; y < levelData.size(); y++) {
        char tile = levelData[y];

        // Обработка земли
        if (tile == '#') {
            sf::RectangleShape block(sf::Vector2f(blockWidth, blockHeight));
            block.setTexture(&groundTexture);
            block.setPosition((y % 38) * blockWidth, (y / 38) * blockHeight); // Координаты блока
            grounds.push_back(block);
        }
        // Обработка земли
        if (tile == '@') {
            sf::RectangleShape block(sf::Vector2f(blockWidth, blockHeight));
            block.setTexture(&wallTexture);
            block.setPosition((y % 38) * blockWidth, (y / 38) * blockHeight); // Координаты блока
            grounds.push_back(block);
        }
        // Обработка точки спавна
        else if (tile == 'P') {
            spawnPoint.x = (y % 38) * blockWidth;
            spawnPoint.y = (y / 38) * blockHeight;
        }
    }
}

const std::vector<sf::RectangleShape>& Level::getGrounds() const {
    return grounds;
}

// Геттер для точки спавна
const sf::Vector2f& Level::getSpawnPoint() const {
    return spawnPoint;
}

void Level::draw(sf::RenderWindow& window) {
    for (const auto& ground : grounds) {
        window.draw(ground);
    }
}
