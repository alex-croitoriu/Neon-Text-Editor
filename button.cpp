#include <SFML/Graphics.hpp>
#include <string>
#include "button.hpp"

using namespace std;

Button::Button(string& string, sf::Font& font, sf::Vector2f& size, sf::Vector2f& position)
{
    container.setSize(size);
    container.setPosition(position);
    container.setFillColor(sf::Color(0, 0, 0, 0));

    content.setString(string);
    content.setFont(font);
    content.setCharacterSize(13);
    content.setStyle(sf::Text::Bold);
    content.setFillColor(sf::Color::Black);

    sf::Vector2f center(
        ((2 * container.getGlobalBounds().left + container.getGlobalBounds().width) / 2.0),
        ((2 * container.getGlobalBounds().top + container.getGlobalBounds().height) / 2.0)
    );

    content.setPosition
    (
        center.x - content.getLocalBounds().width / 2.0,
        center.y - content.getLocalBounds().height / 2.0
    );
}

void Button::setTexture(const sf::Texture* texture)
{
    container.setTexture(texture);
}

sf::FloatRect Button::getGlobalBounds()
{
    return container.getGlobalBounds();
}

bool Button::isInside(sf::RenderWindow& window)
{
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    return getGlobalBounds().contains(window.mapPixelToCoords(localPosition));
}

void Button::setOpacity(bool hover)
{
    container.setFillColor(sf::Color(0, 0, 0, hover ? 32 : 0));
}
