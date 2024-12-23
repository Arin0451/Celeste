#include "Menu.hpp"
#include <stdexcept>

Menu::Menu(const std::vector<std::string>& optionTexts, const std::string& fontPath, sf::Vector2f startPos, float spacing) {
    if (!font.loadFromFile(fontPath)) {
        throw std::runtime_error("Failed to load font from " + fontPath);
    }
    selectedOption = 0;

    for (size_t i = 0; i < optionTexts.size(); ++i) {
        sf::Text text(optionTexts[i], font, 30);
        text.setPosition(startPos.x, startPos.y + i * spacing);
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::Black); // Первый элемент выделен
        options.push_back(text);
    }
}

void Menu::draw(sf::RenderWindow& window) {
    for (const auto& option : options) {
        window.draw(option);
    }
}

void Menu::moveUp() {
    if (selectedOption > 0) {
        options[selectedOption].setFillColor(sf::Color::Black);
        --selectedOption;
        options[selectedOption].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedOption < options.size() - 1) {
        options[selectedOption].setFillColor(sf::Color::Black);
        ++selectedOption;
        options[selectedOption].setFillColor(sf::Color::Red);
    }
}

int Menu::getSelectedOption() const {
    return selectedOption;
}
