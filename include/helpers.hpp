#include <SFML/Graphics.hpp>

#include "globals.hpp"

namespace Helpers 
{
    float computedLineHeight(int fnt = fontSize);
    // TODO: make strings global so no need for prop drilling
    void switchTheme(sf::Text &t1, sf::Text &t2, sf::Text &t3);
    bool isAnyButtonPressed();
    std::string getTime(std::string format);
}
