#include "globals.hpp"
#include "textBox.hpp"
#include "config.hpp"

TextBox::TextBox(const std::string &_content, const sf::Vector2f &position)
{
    container.setSize(smallButtonSize);
    container.setPosition(position);
    container.setFillColor(currentThemeColors.button);
    container.setOutlineColor(currentThemeColors.buttonOutline);
    // container.setOutlineThickness(-1);

    content = sf::Text(_content, font, smallButtonFontSize);
    content.setStyle(sf::Text::Bold);
    content.setFillColor(currentThemeColors.text);
    content.setLetterSpacing(smallButtonLetterSpacing);

    content.setOrigin(int(content.getGlobalBounds().getSize().x / 2.f + content.getLocalBounds().getPosition().x), int(content.getGlobalBounds().getSize().y / 2.f + content.getLocalBounds().getPosition().y));
    content.setPosition(int(container.getPosition().x + container.getSize().x / 2.f), int(container.getPosition().y + container.getSize().y / 2.f));
}

void TextBox::setContent(const std::string &_content)
{
    content.setString(_content);
}

void TextBox::setPosition(const sf::Vector2f &position)
{
    container.setPosition(position);
    content.setOrigin(0, int(content.getGlobalBounds().getSize().y / 2.f + content.getLocalBounds().getPosition().y));
    content.setPosition(int(container.getGlobalBounds().left + 20), int(container.getPosition().y + container.getSize().y / 2.f));
}

void TextBox::updateThemeColors()
{
    container.setFillColor(currentThemeColors.button);
    content.setFillColor(currentThemeColors.text);
}

void TextBox::draw()
{
    window.draw(container);
    window.draw(content);
}
