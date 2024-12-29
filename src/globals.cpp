#include "globals.hpp"
#include "button.hpp"
#include "menu.hpp"
#include "helpers.hpp"
#include "config.hpp"
#include "string.hpp"

sf::Font font;
sf::RenderWindow window;
sf::RectangleShape topSeparator, bottomSeparator, lineNumbersBackground, toolBarBackground, statusBarBackground, cursorBox, cursorLineHighlight, box;
sf::RenderTexture text1, text2, text3;
sf::Sprite img1, img2, img3;

ThemeColors currentThemeColors = themeColorsMapping.at(theme);

int windowWidth = 800, windowHeight = 600;

bool showLineNumbers = true;
Theme theme = Theme::LIGHT;

int lineNumbersMaxDigits = 3;
int fontSize = initialFontSize;
int zoomLevel = 100;
float lineHeight = Helpers::getLineHeight();
bool wordWrap = 0;
float marginLeft, paddingLeft;
std::pair<int, int> segmSelected, segmOnScreen[maxRows];
std::vector<std::string> renderLines(maxRows);

int sizeRLines = 0;

String::Treap *S = new String::Treap(cursorChar, 1);

TextBox *lineColumnTextBox, *zoomLevelTextBox, *selectedCharacterCountTextBox, *lineCountTextBox;
Button *zoomOutButton, *zoomInButton;
Menu **menus;
