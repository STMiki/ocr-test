#include "Button.hpp"

Button::Button(const sf::Vector2f &size, const sf::Vector2f &position, const sf::Color &color, std::function<void()> callback):
    sf::RectangleShape(size),
    mCallback(std::move(callback))
{
    setPosition(position);
    setFillColor(color);
}

bool Button::isPressed(const sf::Vector2i &pos) const { return getGlobalBounds().contains(pos.x, pos.y); }
void Button::setCallback(std::function<void()> callback) { mCallback = std::move(callback); }
