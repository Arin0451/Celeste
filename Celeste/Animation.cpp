#include "Animation.hpp"

Animation::Animation(const sf::Texture& texture, const sf::Vector2u& frameCount, float switchTime)
    : frameCount(frameCount), switchTime(switchTime), totalTime(0.0f), row(0) {
    uvRect.width = texture.getSize().x / frameCount.x;
    uvRect.height = texture.getSize().y / frameCount.y;
}

void Animation::update(float deltaTime, bool faceRight) {
    totalTime += deltaTime;

    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentFrame.x++;

        if (currentFrame.x >= frameCount.x) {
            currentFrame.x = 0; // Возврат к первому кадру
        }
    }

    // Установка направления
    uvRect.top = row * uvRect.height;
    uvRect.left = currentFrame.x * uvRect.width;

    if (!faceRight) {
        uvRect.left += uvRect.width;
        uvRect.width = -std::abs(uvRect.width);
    } else {
        uvRect.width = std::abs(uvRect.width);
    }
}

void Animation::setRow(unsigned int row) {
    this->row = row;
    currentFrame.x = 0; // Сбрасываем текущий кадр
}

const sf::IntRect& Animation::getUVRect() const {
    return uvRect;
}
