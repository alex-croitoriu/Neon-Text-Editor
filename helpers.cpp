#include "helpers.hpp"

// TODO: make strings global so no need for prop drilling
void Helpers::switchTheme(sf::Text &t1, sf::Text &t2, sf::Text &t3)
{
    lightTheme = !lightTheme;

    currentThemeColors = themeColors[lightTheme];

    t1.setFillColor(currentThemeColors.text);
    t2.setFillColor(currentThemeColors.text);
    t3.setFillColor(currentThemeColors.text);

    zoomInButton->updateThemeColors();
    zoomOutButton->updateThemeColors();

    for (int i = 0; i < 3; i++)
    {
        menus[i]->getToggleButton()->updateThemeColors();
        for (int j = 0; j < menus[i]->getButtonCount(); j++)
            menus[i]->getButtons()[j]->updateThemeColors();
    }
}