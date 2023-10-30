#include "Ocr.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/WindowStyle.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Thread.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <tesseract/baseapi.h>

#define UNUSED __attribute__((unused))

#ifndef SFML_SYSTEM_MACOS
#define CREATE_WINDOW(videomode, title) sf::RenderWindow(videomode, title, sf::Style::Fullscreen)
#else
#define CREATE_WINDOW(videomode, title) sf::RenderWindow(videomode, title, sf::Style::Default)
#endif

void move(const sf::Window &window, sf::RenderTexture &texture, UNUSED sf::Vector2i pos)
{
    auto circle = sf::CircleShape(10);
    circle.setFillColor(sf::Color::White);
    circle.setPosition(pos.x, window.getSize().y - pos.y);
    texture.draw(std::move(circle));
    std::cout << "Moving to " << pos.x << ", " << pos.y << std::endl;
}

bool checkCollisions(UNUSED sf::Vector2i pos) { return false; }

int main()
{
    tesseract::TessBaseAPI api = tesseract::TessBaseAPI();
    std::cout << "Hello, World!" << std::endl;
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    std::string title = "Ocr test";
    sf::RenderWindow window = CREATE_WINDOW(videoMode, title);
    sf::RenderTexture texture;
    sf::Sprite sprite;
    Ocr ocr;

    window.setFramerateLimit(240);
    texture.create(window.getSize().x, window.getSize().y, sf::ContextSettings());
    sprite.setTexture(texture.getTexture());

    bool pressed = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                texture.clear();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                auto texts = ocr.getTextFromImage(texture.getTexture());
                if (texts.empty())
                    std::cout << "No text found" << std::endl;
                for (auto &text : texts)
                    std::cout << text << std::endl;
            }

            if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::TouchBegan) {
                if (checkCollisions({event.mouseButton.x, event.mouseButton.y})) [[unlikely]]
                    continue;
                pressed = true;
                move(window, texture, {event.mouseButton.x, event.mouseButton.y});
            } else if (event.type == sf::Event::MouseButtonReleased || event.type == sf::Event::TouchEnded) {
                pressed = false;
                move(window, texture, {event.mouseButton.x, event.mouseButton.y});
            } else if (event.type == sf::Event::MouseMoved || event.type == sf::Event::TouchMoved) {
                if (pressed)
                    move(window, texture, {event.mouseMove.x, event.mouseMove.y});
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
