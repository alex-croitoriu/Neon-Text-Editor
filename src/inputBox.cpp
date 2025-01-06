#include "helpers.hpp"
#include "globals.hpp"
#include "inputBox.hpp"
#include "config.hpp"
#include "windows.hpp"

InputBox::InputBox(const std::string &_content, const sf::Vector2f &position, const sf::Vector2f &size, const bool &outline)
{
    cursorTimer = 0;

    container.setPosition(position);
    container.setFillColor(currentThemeColors.textBoxBackground);
    container.setOutlineColor(currentThemeColors.textBoxOutline);
    container.setOutlineThickness(outline ? -1 : 0);

    content = sf::Text(_content, globalFont, 16);
    content.setFillColor(currentThemeColors.text);
    content.setLetterSpacing(textBoxLetterSpacing);

    container.setSize(size);
    cursorBox.setSize(sf::Vector2f(1, 18));
    cursorBox.setPosition(container.getPosition() + sf::Vector2f(8 + content.getGlobalBounds().getSize().x, 3));

    Helpers::centerContentInsideContainer(container, content, false, false, 2, 0, 0, 7);
}

bool InputBox::isHovering()
{
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    return container.getGlobalBounds().contains(window.mapPixelToCoords(localPosition));
}

bool InputBox::isHovering(sf::RenderWindow &window)
{
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    return container.getGlobalBounds().contains(window.mapPixelToCoords(localPosition));
}

void InputBox::setContent(const std::string &_content)
{
    content.setString(_content);
}

void InputBox::setIsActive(const bool &_isActive)
{
    isActive = _isActive;
    cursorTimer = 0;
    container.setFillColor((isActive || isHovering(goToLineWindow::window) || isHovering(findWindow::window) || isHovering(replaceWindow::window)) ? currentThemeColors.buttonHover : currentThemeColors.buttonBackground);
}

void InputBox::setHoverState(const bool &isHovering)
{
    container.setFillColor(isHovering || isActive ? currentThemeColors.buttonHover : currentThemeColors.buttonBackground);
}

std::string InputBox::getContent()
{
    return content.getString();
}

bool InputBox::getIsActive()
{
    return isActive;
}

void InputBox::updateThemeColors()
{
    container.setFillColor(currentThemeColors.textBoxBackground);
    container.setOutlineColor(currentThemeColors.textBoxOutline);
    content.setFillColor(currentThemeColors.text);
}

void InputBox::handleInput(sf::RenderWindow &window, sf::Event event, const bool &digitsOnly)
{
    std::string text = getContent();

    if (event.type == sf::Event::TextEntered)
    {
        int ch = event.text.unicode;

        if (ch == 8)
        {
            if (text.size())
                text.pop_back();
        }
        else 
        {
            if (digitsOnly)
            {
                // digits only
                if (ch >= 48 && ch <= 57)
                    text += ch;
            }
            // printable ascii characters only
            else if (ch >= 32 && ch <= 126)
                text += ch;
        }
    }

    setContent(text);
    cursorBox.setPosition(container.getPosition() + sf::Vector2f(8 + content.getGlobalBounds().getSize().x, 3));
}

void InputBox::updateCursorTimer()
{
    cursorTimer++;
    cursorTimer %= timeUnit * 2;

    if (cursorTimer % (timeUnit * 2) <= timeUnit)
        cursorBox.setFillColor(currentThemeColors.text);
    else if (cursorTimer % (timeUnit * 2) != 0)
        cursorBox.setFillColor(currentThemeColors.buttonHover);
}

void InputBox::draw()
{
    window.draw(container);
    window.draw(content);
    if (isActive)
        window.draw(cursorBox);
}

void InputBox::draw(sf::RenderWindow &window)
{
    window.draw(container);
    window.draw(content);
    if (isActive)
        window.draw(cursorBox);
}
