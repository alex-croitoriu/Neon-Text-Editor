#include "globals.hpp"
#include "button.hpp"
#include "config.hpp"
#include "helpers.hpp"

Button::Button(const std::string &label, const sf::Vector2f &position, const ButtonSize &_size, const bool &_alignCenter)
{
    size = _size;
    alignCenter = _alignCenter;

    ButtonProperties properties = buttonSizeMapping.at(size);

    container.setSize(properties.size);
    container.setPosition(position);
    container.setFillColor(currentThemeColors.buttonBackground);
    container.setOutlineColor(currentThemeColors.buttonOutline);
    container.setOutlineThickness(properties.outlineThickness);

    content = sf::Text(label, font, properties.fontSize);
    content.setStyle(sf::Text::Bold);
    content.setFillColor(currentThemeColors.text);
    content.setLetterSpacing(properties.letterSpacing);

    if (alignCenter) 
        Helpers::centerContentInsideContainer(container, content);
    else
        Helpers::centerContentInsideContainer(container, content, true, false, 0, 20);
}

bool Button::isHovering()
{
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    return container.getGlobalBounds().contains(window.mapPixelToCoords(localPosition));
}

void Button::setLabel(const std::string &label)
{
    content.setString(label);
}

void Button::setPosition(const sf::Vector2f &position)
{
    container.setPosition(position);
    if (alignCenter) 
        Helpers::centerContentInsideContainer(container, content);
    else
        Helpers::centerContentInsideContainer(container, content, true, false, 0, 20);
}

void Button::setHoverState(bool isHovering)
{
    container.setFillColor(isHovering ? currentThemeColors.buttonHover : currentThemeColors.buttonBackground);
}

void Button::updateThemeColors()
{
    container.setFillColor(currentThemeColors.buttonBackground);
    container.setOutlineColor(currentThemeColors.buttonOutline);
    content.setFillColor(currentThemeColors.text);
}

void Button::draw()
{
    window.draw(container);
    window.draw(content);
}
