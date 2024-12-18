#include "Animation.hpp"

Animation::Animation(const sf::Texture& texture, const sf::Vector2u& frameCount, float switchTime)
    : frameCount(frameCount), switchTime(switchTime), totalTime(0.0f), row(0) {
    uvRect.width = 15;
    uvRect.height = 18;

}// СДВИГАТЬ ПО ЗАДАННОМУ ИКСУ

void Animation::update(float deltaTime, bool faceRight) {
    totalTime += deltaTime;

    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentFrame.x+=1;

        if (currentFrame.x >= frameCount.x) {
            currentFrame.x = 0; // Возврат к первому кадру
        }
    }

    // Установка направления
    uvRect.top = row * uvRect.height;
    uvRect.left = currentFrame.x * uvRect.width;

    if (!faceRight) {
        row = 1;
    } else {
        row = 0;
    }
}

void Animation::resetFrame() {
    currentFrame.x = 0; // Сбрасываем текущий кадр
}

const sf::IntRect& Animation::getUVRect() const {
    return uvRect;
}
