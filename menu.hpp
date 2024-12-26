#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

#include "button.hpp"

class Menu 
{
    bool isOpen;
    int buttonCount;
    sf::RectangleShape container;
    Button **buttons;
    Button *toggleButton;

public:
    Menu(Button *_toggleButton, std::vector<std::string> buttonLabels, sf::Vector2f position);

    bool isHovering();

    bool getIsOpen();
    sf::Vector2f getPosition();
    int getButtonCount();
    Button** getButtons();
    Button* getToggleButton();

    void setIsOpen(bool _isOpen);
    void setPosition(sf::Vector2f position, int windowWidth, int windowHeight);
    void toggle();

    void draw();
};
