#include "helpers.hpp"
#include "render.hpp"

std::string txt;

bool Render::updateViewX(String::Treap *&S, int &Xoffset, int scrollUnitX)
{
    int currLineWidth = String::findCurrentWidth(String::findCursorPosition(S), S);
    bool modif = 0;

    while (currLineWidth <= Xoffset)
        Xoffset -= scrollUnitX, modif = 1;

    if (modif)
        Xoffset -= scrollUnitX;
    Xoffset = std::max(0, Xoffset);

    while (currLineWidth >= Xoffset + windowWidth - marginLeft - scrollUnitX)
        Xoffset += scrollUnitX, modif = 1;

    return modif;
}

bool Render::updateViewY(String::Treap *&S, int &Yoffset, int scrollUnitY)
{
    int globalHeight = String::findCurrentHeight(S);
    int height = Helpers::getLineHeight();
    bool modif = 0;

    while (globalHeight - height < Yoffset)
        Yoffset -= scrollUnitY, modif = 1;

    Yoffset = std::max(0, Yoffset);

    while (globalHeight > Yoffset + windowHeight - marginBottom - marginTop)
        Yoffset += scrollUnitY, modif = 1;

    return modif;
}

void Render::updateTextLine(int line, std::vector<std::string> &renderLines, std::string L)
{
    if (line == sizeRLines)
        renderLines[sizeRLines++] = L;
    else
        renderLines[line] = L;
}

int Render::findLineOnScreen(float y)
{
    return (int)((y - marginTop) / lineHeight) + 1;
}

int Render::moveCursorToClick(sf::Vector2i localPosition, String::Treap *&S, int scrollUnitY, int l1, int l2, int Xoffset)
{
    int l = findLineOnScreen(localPosition.y);
    float w = localPosition.x - marginLeft - paddingLeft;

    if (l + l1 - 1 > l2)
        return String::len(S) + 1;
    int p1 = String::findKthLine(l + l1 - 1, S);
    if (w <= 0)
        return p1;

    if (String::len(S) + 1 == p1)
        return String::len(S) + 1;
    if (String::get(p1, S) == 10)
        return p1;

    int p2 = String::findNextEndline(p1, S) - 1;
    int p = String::getFirstSeen(p1, p2, w + Xoffset, S);

    if (p == -1)
        p = p2;
    return p + 1;
}

void Render::centerText(sf::Text &text, std::string s, float startY, float startX)
{
    bool empty = 0;
    s += "|";
    text.setString(s);
    int centerConst = ((float)lineHeight - text.getGlobalBounds().height) / 2;
    s.pop_back();
    text.setString(s);
    text.setPosition(startX, (int)startY + centerConst);
}

void Render::updateSmartRender(sf::Text &text, int l1, int l2, int cursorLine, int scrollUnitY)
{
    txt.clear();
    int h1 = 0;
    int L = std::min(l2 - l1 + 1, cursorLine - l1);

    text.setCharacterSize(fontSize);
    text.setLetterSpacing(0.8);
    text.setFillColor(currentThemeColors.lineNumbersText);
    text.setFont(lineNumbersTextFont);

    aboveCurrentLineText.clear(sf::Color(0, 0, 0, 0));
    belowCurrentLineText.clear(sf::Color(0, 0, 0, 0));
    lineNumbersText.clear(sf::Color(0, 0, 0, 0));

    int lastHeight = -lineHeight;

    for (int i = l1; i <= l2; i++)
    {
        std::string line = "";
        std::string number = std::to_string(i);
        if (number.length() > lineNumbersMaxDigits)
            lineNumbersMaxDigits = number.length();
        for (int j = 0; j < lineNumbersMaxDigits - number.length(); j++)
            line += " ";
        line += number;
        centerText(text, line, marginTop + lastHeight + lineHeight, 5);
        lineNumbersText.draw(text);
        lastHeight += lineHeight;
    }

    marginLeft = showLineNumbers * (lineNumbersMaxDigits + 1) * charWidth[0][fontSize]['9'];
    paddingLeft = 0.5 * charWidth[0][fontSize]['a'];

    lineNumbersBackground.setSize(sf::Vector2f(marginLeft, windowHeight));
    statusBarBackground.setSize(sf::Vector2f(windowWidth, marginBottom));
    toolBarBackground.setSize(sf::Vector2f(windowWidth, marginTop));

    text.setLetterSpacing(1);
    text.setFillColor(currentThemeColors.text);
    text.setFont(textFont);

    lastHeight = -lineHeight;

    for (int i = 0; i < L; i++)
    {
        centerText(text, renderLines[i], marginTop + lastHeight + lineHeight);
        aboveCurrentLineText.draw(text);
        lastHeight += lineHeight;
    }

    int textHeight = lastHeight;

    if (l1 <= cursorLine && cursorLine <= l2)
        txt = renderLines[cursorLine - l1];
    else
        txt = "";

    if (txt.size())
        lastHeight += lineHeight;

    for (int i = std::max(0, cursorLine - l1 + 1); i < sizeRLines; i++)
    {
        centerText(text, renderLines[i], marginTop + lastHeight + lineHeight);
        belowCurrentLineText.draw(text);
        lastHeight += lineHeight;
    }

    aboveCurrentLineSprite.setTexture(aboveCurrentLineText.getTexture());
    belowCurrentLineSprite.setTexture(belowCurrentLineText.getTexture());
    lineNumbersSprite.setTexture(lineNumbersText.getTexture());

    centerText(text, txt, marginTop + textHeight + lineHeight);

    aboveCurrentLineText.display();
    belowCurrentLineText.display();
    lineNumbersText.display();
}

float Render::splitCursorLine(sf::Text &text, sf::Text &h1, std::string &txt, int posCursorOnScreen, int fp)
{
    if (txt.size() == 0)
    {
        h1.setString("");
        return 0;
    }

    if (fp == -1)
    {
        h1 = text;
        return 0;
    }

    h1.setCharacterSize(fontSize);

    std::string s1, s2;

    for (int i = 0; i < posCursorOnScreen - 1; i++)
        s1 += txt[i];

    h1.setString(s1);
    float w = h1.getGlobalBounds().width;
    char ch;

    if (posCursorOnScreen < txt.size() && txt[posCursorOnScreen] != 13)
        ch = txt[posCursorOnScreen];
    else
        ch = '|';

    s1 += ch;
    h1.setString(s1);
    float W = h1.getGlobalBounds().width;
    s1.pop_back();

    s2 += ch;

    h1.setString(s2);
    float cW = h1.getGlobalBounds().width;

    for (int i = posCursorOnScreen; i < txt.size(); i++)
        s1 += txt[i];

    h1.setString(s1);
    h1.setPosition(marginLeft + paddingLeft, text.getPosition().y);

    return w + (W - w - cW) / 2;
}

void Render::render(int &l1, int &l2, String::Treap *&S, int Yoffset, int Xoffset, int cursorLine, sf::Text &text, int scrollUnitY)
{
    int numberOfLines = String::findNumberOfEndlines(1, String::len(S), S) + 1;

    l1 = std::max(1, (Yoffset) / scrollUnitY + 1);
    l2 = std::min(numberOfLines, std::max(1, (Yoffset + windowHeight - marginBottom - marginTop) / scrollUnitY));

    sizeRLines = 0;

    for (int i = l1; l1 > 0 && l2 > 0 && l1 <= l2 && i <= l2 + (l2 < numberOfLines); i++)
        updateTextLine(sizeRLines, renderLines, String::constructRenderedLine(i, S, Xoffset, i - l1));

    updateSmartRender(text, l1, l2 + (l2 < numberOfLines), cursorLine, scrollUnitY);
}
