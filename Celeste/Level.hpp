#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Level {
public:
    Level(const std::string& levelData, const sf::Texture& groundTexture);

    const std::vector<sf::RectangleShape>& getGrounds() const;
    void draw(sf::RenderWindow& window);

private:
    std::vector<sf::RectangleShape> grounds;
    void createLevel(const std::string& levelData, const sf::Texture& groundTexture);
};
