#pragma once

#include <SFML/Graphics.hpp>
#include <string>

enum ButtonSize
{
    SMALL,
    MEDIUM,
    LARGE,
    EXTRA_LARGE
};

class Button
{
    sf::RectangleShape container;
    sf::Text contentLeft, contentRight;
    std::pair<std::string, std::string> label;
    ButtonSize size;
    bool centerX, centerY;

public:
    Button(const std::string &label, const sf::Vector2f &position, const bool &outline = false, const ButtonSize &_size = ButtonSize::MEDIUM, const bool &centerX = true, const bool &centerY = true);
    Button(const std::pair<std::string, std::string> &_label, const sf::Vector2f &position, const bool &outline = false, const ButtonSize &_size = ButtonSize::MEDIUM, const bool &centerX = true, const bool &centerY = true);

    bool isHovering();
    bool isHovering(sf::RenderWindow &window);
    void setLabel(const std::string &_label);
    void setLabel(const std::pair<std::string, std::string> &_label);
    void setOutline(const bool &outline);
    void setPosition(const sf::Vector2f &position);
    void setHoverState(const bool &isHovering);
    void setIsActive(const bool &isActive);
    sf::Vector2f getPosition();
    void updateThemeColors();
    void draw();
    void draw(sf::RenderWindow &window);
};

extern Button *zoomOutButton, *zoomInButton;
