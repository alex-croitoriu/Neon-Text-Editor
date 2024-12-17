#include <SFML/Graphics.hpp>

#include <string>

#include "button.hpp"

Button::Button(std::string& label, sf::Vector2f& size, sf::Vector2f& position, int fontSize) //, std::function<void> _onClick = nullptr
{
    // onClick = _onClick;

    sf::Font font;
    font.loadFromFile("assets/fonts/cour.ttf");

    container.setSize(size);
    container.setPosition(position);
    container.setFillColor(sf::Color(0, 0, 0, 0));

    content.setString(label);
    content.setFont(font);
    content.setCharacterSize(fontSize);
    content.setStyle(sf::Text::Bold);
    content.setFillColor(sf::Color::Black);

    content.setPosition
    (
        (2 * container.getGlobalBounds().left + container.getGlobalBounds().width) / 2.0 - content.getLocalBounds().width / 2.0,
        (2 * container.getGlobalBounds().top + container.getGlobalBounds().height) / 2.0 - content.getLocalBounds().height / 2.0
    );
}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(container);
    window.draw(content);
}

void Button::setTexture(const sf::Texture* texture)
{
    container.setTexture(texture);
}

void Button::setOpacity(bool isHovering)
{
    container.setFillColor(sf::Color(0, 0, 0, isHovering ? 32 : 0));
}

bool Button::isHovering(sf::RenderWindow &window)
{
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    return getGlobalBounds().contains(window.mapPixelToCoords(localPosition));
}

sf::FloatRect Button::getGlobalBounds()
{
    return container.getGlobalBounds();
}

