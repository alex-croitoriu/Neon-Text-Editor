#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

#include "button.hpp"
#include "menu.hpp"

Menu::Menu(std::string &_label)
{
    label = _label;
    // toggleButton = new Button(label);
}

void Menu::setIsOpen(bool _isOpen)
{
    isOpen = _isOpen;
}

void Menu::addButton(Button &button) 
{
    // buttons.emplace_back(button);
}