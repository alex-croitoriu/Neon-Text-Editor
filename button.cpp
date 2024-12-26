#include <SFML/Graphics.hpp>

#include <string>

#include "globals.hpp"
#include "button.hpp"

Button::Button(const std::string &label, const sf::Vector2f &size, const sf::Vector2f &position, int fontSize, bool alignCenter)
{
    container.setSize(size);
    container.setPosition(position);
    container.setFillColor(sf::Color(0, 0, 0, 0));

    content = sf::Text(label, font, fontSize);
    content.setStyle(sf::Text::Bold);
    content.setFillColor(sf::Color::Black);

    if (alignCenter) 
    {
        content.setOrigin(int(content.getGlobalBounds().getSize().x / 2.f + content.getLocalBounds().getPosition().x), int(content.getGlobalBounds().getSize().y / 2.f + content.getLocalBounds().getPosition().y));
        content.setPosition(int(container.getPosition().x + container.getSize().x / 2.f), int(container.getPosition().y + container.getSize().y / 2.f));
    }
    else
    {
        content.setOrigin(0, int(content.getGlobalBounds().getSize().y / 2.f + content.getLocalBounds().getPosition().y));
        content.setPosition(int(container.getGlobalBounds().left + 20), int(container.getPosition().y + container.getSize().y / 2.f));
    }
}

bool Button::isHovering()
{
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    return getGlobalBounds().contains(window.mapPixelToCoords(localPosition));
}

sf::FloatRect Button::getGlobalBounds()
{
    return container.getGlobalBounds();
}

void Button::setLabel(const std::string &label)
{
    content.setString(label);
}

void Button::setPosition(const sf::Vector2f &position)
{
    container.setPosition(position);
    content.setOrigin(0, int(content.getGlobalBounds().getSize().y / 2.f + content.getLocalBounds().getPosition().y));
    content.setPosition(int(container.getGlobalBounds().left + 20), int(container.getPosition().y + container.getSize().y / 2.f));
}

void Button::setHoverState(bool isHovering)
{
    container.setFillColor(sf::Color(0, 0, 0, isHovering ? 32 : 0));
}

void Button::draw()
{
    window.draw(container);
    window.draw(content);
}
