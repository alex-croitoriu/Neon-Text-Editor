#include "globals.hpp"
#include "config.hpp"

sf::Font font;
sf::RenderWindow window;

ThemeColors currentThemeColors = themeColors[lightTheme];

int windowWidth = 1000;
int windowHeight = 1000;

bool showLineNumbers = true;
bool lightTheme = true;

Button *zoomOutButton, *zoomInButton;

Menu **menus;
