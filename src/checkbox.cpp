#include "checkbox.hpp"
#include "globals.hpp"
#include "helpers.hpp"
#include "windows.hpp"

CheckBox::CheckBox(const sf::Vector2f &position)
{
    isChecked = false;
    container.setPosition(position);
    container.setSize(sf::Vector2f(16, 16));
    container.setFillColor(currentThemeColors.buttonBackground);
    container.setOutlineColor(currentThemeColors.buttonOutline);
    container.setOutlineThickness(-1);

    content = sf::Text("", checkmarkFont, 10);
    content.setFillColor(currentThemeColors.text);
}

bool CheckBox::isHovering()
{
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    return container.getGlobalBounds().contains(window.mapPixelToCoords(localPosition));
}

bool CheckBox::isHovering(sf::RenderWindow &window)
{
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    return container.getGlobalBounds().contains(window.mapPixelToCoords(localPosition));
}

void CheckBox::setHoverState(const bool &isHovering)
{
    container.setFillColor(isHovering ? currentThemeColors.buttonHover : currentThemeColors.buttonBackground);
}

bool CheckBox::getIsChecked()
{
    return isChecked;
}

void CheckBox::toggle()
{
    isChecked = !isChecked;
    container.setFillColor(isChecked || isHovering(findWindow::window) || isHovering(replaceWindow::window) ? currentThemeColors.buttonHover : currentThemeColors.buttonBackground);
    const wchar_t text[] = {0x2713, 0};
    if (isChecked)
        content.setString(text);
    else
        content.setString("");
    Helpers::centerContentInsideContainer(container, content);
}

void CheckBox::updateThemeColors()
{
    container.setFillColor(currentThemeColors.buttonBackground);
    container.setOutlineColor(currentThemeColors.buttonOutline);
    content.setFillColor(currentThemeColors.text);
}

void CheckBox::draw()
{
    window.draw(container);
    window.draw(content);
}

void CheckBox::draw(sf::RenderWindow &window)
{
    window.draw(container);
    window.draw(content);
}
