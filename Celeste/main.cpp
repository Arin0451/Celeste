#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include <iostream>
using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Celeste");

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("assets/textures/runLeftAndRight.png")) {
        return -1;
    }



    Player player(playerTexture);

    std::vector<sf::RectangleShape> grounds;

    // Пол
    sf::RectangleShape ground1(sf::Vector2f(800.0f, 50.0f));
    ground1.setFillColor(sf::Color::Black);
    ground1.setPosition(0.0f, 550.0f);
    grounds.push_back(ground1);

    sf::RectangleShape ground2(sf::Vector2f(1920.0f, 50.0f));
    ground2.setFillColor(sf::Color::Black);
    ground2.setPosition(0.0f, 1030.0f);
    grounds.push_back(ground2);

    sf::RectangleShape wall(sf::Vector2f(50.0f, -500.0f));
    wall.setFillColor(sf::Color::Black);
    wall.setPosition(1800.0f, 1000.0f);
    grounds.push_back(wall);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        player.update(deltaTime);
        player.checkCollision(grounds);


        window.clear(sf::Color::White);

        // Создание фона
        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("Background.png")) {
            std::cerr << "Failed to load background texture!" << std::endl;
            return -1;
        }
        sf::Sprite backgroundSprite(backgroundTexture);
        
        // Масштабирование спрайта фона, чтобы он занимал весь экран
        backgroundSprite.setScale(
            static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
            static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
        );

        window.draw(backgroundSprite);

        sf::Clock clock;

        for (const auto& ground : grounds) {
            window.draw(ground);
        }
        window.draw(player.getSprite());
        window.display();
    }

    return 0;
}
