#include "Spikes.hpp"

Spikes::Spikes(const sf::Texture& texture, const sf::Vector2f& position) {
    spikeSprite.setTexture(texture);
    spikeSprite.setPosition(position);
}

void Spikes::draw(sf::RenderWindow& window) const {
    window.draw(spikeSprite);
}

sf::FloatRect Spikes::getBounds() const {
    return spikeSprite.getGlobalBounds();
}
