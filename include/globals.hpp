#pragma once

#include <SFML/Graphics.hpp>

#include "textBox.hpp"
#include "button.hpp"
#include "menu.hpp"
#include "config.hpp"

extern sf::Font font;
extern sf::RenderWindow window;
extern sf::RectangleShape topSeparator, bottomSeparator, lineNumbersBackground, toolBarBackground, statusBarBackground, cursorBox, cursorLineHighlight, box;

extern int windowWidth, windowHeight;

extern bool showLineNumbers;
extern Theme theme;
extern ThemeColors currentThemeColors;

extern int fontSize;
extern int zoomLevel;
extern float lineHeight;
extern bool wordWrap;
extern float marginLeft, paddingLeft;
extern std::pair<int, int> segmSelected, segmOnScreen[];

