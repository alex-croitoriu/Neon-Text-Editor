#pragma once

#include <SFML/Graphics.hpp>

#include <string>

enum ButtonSize
{
    SMALL,
    MEDIUM,
    LARGE
};

class Button
{
    sf::RectangleShape container;
    sf::Text content;
    ButtonSize size;
    bool alignCenter;
    
public:
    Button(const std::string &label, const sf::Vector2f &position, const ButtonSize &_size = ButtonSize::MEDIUM, const bool &alignCenter = true);

    bool isHovering();
    void setLabel(const std::string &label);
    void setPosition(const sf::Vector2f &position);
    void setHoverState(bool isHovering);
    void updateThemeColors();
    void draw();
};
