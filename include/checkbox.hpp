#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class CheckBox
{
    sf::RectangleShape container;
    sf::Text content;
    bool isChecked;
public:
    CheckBox(const sf::Vector2f &position);
    bool isHovering();
    bool isHovering(sf::RenderWindow &window);
    void setHoverState(const bool &isHovering);
    bool getIsChecked();
    void toggle();
    void updateThemeColors();
    void draw();
    void draw(sf::RenderWindow &window);
};
