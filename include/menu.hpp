#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "button.hpp"

class Menu 
{
    bool isOpen, isSideMenu;
    int buttonCount;
    sf::RectangleShape container;
    Button **buttons;
    Button *toggleButton;

public:
    Menu(const std::string &label, const std::vector<std::pair<std::string, std::string>> &buttonLabels, const sf::Vector2f &position, const bool &isSideMenu = false);
    Menu(Button *_toggleButton, const std::vector<std::pair<std::string, std::string>> &buttonLabels, const sf::Vector2f &position, const bool &isSideMenu = false);
    bool isHovering();
    bool isHovering(sf::RenderWindow &window);
    bool getIsOpen();
    sf::Vector2f getPosition();
    int getButtonCount();
    Button* getToggleButton();
    Button** getButtons();
    void open();
    void close();
    void setPosition(const sf::Vector2f &position);
    void draw();
    void draw(sf::RenderWindow &window);
};

extern Menu **menus;
