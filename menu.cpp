#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

#include "globals.hpp"
#include "button.hpp"
#include "menu.hpp"

Menu::Menu(Button *_toggleButton, std::vector<std::string> buttonLabels, sf::Vector2f position)
{
    isOpen = false;

    toggleButton = _toggleButton;
    buttonCount = buttonLabels.size();

    sf::Vector2f size(150, 30);

    buttons = new Button*[buttonCount];
    for (int i = 0; i < buttonCount; i++)
    {
        sf::Vector2f pos(position.x, position.y + 30 * i);
        buttons[i] = new Button(buttonLabels[i], size, pos, 12, false);
    }

    container.setSize(sf::Vector2f(size.x, size.y * buttonCount)); 
    container.setPosition(position);
    container.setFillColor(sf::Color::Cyan);
}

bool Menu::isHovering()
{
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    return container.getGlobalBounds().contains(window.mapPixelToCoords(localPosition));
}

bool Menu::getIsOpen() 
{
    return isOpen;
}

sf::Vector2f Menu::getPosition()
{
    return container.getPosition();
}

int Menu::getButtonCount() 
{
    return buttonCount;
}

Button** Menu::getButtons()
{
    return buttons;
}

Button* Menu::getToggleButton()
{
    return toggleButton;
}

void Menu::setIsOpen(bool _isOpen)
{
    isOpen = _isOpen;
}

void Menu::setPosition(sf::Vector2f position, int windowWidth, int windowHeight)
{
    sf::Vector2f size(container.getGlobalBounds().width, container.getGlobalBounds().height);

    if (position.x + size.x > windowWidth)
        position.x = windowWidth - size.x;
    if (position.y + size.y > windowHeight)
        position.y = windowHeight - size.y;

    container.setPosition(position);
    for (int i = 0; i < buttonCount; i++)
    {
        sf::Vector2f pos(position.x, position.y + 30 * i);
        buttons[i]->setPosition(pos);
    }
}

void Menu::toggle()
{
    isOpen = !isOpen;
}

void Menu::draw()
{
    if (!isOpen)
        toggleButton->draw();
    else
    {
        toggleButton->draw();
        window.draw(container);
        for (int i = 0; i < buttonCount; i++)
        {
            buttons[i]->draw();
        }
    }
}
