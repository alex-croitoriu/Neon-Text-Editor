#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <functional>

class Button
{
    sf::RectangleShape container;
    sf::Text content;
    sf::Texture texture;
    std::string label;

public:
    Button(std::string &label, sf::Vector2f &size, sf::Vector2f &position, sf::Font &font, int fontSize, bool alignCenter = true); //, std::function<void> _onClick

    bool isHovering(sf::RenderWindow &window);
    
    std::string getLabel();
    sf::FloatRect getGlobalBounds();

    void setPosition(sf::Vector2f position);
    void setHoverState(bool isHovering);
    
    void draw(sf::RenderWindow &window);

};
