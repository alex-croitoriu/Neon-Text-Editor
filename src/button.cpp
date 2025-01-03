#include "globals.hpp"
#include "helpers.hpp"
#include "config.hpp"
#include "button.hpp"

Button::Button(const std::string &_label, const sf::Vector2f &position, const bool &outline, const ButtonSize &_size, const bool &_centerX, const bool &_centerY)
{
    size = _size;
    centerX = _centerX;
    centerY = _centerY;
    label = make_pair(_label, "");

    ButtonProperties properties = buttonSizeMapping.at(size);

    container.setSize(properties.size);
    container.setPosition(position);
    container.setFillColor(currentThemeColors.buttonBackground);
    container.setOutlineColor(currentThemeColors.buttonOutline);
    container.setOutlineThickness(outline ? -1 : 0);

    contentLeft = sf::Text(_label, globalFont, properties.fontSize);
    contentLeft.setFillColor(currentThemeColors.text);
    contentLeft.setLetterSpacing(properties.letterSpacing);

    Helpers::centerContentInsideContainer(container, contentLeft, centerX, centerY, 3, 20, 0, 0);
}

Button::Button(const std::pair<std::string, std::string> &_label, const sf::Vector2f &position, const bool &outline, const ButtonSize &_size, const bool &_centerX, const bool &_centerY)
{
    size = _size;
    centerX = _centerX;
    centerY = _centerY;
    label = _label;

    ButtonProperties properties = buttonSizeMapping.at(size);

    container.setSize(properties.size);
    container.setPosition(position);
    container.setFillColor(currentThemeColors.buttonBackground);
    container.setOutlineColor(currentThemeColors.buttonOutline);
    container.setOutlineThickness(outline ? -1 : 0);

    contentLeft = sf::Text(label.first, globalFont, properties.fontSize);
    contentRight = sf::Text(label.second, globalFont, properties.fontSize);
    contentLeft.setFillColor(currentThemeColors.text);
    contentLeft.setLetterSpacing(properties.letterSpacing);
    contentRight.setFillColor(currentThemeColors.text);
    contentRight.setLetterSpacing(properties.letterSpacing);

    Helpers::centerContentInsideContainer(container, contentLeft, centerX, centerY, 5, 0, 0, 20);
    Helpers::centerContentInsideContainer(container, contentRight, centerX, centerY, 5, 20, 0, 0);
}

bool Button::isHovering()
{
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    return container.getGlobalBounds().contains(window.mapPixelToCoords(localPosition));
}

void Button::setLabel(const std::string &_label)
{
    label = std::make_pair(_label, "");
    contentLeft.setString(label.first);
    contentRight.setString(label.second);
}

void Button::setLabel(const std::pair<std::string, std::string> &_label)
{
    label = _label;
    contentLeft.setString(label.first);
    contentRight.setString(label.second);
}

void Button::setOutline(const bool &outline)
{
    container.setOutlineThickness(outline ? -1 : 0);
}

void Button::setPosition(const sf::Vector2f &position)
{
    container.setPosition(position);
    Helpers::centerContentInsideContainer(container, contentLeft, centerX, centerY, 5, 0, 0, 20);
    Helpers::centerContentInsideContainer(container, contentRight, centerX, centerY, 5, 20, 0, 0);
}

void Button::setHoverState(const bool &isHovering)
{
    container.setFillColor(isHovering ? currentThemeColors.buttonHover : currentThemeColors.buttonBackground);
}

void Button::setIsActive(const bool &isActive)
{
    const wchar_t text[] = {0x2713, 0};
    contentRight.setFont(checkmarkFont);
    contentRight.setCharacterSize(18);

    contentLeft.setString(label.first);

    if (isActive)
        contentRight.setString(text);
    else
        contentRight.setString("");

    Helpers::centerContentInsideContainer(container, contentLeft, centerX, centerY, 5, 0, 0, 20);
    Helpers::centerContentInsideContainer(container, contentRight, centerX, centerY, 3, 20, 0, 0);
}

sf::Vector2f Button::getPosition()
{
    return container.getPosition();
}

void Button::updateThemeColors()
{
    container.setFillColor(currentThemeColors.buttonBackground);
    container.setOutlineColor(currentThemeColors.buttonOutline);
    contentLeft.setFillColor(currentThemeColors.text);
    contentRight.setFillColor(currentThemeColors.text);
}

void Button::draw()
{
    window.draw(container);
    window.draw(contentLeft);
    window.draw(contentRight);
}
