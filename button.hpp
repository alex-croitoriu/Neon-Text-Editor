#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <functional>

class Button
{
    sf::RectangleShape container;
    sf::Text content;
    sf::Texture texture;

public:
    Button(const std::string &label, const sf::Vector2f &size, const sf::Vector2f &position, int fontSize, bool alignCenter = true);

    bool isHovering();
    
    sf::FloatRect getGlobalBounds();

    void setLabel(const std::string &_label);
    void setPosition(const sf::Vector2f &position);
    void setHoverState(bool isHovering);
    
    void draw();

};
