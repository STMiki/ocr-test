#include "Application.hpp"
#include "Line.hpp"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <iostream>

Application::Application():
    mWindow(sf::VideoMode::getDesktopMode(), "Ocr test", WINDOW_CONFIG),
    mTexture(),
    mSprite(),
    mPressed(false),
    mOcr()
{
    Button exitButton(sf::Vector2f(100, 100), sf::Vector2f(mWindow.getSize().x - 100, 0), sf::Color::Red);
    Button clearButton(sf::Vector2f(100, 100), sf::Vector2f(mWindow.getSize().x - 100, 100), sf::Color::Green);
    Button ocrButton(sf::Vector2f(100, 100), sf::Vector2f(mWindow.getSize().x - 100, 200), sf::Color::Blue);

    exitButton.setCallback(std::bind(&Application::handleExitButton, this));
    clearButton.setCallback(std::bind(&Application::handleClearButton, this));
    ocrButton.setCallback(std::bind(&Application::handleOcrButton, this));

    addButton(std::move(exitButton));
    addButton(std::move(clearButton));
    addButton(std::move(ocrButton));

    mTexture.create(mWindow.getSize().x, mWindow.getSize().y, sf::ContextSettings());
    mSprite.setTexture(mTexture.getTexture());
    mTexture.setSmooth(true);

    handleClearButton();
}

void Application::addButton(Button &&button) { mButtons.push_back(std::move(button)); }

void Application::move(sf::Vector2i pos)
{
    Line line(
        {static_cast<float>(mLastPos.x), static_cast<float>(mTexture.getSize().y - mLastPos.y)}, {static_cast<float>(pos.x), static_cast<float>(mTexture.getSize().y - pos.y)},
        20.f, sf::Color::Black
    );

    mTexture.draw(line);
    mLastPos = pos;
}

bool Application::checkCollisions(UNUSED sf::Vector2i pos)
{
    for (auto &button : mButtons) {
        if (button.isPressed(pos)) {
            button();
            return true;
        }
    }
    return false;
}

void Application::handleOcrButton()
{
    auto texts = mOcr.getTextFromImage(mTexture.getTexture());
    if (texts.empty())
        std::cout << "No text found" << std::endl;
    for (auto &text : texts)
        std::cout << text << std::endl;
}

void Application::handleClearButton()
{
    mTexture.clear();
    auto background = sf::RectangleShape(sf::Vector2f(mTexture.getSize().x, mTexture.getSize().y));
    background.setFillColor(sf::Color::White);
    mTexture.draw(background);
}

void Application::handleExitButton() { mWindow.close(); }

void Application::handleEvent()
{
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            handleExitButton();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            handleClearButton();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            handleOcrButton();
        }

        if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::TouchBegan) {
            if (checkCollisions({event.mouseButton.x, event.mouseButton.y})) [[unlikely]]
                continue;
            mPressed = true;
            mLastPos = {event.mouseButton.x, event.mouseButton.y};
        } else if (event.type == sf::Event::MouseButtonReleased || event.type == sf::Event::TouchEnded) {
            if (!mPressed)
                continue;
            mPressed = false;
            move({event.mouseButton.x, event.mouseButton.y});
        } else if (event.type == sf::Event::MouseMoved || event.type == sf::Event::TouchMoved) {
            if (!mPressed)
                continue;
            move({event.mouseMove.x, event.mouseMove.y});
        }
    }
}

void Application::run()
{
    while (mWindow.isOpen()) {
        handleEvent();

        mWindow.clear();
        mWindow.draw(mSprite);
        for (auto &button : mButtons)
            mWindow.draw(button);
        mWindow.display();
    }
}
