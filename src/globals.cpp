#include "globals.hpp"
#include "helpers.hpp"
#include "string.hpp"
#include "button.hpp"
#include "menu.hpp"
#include "config.hpp"

sf::Font globalFont, textFont;
sf::RenderWindow window;
sf::RectangleShape topSeparator, bottomSeparator, lineNumbersBackground, toolBarBackground, statusBarBackground, cursorBox, cursorLineHighlight, box;
sf::RenderTexture aboveCurrentLineText, belowCurrentLineText, lineNumbersText;
sf::Sprite aboveCurrentLineSprite, belowCurrentLineSprite, lineNumbersSprite;

ThemeColors currentThemeColors = themeColorsMapping.at(theme);

bool fileSaved = 1;

int windowWidth = 800, windowHeight = 600;

bool showLineNumbers = true;
Theme theme = Theme::LIGHT;

int lineNumbersMaxDigits = 3;
int fontSize = initialFontSize;
int zoomLevel = 100;
float lineHeight = Helpers::getLineHeight();
float marginLeft, paddingLeft;
std::pair<int, int> segmSelected, segmOnScreen[maxRows];
std::vector<std::string> renderLines(maxRows);
int sizeRLines = 0;

std::string path = "";

String::Treap *S = new String::Treap(cursorChar, 1);

TextBox *lineColumnTextBox, *zoomLevelTextBox, *selectedCharacterCountTextBox, *lineCountTextBox, *fileNameTextBox;
Button *zoomOutButton, *zoomInButton;
Menu **menus;
