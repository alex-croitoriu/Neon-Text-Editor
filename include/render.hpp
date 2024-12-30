#pragma once

#include <vector>

#include "string.hpp"

namespace Render
{
    bool updateViewX(String::Treap *&S, int &Xoffset, int scrollUnitX);
    bool updateViewY(String::Treap *&S, int &Yoffset, int scrollUnitY);
    void updateTextLine(int line, std::vector<std::string> &renderLines, std::string L);
    int findLineOnScreen(float y);
    int moveCursorToClick(sf::Vector2i localPosition, String::Treap *&S, int scrollUnitY, int l1, int l2, int Xoffset);
    void centerText(sf::Text &text, std::string s, float startY, float startX = marginLeft + paddingLeft);
    void render(int &l1, int &l2, String::Treap *&S, int Yoffset, int Xoffset, int cursorLine, sf::Text &text, int scrollUnitY);
    void updateSmartRender(sf::Text &text, int l1, int l2, int cursorLine, int scrollUnitY);
    float splitCursorLine(sf::Text &text, sf::Text &h1, std::string &txt, int posCursorOnScreen, int fp);
}
