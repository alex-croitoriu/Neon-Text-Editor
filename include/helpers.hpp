#pragma once

#include <SFML/Graphics.hpp>

#include "globals.hpp"

namespace Helpers 
{
    float getLineHeight(int fnt = fontSize);
    void centerContentInsideContainer(sf::RectangleShape &container, sf::Text &content, bool vertical = true, bool horizontal = true, int paddingTop = 0, int paddingLeft = 0);
    // TODO: make strings global so no need for prop drilling
    void changeTheme(Theme theme, sf::Text &t1, sf::Text &t2);
    bool isAnyButtonPressed();
    std::string getTime(const std::string &format);
    std::vector<sf::Vector2f> getToolBarPositions();
    void updateToolBarPositions();
    void updateToolBarInfo();
    std::vector<sf::Vector2f> getStatusBarPositions();
    void updateStatusBarPositions();
    void updateStatusBarInfo();
    std::string getFileName();
}
