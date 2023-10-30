#pragma once

#include "config.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/BlendMode.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

class Line : public sf::Drawable {
public:
    Line(const sf::Vector2f &point1, const sf::Vector2f &point2, float thickness = 5.f, sf::Color color = sf::Color::Yellow):
        thickness(thickness),
        point1(point1),
        point2(point2)
    {
        direction = point2 - point1;
        unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
        unitPerpendicular = {-unitDirection.y, unitDirection.x};

        update();
        setColor(color);
    }

    void draw(sf::RenderTarget &target, UNUSED sf::RenderStates states) const
    {
        auto point = sf::CircleShape();
        point.setRadius(thickness / 2.f);
        point.setPointCount(30);
        point.setFillColor(vertices[0].color);
        point.setOrigin(point.getRadius(), point.getRadius());
        point.setPosition(point1);
        target.draw(point);
        point.setPosition(point2);
        target.draw(point);
        target.draw(vertices, 4, sf::Quads);
    }
    void setThickness(float thickness) { this->thickness = thickness; }

    void setColor(sf::Color color)
    {
        for (int i = 0; i < 4; ++i)
            vertices[i].color = color;
    }

private:
    void update()
    {
        sf::Vector2f offset = (thickness / 2.f) * unitPerpendicular;

        vertices[0].position = point1 + offset;
        vertices[1].position = point2 + offset;
        vertices[2].position = point2 - offset;
        vertices[3].position = point1 - offset;
    }

private:
    sf::Vertex vertices[4];
    float thickness;

    sf::Vector2f point1;
    sf::Vector2f point2;
    sf::Vector2f direction;
    sf::Vector2f unitDirection;
    sf::Vector2f unitPerpendicular;
};
