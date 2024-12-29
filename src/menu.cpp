#include <SFML/Graphics.hpp>

#include "menu.hpp"
#include "globals.hpp"
#include "config.hpp"

Menu::Menu(const std::string &label, const std::vector<std::string> &buttonLabels, const sf::Vector2f &position)
{
    isOpen = false;

    // the position parameter is the top left corner of the menu itself, so the toggle button has to go above it
    toggleButton = new Button(label, sf::Vector2f(position.x, position.y - buttonSizeMapping.at(ButtonSize::MEDIUM).size.y));
    buttonCount = buttonLabels.size();

    ButtonProperties properties = buttonSizeMapping.at(ButtonSize::LARGE);

    buttons = new Button*[buttonCount];
    for (int i = 0; i < buttonCount; i++)
    {
        sf::Vector2f buttonPosition(position.x + buttonSizeMapping.at(ButtonSize::MEDIUM).size.x, position.y + (properties.size.y - 1) * i);
        buttons[i] = new Button(buttonLabels[i], buttonPosition, ButtonSize::LARGE, false);
    }

    container.setSize(sf::Vector2f(properties.size.x, (properties.size.y - 1) * buttonCount + 1)); 
    container.setPosition(position);
    container.setFillColor(sf::Color(141, 171, 204));
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

    ButtonProperties properties = buttonSizeMapping.at(ButtonSize::LARGE);

    if (boundedPosition.x + size.x > windowWidth)
        boundedPosition.x = windowWidth - size.x;
    if (boundedPosition.y + size.y > windowHeight)
        boundedPosition.y = windowHeight - size.y;

    container.setPosition(boundedPosition);
    for (int i = 0; i < buttonCount; i++)
    {
        sf::Vector2f buttonPosition(boundedPosition.x, boundedPosition.y + (properties.size.y - 1) * i);
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
            buttons[i]->draw();
    }
}
