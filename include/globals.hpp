#pragma once

#include <SFML/Graphics.hpp>

#include "textBox.hpp"
#include "button.hpp"
#include "menu.hpp"

extern sf::Font font;
extern sf::RenderWindow window;

enum Theme
{
    LIGHT,
    DARK
};

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
    sf::Color textBox;
    sf::Color textBoxOutline;
    std::vector<sf::Color> cursor;
};

struct ButtonProperties
{
    sf::Vector2f size;
    float fontSize;
    float letterSpacing;
    float outlineThickness;
};

extern int windowWidth, windowHeight;

extern bool showLineNumbers;
extern Theme theme;
extern ThemeColors currentThemeColors;

extern int fontSize;
extern int zoomLevel;
extern float lineHeight;
extern bool wordWrap;
extern float marginLeft, paddingLeft;
extern std::pair<int, int> segmOnScreen[];

extern TextBox *lineColumnTextBox, *zoomLevelTextBox, *fontSizeTextBox, *selectedCharactersTextBox, *lineCountTextBox;
extern Button *zoomOutButton, *zoomInButton;
extern Menu **menus;
