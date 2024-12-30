#pragma once

#include <SFML/Graphics.hpp>

#include "globals.hpp"

namespace Helpers 
{
    float getLineHeight(int fnt = fontSize);
    void centerContentInsideContainer(sf::RectangleShape &container, sf::Text &content, bool vertical = true, bool horizontal = true, int paddingTop = 0, int paddingLeft = 0);
    // TODO: make strings global so no need for prop drilling
    void changeTheme(sf::Text &t1, sf::Text &t2);
    bool isAnyButtonPressed();
    std::string getTime(std::string format);
    std::vector<sf::Vector2f> getToolBarPositions();
    std::vector<sf::Vector2f> getStatusBarPositions();
    void updateStatusBarInfo();
    void updateStatusBarPositions();
}
