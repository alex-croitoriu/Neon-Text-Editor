#include "globals.hpp"

sf::Font font;
sf::RenderWindow window;

const ThemeColors themeColors[] =
{
    {
        sf::Color(0, 0, 0, 30), 
        sf::Color::White, 
        sf::Color::White, 
        sf::Color(255, 255, 255, 128),
        sf::Color(255, 255, 255, 30), 
        sf::Color(80, 80, 80), 
        sf::Color(0, 0, 0, 255), 
        sf::Color(0, 0, 0, 50),
        { sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 0) }
    },
        {
        sf::Color::White, 
        sf::Color::Black, 
        sf::Color::Black, 
        sf::Color(0, 0, 0, 128),
        sf::Color(0, 0, 0, 30),
        sf::Color(200, 200, 200),
        sf::Color(255, 255, 255, 255), 
        sf::Color(0, 0, 0, 30), 
        { sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 0) }
    }
};

ThemeColors currentThemeColors = themeColors[lightTheme];

int windowWidth = 1000;
int windowHeight = 1000;

bool showLineNumbers = true;
bool lightTheme = true;

Button *zoomOutButton, *zoomInButton;

Menu **menus;
