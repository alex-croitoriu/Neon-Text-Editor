#pragma once

#include <SFML/Graphics.hpp>

#include "textBox.hpp"
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
    sf::Color buttonOutline;
    std::vector<sf::Color> cursor;
};

extern ThemeColors currentThemeColors;

extern int windowWidth;
extern int windowHeight;

extern bool showLineNumbers;
extern bool lightTheme;

extern int fontSize;

extern TextBox *lineColumnTextBox, *zoomLevelTextBox, *fontSizeTextBox, *selectedCharactersTextBox, *lineCountTextBox;

extern Button *zoomOutButton, *zoomInButton;

extern Menu **menus;
