#include <SFML/Graphics.hpp>
#include <iostream>

#include "./Constants.h"
#include "./Player.cpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");


    sf::Texture texture;
    if (!texture.loadFromFile("MadeLine.png"))
    {
        std::cout << "Ошибка загрузки текстуры Медилайн!" << std::endl;
        return -1;
    }
    sf::Sprite playerSprite;
    playerSprite.setTexture(texture);
    playerSprite.setScale(0.1f, 0.1f);
    playerSprite.setPosition(100.0f, 1000.0f);

    // Скорость движения спрайта
    float speed = 200.0f;  // Пикселей в секунду
    // Время с последнего кадра
    sf::Clock clock;





    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Получаем время, прошедшее с предыдущего кадра
        sf::Time deltaTime = clock.restart();
        float delta = deltaTime.asSeconds();  // Время в секундах

 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            playerSprite.move(-speed * delta, 0.0f);  // Влево
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            playerSprite.move(speed * delta, 0.0f);  // Вправо
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            playerSprite.move(0.0f, -speed * delta);  // Вверх
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            playerSprite.move(0.0f, speed * delta);  // Вниз
        }

        window.clear(sf::Color::White);
        window.draw(playerSprite);
        window.display();
    }

    return 0;
}