#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Level.hpp"
#include "Menu.hpp"
#include <iostream>
#include <vector>

enum GameState { MENU, PLAYING, HELP, EXIT };

int main() {
    sf::RenderWindow window(sf::VideoMode(1900, 1080), "Celeste");

    // Создаем меню
    std::vector<std::string> menuOptions = { "Play", "Help", "Exit" };
    Menu menu(menuOptions, "assets/fonts/PixelOperator8.ttf", { 850, 400 }, 50);

    // Создаем текст для "Help"
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/PixelOperator8.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }
    sf::Text helpText("This is the help screen.\nPress Esc to return to the menu.\n\nTo move, use the arrow keys.\nTo jump, press space.\n\n"
        "In the game, there is a Directed Dash. To perform it, press Left Shift (LShift).\nDirect the dash with the arrow keys in any of the 8 directions."
        "\nYou can use the dash in the air too! But remember, you will have 1 dash\nuntil you touch the ground again.\n\n"
        "To complete the level, pick up the strawberry!\nIf you encounter difficulties, you can always restart by pressing R.", font, 30);
    helpText.setFillColor(sf::Color::White);
    helpText.setPosition(50, 50);


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

    sf::Texture wallTexture;
    if (!wallTexture.loadFromFile("assets/textures/wall.png")) {
        std::cerr << "Failed to load wall texture!" << std::endl;
        return -1;
    }

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/textures/Background.png")) {
        std::cerr << "Failed to load background texture!" << std::endl;
        return -1;
    }
    
    sf::Texture helpgroundTexture;
    if (!helpgroundTexture.loadFromFile("assets/textures/helpground.jpg")) {
        std::cerr << "Failed to load background texture!" << std::endl;
        return -1;
    }

    sf::Sprite helpgroundSprite(helpgroundTexture);
    helpgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / helpgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / helpgroundTexture.getSize().y
    );

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
        ".....................................@"
        ".....................................@"
        ".....................................@"
        ".....................................@"
        ".....................................@"
        ".....................................@"
        "......................................"
        "...........................@.........."
        "@@@........................@....P....."
        "@@@...................#....@.........."
        "@@@.................#####..@...####..."
        "......................................"
        "......................................"
        ".............#####...................."
        ".............#####.......@@@@....@@@.."
        ".............#####...................."
        ".............#####...................."
        "......................................"
        "######################################"
        "######################################";

    Level level(levelData, groundTexture, wallTexture);

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
                        player.respawn(level.getSpawnPoint()); // Респавн игрока в точке спавна
                    }
                    else if (selected == 1) {
                        currentState = HELP; // Переход в состояние HELP
                    }
                    else if (selected == 2) {
                        currentState = EXIT;
                    }
                }
            }

            if ((currentState == HELP || currentState == PLAYING) && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) { // Выход из HELP
                    currentState = MENU;
                }
            }

            // Обработка нажатия клавиши "R" для респавна
            if (currentState == PLAYING && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                player.respawn(level.getSpawnPoint());
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
        else if (currentState == HELP) { // Обработка состояния HELP
            window.clear(sf::Color::White);
            window.draw(helpgroundSprite);
            window.draw(helpText);
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
