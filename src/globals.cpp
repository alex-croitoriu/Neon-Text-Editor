#include "globals.hpp"
#include "button.hpp"
#include "menu.hpp"
#include "config.hpp"
#include "helpers.hpp"

sf::Font font;
sf::RenderWindow window;

ThemeColors currentThemeColors = themeColorsMapping.at(theme);

int windowWidth = 1000, windowHeight = 1000;

bool showLineNumbers = true;
Theme theme = Theme::LIGHT;

int fontSize = initialFontSize;
int zoomLevel = 100;
float lineHeight = Helpers::getLineHeight();
bool wordWrap = 0;
float marginLeft, paddingLeft;
std::pair<int, int> segmOnScreen[maxRows];

TextBox *lineColumnTextBox, *zoomLevelTextBox, *fontSizeTextBox, *selectedCharactersTextBox, *lineCountTextBox;
Button *zoomOutButton, *zoomInButton;
Menu **menus;
