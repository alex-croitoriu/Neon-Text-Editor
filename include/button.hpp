#pragma once

#include <SFML/Graphics.hpp>

#include <string>

class Button
{
    sf::RectangleShape container;
    sf::Text content;
    bool small;
    
public:
    Button(const std::string &label, const sf::Vector2f &position, bool alignCenter = true, bool small = true);

    bool isHovering();
    void setLabel(const std::string &label);
    void setPosition(const sf::Vector2f &position);
    void setHoverState(bool isHovering);
    void updateThemeColors();
    void draw();
};
