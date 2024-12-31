#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "button.hpp"

class Menu 
{
    bool isOpen;
    bool sideMenu;
    int buttonCount;
    sf::RectangleShape container;
    Button **buttons;
    Button *toggleButton;

public:
    Menu(const std::string &label, const std::vector<std::string> &buttonLabels, const sf::Vector2f &position, const bool &sideMenu = false);
    Menu(Button *_toggleButton, const std::vector<std::string> &buttonLabels, const sf::Vector2f &position, const bool &sideMenu = false);
    bool isHovering();
    bool getIsOpen();
    sf::Vector2f getPosition();
    int getButtonCount();
    Button* getToggleButton();
    Button** getButtons();
    void open();
    void close();
    void setPosition(const sf::Vector2f &position);
    void draw();
};

extern Menu **menus;
