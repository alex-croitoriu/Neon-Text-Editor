#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

#include "button.hpp"
#include "menu.hpp"

Menu::Menu(Button *_toggleButton, std::vector<std::string> &buttonLabels, sf::Vector2f position, sf::Font &font)
{
    isOpen = false;

    toggleButton = _toggleButton;

    sf::Vector2f size(20, 60);
    for (int i = 0; i < buttonLabels.size(); i++)
    {
        sf::Vector2f pos(position.x + 10, position.y + 10 + 30 * i);
        buttons.emplace_back(buttonLabels[i], size, pos, font, 12);
    }

    container.setSize(sf::Vector2f(100, 60));
    container.setPosition(position);
    container.setFillColor(sf::Color(209, 255, 255, 255));
    // container.setOutlineThickness(2);
    container.setOutlineColor(sf::Color::Black);
}

void Menu::toggle()
{
    isOpen = !isOpen;
}

bool Menu::getIsOpen() 
{
    return isOpen;
}

std::vector<Button> Menu::getButtons()
{
    return buttons;
}

void Menu::draw(sf::RenderWindow &window)
{
    if (!isOpen)
        toggleButton->draw(window);
    else
    {
        toggleButton->draw(window);
        window.draw(container);
        for (auto button : buttons)
            button.draw(window);
    }
}
