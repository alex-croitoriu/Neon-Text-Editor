#pragma once

#include <SFML/Graphics.hpp>

extern sf::Font font;
extern sf::RenderWindow window;

struct ThemeColors 
{
    sf::Color background;
    sf::Color text;
    sf::Color separator;
    sf::Color lineHighlight;
    sf::Color selecHighlight;
    sf::Color button;
    sf::Color buttonHover;
    std::vector<sf::Color> cursor;
};

extern const ThemeColors themeColors[];
extern ThemeColors currentThemeColors;

extern int windowWidth;
extern int windowHeight;

extern bool showLineNumbers;
extern bool lightTheme;
