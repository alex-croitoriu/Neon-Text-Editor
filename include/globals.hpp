#pragma once

#include <SFML/Graphics.hpp>

#include "textBox.hpp"
#include "button.hpp"
#include "menu.hpp"
#include "config.hpp"

extern sf::Font font;
extern sf::RenderWindow window;
extern sf::RectangleShape topSeparator, bottomSeparator, lineNumbersBackground, toolBarBackground, statusBarBackground, cursorBox, cursorLineHighlight, box;
extern sf::RenderTexture text1, text2, text3;
extern sf::Sprite img1, img2, img3;

extern bool fileSaved;

extern int windowWidth, windowHeight;

extern bool showLineNumbers;
extern Theme theme;
extern ThemeColors currentThemeColors;

extern int lineNumbersMaxDigits;
extern int fontSize;
extern int zoomLevel;
extern float lineHeight;
extern float marginLeft, paddingLeft;
extern std::pair<int, int> segmSelected, segmOnScreen[];
extern std::vector<std::string> renderLines;
extern int sizeRLines;

extern std::string path;
