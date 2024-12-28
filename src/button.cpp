#include "globals.hpp"
#include "button.hpp"
#include "config.hpp"

Button::Button(const std::string &label, const sf::Vector2f &position, bool alignCenter, bool _small)
{
    small = _small;

    container.setSize(small ? smallButtonSize : buttonSize);
    container.setPosition(position);
    container.setFillColor(currentThemeColors.button);
    container.setOutlineColor(currentThemeColors.buttonOutline);
    container.setOutlineThickness(small ? 0 : -1);

    content = sf::Text(label, font, small ? smallButtonFontSize : buttonFontSize);
    content.setStyle(sf::Text::Bold);
    content.setFillColor(currentThemeColors.text);
    content.setLetterSpacing(small ? smallButtonLetterSpacing : buttonLetterSpacing);

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
    return container.getGlobalBounds().contains(window.mapPixelToCoords(localPosition));
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
    container.setFillColor(isHovering ? currentThemeColors.buttonHover : currentThemeColors.button);
}

void Button::updateThemeColors()
{
    container.setFillColor(currentThemeColors.button);
    content.setFillColor(currentThemeColors.text);
}

void Button::draw()
{
    window.draw(container);
    window.draw(content);
}
