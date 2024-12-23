#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Level.hpp"
#include "Menu.hpp"
#include <iostream>
#include <vector>

enum GameState { MENU, PLAYING, EXIT };

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Celeste");

    // Создаем меню
    std::vector<std::string> menuOptions = { "Play", "Exit" };
    Menu menu(menuOptions, "assets/fonts/AtariClassic-gry3.ttf", { 850, 400 }, 50);

    // Загрузка текстур
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("assets/textures/runLeftAndRight.png")) {
        std::cerr << "Failed to load player texture!" << std::endl;
        return -1;
    }

    sf::Texture groundTexture;
    if (!groundTexture.loadFromFile("assets/textures/ground.png")) {
        std::cerr << "Failed to load ground texture!" << std::endl;
        return -1;
    }
    groundTexture.setRepeated(true);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/textures/Background.png")) {
        std::cerr << "Failed to load background texture!" << std::endl;
        return -1;
    }

    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    Player player(playerTexture);

    // Уровень
    std::string levelData =
        "......................................"
        "......................................"
        "......................................"
        "......................................"
        "......................................"
        "......................................"
        "......................................"
        "......................................"
        "......................................"
        "......................................"
        "...........................#.........."
        "...........................#.........."
        "...........................#.........."
        "....................#####..#...####..."
        "......................................"
        "......................................"
        ".............#####...................."
        ".............#####...................."
        ".............#####...................."
        ".............#####...................."
        "......................................"
        "######################################"
        "######################################";

    Level level(levelData, groundTexture);

    sf::Clock clock;

    GameState currentState = MENU;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (currentState == MENU && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    menu.moveUp();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    menu.moveDown();
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    int selected = menu.getSelectedOption();
                    if (selected == 0) {
                        currentState = PLAYING;
                    }
                    else if (selected == 1) {
                        currentState = EXIT;
                    }
                }
            }
        }

        if (currentState == EXIT) {
            window.close();
        }

        if (currentState == MENU) {
            window.clear(sf::Color::White);
            window.draw(backgroundSprite);
            menu.draw(window);
            window.display();
        }
        else if (currentState == PLAYING) {
            float deltaTime = clock.restart().asSeconds();

            player.update(deltaTime);
            player.checkCollision(level.getGrounds());

            window.clear(sf::Color::White);
            window.draw(backgroundSprite);
            level.draw(window);
            window.draw(player.getSprite());
            window.display();
        }
    }

    return 0;
}
