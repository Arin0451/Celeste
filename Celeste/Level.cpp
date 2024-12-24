#include "Level.hpp"

Level::Level(const std::string& levelData, const sf::Texture& groundTexture, const sf::Texture& wallTexture, const sf::Texture& strawberryTexture) {
    createLevel(levelData, groundTexture, wallTexture, strawberryTexture);
}

void Level::createLevel(const std::string& levelData, const sf::Texture& groundTexture, const sf::Texture& wallTexture, const sf::Texture& strawberryTexture) {
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
        else if (tile == 'S') {
            sf::RectangleShape strawberry(sf::Vector2f(blockWidth, blockHeight+5));
            strawberry.setTexture(&strawberryTexture); // Можно настроить текстуру клубнички
            strawberry.setPosition((y % 38) * blockWidth, (y / 38) * blockHeight - 5);
            strawberries.push_back(strawberry); // Добавляем клубничку в список
        }
    }
}

const std::vector<sf::RectangleShape>& Level::getGrounds() const {
    return grounds;
}
const std::vector<sf::RectangleShape>& Level::getStrawberries() const {
    return strawberries;
}

// Геттер для точки спавна
const sf::Vector2f& Level::getSpawnPoint() const {
    return spawnPoint;
}

void Level::draw(sf::RenderWindow& window) {
    for (const auto& ground : grounds) {
        window.draw(ground);
    }   
    for (const auto& strawberry : strawberries) {
        window.draw(strawberry);
    }
   
}

void Level::loadNewLevel(const std::string& levelData, const sf::Texture& groundTexture, const sf::Texture& wallTexture, const sf::Texture& strawberryTexture) {
    grounds.clear();
    createLevel(levelData, groundTexture, wallTexture, strawberryTexture); // Перезагружаем уровень
}