#include <SFML/Graphics.hpp>
#include "Player.hpp"

int main() {
    // Создаем окно
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Celeste");

    // Загружаем текстуру игрока
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("MadeLine.png")) {
        return -1;
    }

    // Создаем игрока
    Player player(playerTexture);
    
    // Создаем несколько объектов "пол"
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
    // Часы для времени между кадрами
    sf::Clock clock;

    // Основной игровой цикл
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Время между кадрами
        float deltaTime = clock.restart().asSeconds();

        // Обновляем игрока
        player.update(deltaTime);

        // Проверяем коллизии со всеми объектами "пола"
        player.checkCollision(grounds);


        // Очистка экрана
        window.clear(sf::Color::White);

        // Отрисовываем все объекты "пол"
        for (const auto& ground : grounds) {
            window.draw(ground);
        }
        window.draw(player.getSprite());

        // Отображение
        window.display();
    }

    return 0;
}
