#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class Button : public sf::RectangleShape {
public:
    Button(const sf::Vector2f &size, const sf::Vector2f &position, const sf::Color &color, std::function<void()> callback = nullptr);
    ~Button() = default;

    void setCallback(std::function<void()> callback);
    bool isPressed(const sf::Vector2i &pos) const;

    void operator()() const { mCallback(); }

private:
    std::function<void()> mCallback;
};
