#pragma once

#include <SFML/Graphics.hpp>

#include "button.hpp"
#include "menu.hpp"

extern sf::Font font;
extern sf::RenderWindow window;

struct ThemeColors 
{
    sf::Color background;
    sf::Color text;
    sf::Color separator;
    sf::Color lineNumbersBackground;
    sf::Color cursorLineHighlight;
    sf::Color selectHighlight;
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

extern Button *zoomOutButton, *zoomInButton;

extern Menu **menus;
