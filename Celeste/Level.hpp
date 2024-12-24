#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Level {
public:
    Level(const std::string& levelData, const sf::Texture& groundTexture, const sf::Texture& wallTexture, const sf::Texture& strawberryTexture);

    const std::vector<sf::RectangleShape>& getGrounds() const;
    const std::vector<sf::RectangleShape>& getStrawberries() const;
    const sf::Vector2f& getSpawnPoint() const; // Новый геттер для точки спавна
    void draw(sf::RenderWindow& window);
    void loadNewLevel(const std::string& levelData, const sf::Texture& groundTexture, const sf::Texture& wallTexture, const sf::Texture& strawberryTexture);

private:
    std::vector<sf::RectangleShape> grounds;
    std::vector<sf::RectangleShape> strawberries;
    sf::Vector2f spawnPoint; // Точка спавна
    void createLevel(const std::string& levelData, const sf::Texture& groundTexture, const sf::Texture& wallTexture, const sf::Texture& strawberryTexture);
};
