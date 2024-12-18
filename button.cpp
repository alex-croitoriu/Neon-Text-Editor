#include <SFML/Graphics.hpp>

#include <string>

#include "button.hpp"

Button::Button(std::string  &label, sf::Vector2f &size, sf::Vector2f &position, sf::Font &font, int fontSize, bool alignCenter) //, std::function<void> _onClick = nullptr
{
    // onClick = _onClick;

    container.setSize(size);
    container.setPosition(position);
    container.setFillColor(sf::Color(0, 0, 0, 0));

    content = sf::Text(label, font, fontSize);
    content.setStyle(sf::Text::Bold);
    content.setFillColor(sf::Color::Black);

    if (alignCenter) 
    {
        content.setOrigin(content.getGlobalBounds().getSize() / 2.f + content.getLocalBounds().getPosition());
        content.setPosition(container.getPosition() + container.getSize() / 2.f);
    }
    else
    {
        content.setOrigin(0, content.getGlobalBounds().getSize().y / 2.f + content.getLocalBounds().getPosition().y);
        content.setPosition(container.getGlobalBounds().left + 20, container.getPosition().y + container.getSize().y / 2.f);
    }
}

bool Button::isHovering(sf::RenderWindow &window)
{
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    return getGlobalBounds().contains(window.mapPixelToCoords(localPosition));
}

std::string Button::getLabel()
{
    return label;
}

sf::FloatRect Button::getGlobalBounds()
{
    return container.getGlobalBounds();
}

void Button::setHoverState(bool isHovering)
{
    container.setFillColor(sf::Color(0, 0, 0, isHovering ? 32 : 0));
}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(container);
    window.draw(content);
}
