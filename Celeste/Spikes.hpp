#pragma once
#include <SFML/Graphics.hpp>

class Spikes {
public:
    Spikes(const sf::Texture& texture, const sf::Vector2f& position);

    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;

private:
    sf::Sprite spikeSprite;
};

