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
    Button(std::string &label, sf::Vector2f &size, sf::Vector2f &position, sf::Font &font, int fontSize); //, std::function<void> _onClick
    // Button(std::string &label, sf::Vector2f &position, sf::Font &font, int fontSize); //, std::function<void> _onClick

    void draw(sf::RenderWindow &window);
    void setTexture(const sf::Texture *texture);
    void setOpacity(bool isHovering);
    bool isHovering(sf::RenderWindow &window);
    sf::FloatRect getGlobalBounds();
};
