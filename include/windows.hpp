#pragma once

#include <string>

#include "inputBox.hpp"
#include "button.hpp"
#include "checkbox.hpp"

namespace Windows
{
    std::string saveAS();
    std::string open();
    int saveModal();
}

namespace goToLineWindow
{
    extern sf::RenderWindow window;
    extern sf::Text text;
    extern InputBox *inputBox;
    extern Button *cancelButton, *goToLineButton;

    void initialize();
    void draw();
    void open();
    void close();
    void handleEvent(const sf::Event &event);
}

namespace findWindow
{
    extern sf::RenderWindow window;
    extern sf::Text text, matchCaseText, wholeWordText, matchCountText;
    extern InputBox *inputBox;
    extern Button *cancelButton, *findButton, *nextButton, *prevButton;
    extern CheckBox *matchCaseCheckBox, *wholeWordCheckBox;

    void initialize();
    void draw();
    void open();
    void close();
    void handleEvent(const sf::Event &event);
}

namespace replaceWindow
{
    extern sf::RenderWindow window;
    extern sf::Text text1, text2, matchCaseText, wholeWordText, matchCountText;
    extern InputBox *findInputBox, *replaceInputBox;
    extern Button *cancelButton, *findButton, *nextButton, *prevButton, *replaceButton, *replaceAllButton;
    extern CheckBox *matchCaseCheckBox, *wholeWordCheckBox;

    void initialize();
    void draw();
    void open();
    void close();
    void handleEvent(const sf::Event &event);
}

namespace errorWindow
{
    void open(const std::string &message);
}