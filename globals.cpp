#include "globals.hpp"

sf::Font font;
sf::RenderWindow window;

const ThemeColors themeColors[] =
{
    {
        sf::Color::White, 
        sf::Color::Black, 
        sf::Color::Black, 
        sf::Color(0, 0, 0, 128),
        sf::Color(200, 200, 200), 
        sf::Color(150, 150, 150), 
        sf::Color(220, 220, 220), 
        { sf::Color(200, 200, 255, 128), sf::Color(200, 200, 255, 128) }
    },
    {
        sf::Color(32, 32, 32), 
        sf::Color::White, 
        sf::Color::White, 
        sf::Color(255, 255, 255, 128), 
        sf::Color(80, 80, 80), 
        sf::Color(60, 60, 60), 
        sf::Color(50, 50, 50), 
        { sf::Color(200, 200, 255, 128), sf::Color(200, 200, 255, 128) }
    }
};

ThemeColors currentThemeColors = themeColors[lightTheme];

int windowWidth = 1000;
int windowHeight = 1000;

bool showLineNumbers = true;
bool lightTheme = true;
