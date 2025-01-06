#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class InputBox
{
    sf::RectangleShape container, cursorBox;
    sf::Text content;
    bool isActive;
    int cursorTimer;

public:
    InputBox(const std::string &label, const sf::Vector2f &position, const sf::Vector2f &size, bool const &outline = true);

    bool isHovering();
    bool isHovering(sf::RenderWindow &window);
    void setIsActive(const bool &isActive);
    void setHoverState(const bool &isHovering);
    void setContent(const std::string &_content);
    std::string getContent();
    void updateThemeColors();
    bool getIsActive();
    void handleInput(sf::RenderWindow &window, sf::Event event, const bool &digitsOnly = false);
    void updateCursorTimer();
    void draw();
    void draw(sf::RenderWindow &window);
};
