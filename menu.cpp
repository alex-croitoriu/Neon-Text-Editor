#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

#include "button.hpp"
#include "menu.hpp"

Menu::Menu(Button *_toggleButton, int _buttonCount, std::string buttonLabels[], sf::Vector2f position, sf::Font &font)
{
    isOpen = false;

    toggleButton = _toggleButton;
    buttonCount = _buttonCount;

    sf::Vector2f size(150, 30);

    buttons = new Button*[buttonCount];
    for (int i = 0; i < buttonCount; i++)
    {
        sf::Vector2f pos(position.x, position.y + 30 * i);
        buttons[i] = new Button(buttonLabels[i], size, pos, font, 12, false);
    }

    container.setSize(sf::Vector2f(size.x, size.y * buttonCount));
    container.setPosition(position);
    container.setFillColor(sf::Color::Cyan);
}

bool Menu::isHovering(sf::RenderWindow &window)
{
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    return container.getGlobalBounds().contains(window.mapPixelToCoords(localPosition));
}

bool Menu::getIsOpen() 
{
    return isOpen;
}

int Menu::getButtonCount() 
{
    return buttonCount;
}

Button** Menu::getButtons()
{
    return buttons;
}

void Menu::setIsOpen(bool _isOpen)
{
    isOpen = _isOpen;
}

void Menu::toggle()
{
    isOpen = !isOpen;
}

void Menu::draw(sf::RenderWindow &window)
{
    if (!isOpen)
        toggleButton->draw(window);
    else
    {
        toggleButton->draw(window);
        window.draw(container);
        for (int i = 0; i < buttonCount; i++)
        {
            buttons[i]->draw(window);
        }
    }
}
