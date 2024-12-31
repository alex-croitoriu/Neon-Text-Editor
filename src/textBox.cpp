#include "helpers.hpp"
#include "globals.hpp"
#include "textBox.hpp"
#include "config.hpp"

TextBox::TextBox(const std::string &_content, const sf::Vector2f &position, bool outline)
{
    container.setPosition(position);
    container.setFillColor(currentThemeColors.textBoxBackground);
    container.setOutlineColor(currentThemeColors.textBoxOutline);
    container.setOutlineThickness(outline ? -1 : 0);

    content = sf::Text(_content, font, textBoxFontSize);
    content.setFillColor(currentThemeColors.text);
    content.setLetterSpacing(textBoxLetterSpacing);

    container.setSize(sf::Vector2f(content.getLocalBounds().getSize().x + 2 * textBoxPaddingX, textBoxHeight));

    Helpers::centerContentInsideContainer(container, content, true, false, textBoxPaddingY, 0);
}

void TextBox::setContent(const std::string &_content)
{
    content.setString(_content);
    container.setSize(sf::Vector2f(content.getLocalBounds().getSize().x + 2 * textBoxPaddingX, textBoxHeight));
    Helpers::centerContentInsideContainer(container, content, true, false, textBoxPaddingY, 0);
}

void TextBox::setPosition(const sf::Vector2f &position)
{
    container.setPosition(position);
    Helpers::centerContentInsideContainer(container, content, true, false, textBoxPaddingY, 0);
}

sf::Vector2f TextBox::getSize()
{
    if (this != NULL)
        return container.getSize();
    return sf::Vector2f(0, 0);
}

void TextBox::updateThemeColors()
{
    container.setFillColor(currentThemeColors.textBoxBackground);
    container.setOutlineColor(currentThemeColors.textBoxOutline);
    content.setFillColor(currentThemeColors.text);
}

void TextBox::draw()
{
    window.draw(container);
    window.draw(content);
}
