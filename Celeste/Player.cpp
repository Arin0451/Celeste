#include <SFML/Graphics.hpp>
#include <iostream>

class Player {

private:
    int x, y;
    float speed;


public:

    sf::Sprite playerSprite() {
        sf::Texture texture;
        if (!texture.loadFromFile("MadeLine.png"))
        {
            std::cout << "Ошибка загрузки текстуры Медилайн!" << std::endl;
        }
        sf::Sprite playerSprite;
        playerSprite.setTexture(texture);
        playerSprite.setScale(0.5f, 0.5f);
        return playerSprite;
    }
};