#include <iostream>
#include <SFML/Window.hpp>

#include "piece.hpp"
#include "board.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess");
    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(60);

    Board board{};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear(sf::Color::White);

        board.render(window);
        board.update(window);

        window.display();
    }

    return 0;
}