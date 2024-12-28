#include "helpers.hpp"
#include "config.hpp"

// TODO: make strings global so no need for prop drilling
void Helpers::switchTheme(sf::Text &t1, sf::Text &t2, sf::Text &t3)
{
    lightTheme = !lightTheme;
    currentThemeColors = themeColors[lightTheme];

    // update text fields
    t1.setFillColor(currentThemeColors.text);
    t2.setFillColor(currentThemeColors.text);
    t3.setFillColor(currentThemeColors.text);

    // update zoom buttons
    zoomInButton->updateThemeColors();
    zoomOutButton->updateThemeColors();
 
    // update menu buttons (including toggle buttons)
    for (int i = 0; i < 3; i++)
    {
        menus[i]->getToggleButton()->updateThemeColors();
        for (int j = 0; j < menus[i]->getButtonCount(); j++)
            menus[i]->getButtons()[j]->updateThemeColors();
    }
}

bool Helpers::isAnyButtonPressed()
{
    // check if zoom buttons are pressed
    if (zoomOutButton->isHovering() || zoomInButton->isHovering())
        return true;

    // check if any menu button (including toggle buttons) is pressed
    for (int i = 0; i < 3; i++)
    {
        if (menus[i]->getToggleButton()->isHovering())
            return true;

        if (menus[i]->getIsOpen())
        {
            Button **menuButtons = menus[i]->getButtons();
            for (int j = 0; j < menus[i]->getButtonCount(); j++)
                if (menuButtons[j]->isHovering())
                    return true;
        }
    }

    return false;
}
