#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

#include "button.hpp"

class Menu 
{
    bool isOpen;
    sf::RectangleShape container;
    std::string label;
    Button *toggleButton;
    std::vector<Button*> buttons;

public:
    Menu(std::string &_title);
    void setIsOpen(bool _isOpen);
    void addButton(Button &button);
};