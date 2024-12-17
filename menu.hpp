#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

#include "button.hpp"

class Menu 
{
    bool isOpen;
    sf::RectangleShape container;
    std::vector<Button> buttons;
    Button *toggleButton;

public:
    Menu(Button *_toggleButton, std::vector<std::string> &buttonLabels, sf::Vector2f position, sf::Font &font);
    void toggle();
    bool getIsOpen();
    std::vector<Button> getButtons();
    void draw(sf::RenderWindow &window);
};
