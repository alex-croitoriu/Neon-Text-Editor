#include "globals.hpp"
#include "helpers.hpp"
#include "string.hpp"
#include "button.hpp"
#include "config.hpp"
#include "menu.hpp"

sf::Font globalFont, textFont, checkmarkFont, lineNumbersTextFont;
sf::RenderWindow window;
sf::RectangleShape topSeparator, bottomSeparator, lineNumbersBackground, toolBarBackground, statusBarBackground, cursorBox, cursorLineHighlight, box;
sf::RenderTexture aboveCurrentLineText, belowCurrentLineText, lineNumbersText;
sf::Sprite aboveCurrentLineSprite, belowCurrentLineSprite, lineNumbersSprite;
sf::Image icon;

ThemeColors currentThemeColors = themeColorsMapping.at(theme);

bool fileSaved = 1;
int fontIndex = 0;

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
std::string findKeyword = "", replaceKeyword = "";

int goToLineNumber = -1;
int currentAppearance = 0;

std::vector<int> positions;

String::Treap *S = new String::Treap(cursorChar, 1);

TextBox *lineColumnTextBox, *zoomLevelTextBox, *selectedCharacterCountTextBox, *lineCountTextBox, *fileNameTextBox;
Button *zoomOutButton, *zoomInButton;
Menu **menus;
