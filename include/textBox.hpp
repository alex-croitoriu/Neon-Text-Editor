#pragma once

#include <SFML/Graphics.hpp>

#include <string>

class TextBox
{
    sf::RectangleShape container;
    sf::Text content;
    
public:
    TextBox(const std::string &label, const sf::Vector2f &position);

    void setContent(const std::string &_content);
    void setPosition(const sf::Vector2f &position);
    void updateThemeColors();
    void draw();
};
