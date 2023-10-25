#include "SFML/Window/Event.hpp"
#include "SFML/Window/WindowStyle.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    std::cout << "Hello, World!" << std::endl;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            if (event.type == sf::Event::TouchBegan) {
                std::cout << "Touch Began" << std::endl;
            } else if (event.type == sf::Event::TouchEnded) {
                std::cout << "Touch Ended" << std::endl;
            } else if (event.type == sf::Event::TouchMoved) {
                std::cout << "Touch Moved" << std::endl;
            }
        }

        window.clear();
        window.display();
    }

    return 0;
}
