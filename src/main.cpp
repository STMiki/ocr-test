#include "SFML/Window/Event.hpp"
#include "SFML/Window/WindowStyle.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <tesseract/baseapi.h>

#define UNUSED __attribute__((unused))

void move(UNUSED sf::Vector2i pos) { std::cout << "Moving to " << pos.x << ", " << pos.y << std::endl; }

int main()
{
    tesseract::TessBaseAPI api = tesseract::TessBaseAPI();
    std::cout << "Hello, World!" << std::endl;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    bool pressed = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                std::cout << "Mouse Button Pressed" << std::endl;
                pressed = true;
            } else if (event.type == sf::Event::MouseButtonReleased) {
                std::cout << "Mouse Button Released" << std::endl;
                pressed = false;
            } else if (event.type == sf::Event::MouseMoved) {
                if (pressed)
                    move({event.mouseMove.x, event.mouseMove.y});
            }

            if (event.type == sf::Event::TouchBegan) {
                std::cout << "Touch Began" << std::endl;
                pressed = true;
            } else if (event.type == sf::Event::TouchEnded) {
                std::cout << "Touch Ended" << std::endl;
                pressed = false;
            } else if (event.type == sf::Event::TouchMoved) {
                if (pressed)
                    move({event.touch.x, event.touch.y});
            }
        }

        window.clear();
        window.display();
    }

    return 0;
}
