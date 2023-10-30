#pragma once

#include "Button.hpp"
#include "Ocr.hpp"
#include "config.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>

#ifndef SFML_SYSTEM_MACOS
#define WINDOW_CONFIG sf::Style::Fullscreen
#else
#define WINDOW_CONFIG sf::Style::Default
#endif

class Application {
public:
    Application();
    ~Application() = default;

    void addButton(Button &&button);
    void move(sf::Vector2i pos);
    bool checkCollisions(sf::Vector2i pos);
    void handleEvent();
    void run();

private:
    void handleOcrButton();
    void handleClearButton();
    void handleExitButton();

private:
    sf::RenderWindow mWindow;
    sf::RenderTexture mTexture;
    sf::Sprite mSprite;
    std::vector<Button> mButtons;
    // sf::RectangleShape saveButton;

    bool mPressed;
    Ocr mOcr;
};
