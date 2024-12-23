#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
private:
    sf::Font font;
    std::vector<sf::Text> options;
    int selectedOption;

public:
    Menu(const std::vector<std::string>& optionTexts, const std::string& fontPath, sf::Vector2f startPos, float spacing);

    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedOption() const;
};
