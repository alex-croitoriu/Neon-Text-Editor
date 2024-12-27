#include <SFML/Graphics.hpp>

#include "globals.hpp"
#include "button.hpp"
#include "menu.hpp"

Menu::Menu(Button *_toggleButton, const std::vector<std::string> &buttonLabels, const sf::Vector2f &position)
{
    isOpen = false;

    toggleButton = _toggleButton;
    buttonCount = buttonLabels.size();

    sf::Vector2f size(150, 30);

    buttons = new Button*[buttonCount];
    for (int i = 0; i < buttonCount; i++)
    {
        sf::Vector2f buttonPosition(position.x, position.y + 30 * i);
        buttons[i] = new Button(buttonLabels[i], buttonPosition, false, false);
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

Button* Menu::getToggleButton()
{
    return toggleButton;
}

Button** Menu::getButtons()
{
    return buttons;
}

void Menu::open()
{
    isOpen = true;
}

void Menu::close()
{
    isOpen = false;
}

void Menu::setPosition(const sf::Vector2f &position)
{
    sf::Vector2f size(container.getGlobalBounds().width, container.getGlobalBounds().height);

    sf::Vector2f boundedPosition = position;

    if (boundedPosition.x + size.x > windowWidth)
        boundedPosition.x = windowWidth - size.x;
    if (boundedPosition.y + size.y > windowHeight)
        boundedPosition.y = windowHeight - size.y;

    container.setPosition(boundedPosition);
    for (int i = 0; i < buttonCount; i++)
    {
        sf::Vector2f buttonPosition(boundedPosition.x, boundedPosition.y + 30 * i);
        buttons[i]->setPosition(buttonPosition);
    }
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
