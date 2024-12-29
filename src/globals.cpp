#include "globals.hpp"
#include "button.hpp"
#include "menu.hpp"
#include "helpers.hpp"
#include "config.hpp"
#include "string.hpp"

sf::Font font;
sf::RenderWindow window;
sf::RectangleShape topSeparator, bottomSeparator, lineNumbersBackground, toolBarBackground, statusBarBackground, cursorBox, cursorLineHighlight, box;

ThemeColors currentThemeColors = themeColorsMapping.at(theme);

int windowWidth = 800, windowHeight = 600;

bool showLineNumbers = true;
Theme theme = Theme::LIGHT;

int fontSize = initialFontSize;
int zoomLevel = 100;
float lineHeight = Helpers::getLineHeight();
bool wordWrap = 0;
float marginLeft, paddingLeft;
std::pair<int, int> segmSelected, segmOnScreen[maxRows];

String::Treap *S = new String::Treap(cursorChar, 1);

TextBox *lineColumnTextBox, *zoomLevelTextBox, *selectedCharacterCountTextBox, *lineCountTextBox;
Button *zoomOutButton, *zoomInButton;
Menu **menus;
