#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <windows.h>
#include <commdlg.h>
#include <filesystem>

#include "windows.hpp"
#include "globals.hpp"
#include "inputBox.hpp"
#include "string.hpp"

std::string Windows::saveAsWindow()
{
    std::filesystem::path originalDir = std::filesystem::current_path();

    OPENFILENAMEA ofn;
    char szFile[260];
    char szFileTitle[260];

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile) / sizeof(szFile[0]);
    ofn.lpstrFileTitle = szFileTitle;
    ofn.lpstrFileTitle[0] = '\0';
    ofn.nMaxFileTitle = sizeof(szFileTitle) / sizeof(szFileTitle[0]);
    ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

    if (GetOpenFileNameA(&ofn) == TRUE)
    {
        std::cout << "Selected file: " << ofn.lpstrFile << std::endl;
        std::filesystem::current_path(originalDir);
        return ofn.lpstrFile;
    }
    else
    {
        std::cout << "Open file dialog canceled or failed." << std::endl;
        std::filesystem::current_path(originalDir);
        return "";
    }
}

std::string Windows::openFileWindow()
{
    std::filesystem::path originalDir = std::filesystem::current_path();

    OPENFILENAMEA ofn;
    char szFile[260];
    char szFileTitle[260];

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFileTitle = szFileTitle;
    ofn.lpstrFileTitle[0] = '\0';
    ofn.nMaxFileTitle = sizeof(szFileTitle);
    ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


    if (GetOpenFileNameA(&ofn) == TRUE)
    {
        std::cout << "Selected file: " << ofn.lpstrFile << std::endl;
        std::filesystem::current_path(originalDir);
        return ofn.lpstrFile;
    }
    else
    {
        std::cout << "Open file dialog canceled or failed." << std::endl;
        std::filesystem::current_path(originalDir);
        return "";
    }
}

int Windows::saveWindow()
{
    sf::Event event;
    sf::Text text("Do you want to save changes?", globalFont, 14);

    sf::RenderWindow window(sf::VideoMode(328, 88), "Save changes", sf::Style::Titlebar);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Button *yesButton = new Button("Yes", sf::Vector2f(40, 44), true);
    Button *noButton = new Button("No", sf::Vector2f(126, 44), true);
    Button *cancelButton = new Button("Cancel", sf::Vector2f(212, 44), true);

    text.setFillColor(currentThemeColors.text);
    text.setPosition(67, 14);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return IDCANCEL;
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == 36)
            {
                window.close();
                return IDCANCEL;
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.key.code == 0)
            {
                if (yesButton->isHovering(window))
                {
                    window.close();
                    return IDYES;
                }
                else if (noButton->isHovering(window))
                {
                    window.close();
                    return IDNO;
                }
                else if (cancelButton->isHovering(window))
                {
                    window.close();
                    return IDCANCEL;
                }
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                yesButton->setHoverState(yesButton->isHovering(window));
                noButton->setHoverState(noButton->isHovering(window));
                cancelButton->setHoverState(cancelButton->isHovering(window));
            }
        }

        window.clear(currentThemeColors.background);
        window.draw(text);
        yesButton->draw(window);
        noButton->draw(window);
        cancelButton->draw(window);
        window.display();
    }

    return IDCANCEL;
}

void Windows::errorWindow(const std::string &message)
{
    sf::Event event;
    sf::Text text;

    text.setFont(globalFont);
    text.setFillColor(currentThemeColors.text);
    text.setString(message);
    text.setCharacterSize(14);
    text.setPosition(40, 14);

    sf::Vector2f size = text.getGlobalBounds().getSize();

    sf::RenderWindow window(sf::VideoMode(size.x + 80, size.y + 44), "Error", sf::Style::Titlebar);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    while (window.isOpen())
    {
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
                if (event.key.code == 36)
                    window.close();

        window.clear(currentThemeColors.background);
        window.draw(text);
        window.display();
    }
}

sf::RenderWindow goToLineWindow::window;
sf::Text goToLineWindow::text("Line number", globalFont, 12);
InputBox *goToLineWindow::inputBox;
Button *goToLineWindow::cancelButton, *goToLineWindow::goToLineButton;

void goToLineWindow::initialize()
{
    goToLineWindow::text.setFillColor(currentThemeColors.text);
    goToLineWindow::text.setPosition(40, 14);

    goToLineWindow::inputBox = new InputBox("", sf::Vector2f(40, 34), sf::Vector2f(162, 24));
    goToLineWindow::goToLineButton = new Button("Go to line", sf::Vector2f(40, 68), true);
    goToLineWindow::cancelButton = new Button("Cancel", sf::Vector2f(126, 68), true);
}

void goToLineWindow::open()
{
    goToLineWindow::window.create(sf::VideoMode(242, 112), "Go to line", sf::Style::Titlebar);
    goToLineWindow::window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    goToLineWindow::inputBox->setContent("");
    goToLineWindow::inputBox->setIsActive(true);
}

void goToLineWindow::close()
{
    goToLineWindow::window.close();
    goToLineWindow::inputBox->setContent("");
    goToLineWindow::inputBox->setIsActive(false);
}

void goToLineWindow::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::Closed)
        goToLineWindow::close();
    
    else if (event.type == sf::Event::MouseMoved)
    {
        goToLineWindow::cancelButton->setHoverState(goToLineWindow::cancelButton->isHovering(goToLineWindow::window));
        goToLineWindow::goToLineButton->setHoverState(goToLineWindow::goToLineButton->isHovering(goToLineWindow::window));
        goToLineWindow::inputBox->setHoverState(goToLineWindow::inputBox->isHovering(goToLineWindow::window));
    }
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.key.code == 0)
        {
            goToLineWindow::inputBox->setIsActive(goToLineWindow::inputBox->isHovering(goToLineWindow::window));

            if (goToLineWindow::cancelButton->isHovering(goToLineWindow::window))
                goToLineWindow::close();
            else if (goToLineWindow::goToLineButton->isHovering(goToLineWindow::window))
                try
                {
                    int lineNumber = stoi(goToLineWindow::inputBox->getContent());
                    if (!lineNumber || lineNumber > String::findNumberOfEndlines(1, String::len(S), S) + 1)
                        throw std::invalid_argument("Invalid number!");
                    goToLineWindow::close();
                    goToLineNumber = lineNumber;
                }
                catch(std::exception &err)
                {
                    Windows::errorWindow("Invalid number!");
                }
        }
    }
    else if (event.type == sf::Event::KeyPressed)
    {
        int key = event.key.code;

        if (key == 36)
            goToLineWindow::close();
        else if (key == 58)
        {
            try
            {
                int lineNumber = stoi(goToLineWindow::inputBox->getContent());
                if (!lineNumber || lineNumber > String::findNumberOfEndlines(1, String::len(S), S) + 1)
                    throw std::invalid_argument("Invalid number!");
                goToLineWindow::close();
                goToLineNumber = lineNumber;
            }
            catch(std::exception &err)
            {
                Windows::errorWindow("Invalid number!");
            }
        }
    }
    if (goToLineWindow::inputBox->getIsActive())
        goToLineWindow::inputBox->handleInput(goToLineWindow::window, event, true);
}

void goToLineWindow::draw()
{
    goToLineWindow::window.clear(currentThemeColors.background);
    goToLineWindow::window.draw(goToLineWindow::text);
    goToLineWindow::inputBox->draw(goToLineWindow::window);
    goToLineWindow::cancelButton->draw(goToLineWindow::window);
    goToLineWindow::goToLineButton->draw(goToLineWindow::window);

    goToLineWindow::window.display();
}


sf::RenderWindow findWindow::window;
sf::Text findWindow::text("Find keyword", globalFont, 12), findWindow::matchCaseText("Match case", globalFont, 12), findWindow::wholeWordText("Whole word", globalFont, 12), findWindow::matchCountText("", globalFont, 12);
InputBox *findWindow::inputBox;
Button *findWindow::cancelButton, *findWindow::findButton, *findWindow::nextButton, *findWindow::prevButton;
CheckBox *findWindow::matchCaseCheckBox, *findWindow::wholeWordCheckBox;

void findWindow::initialize()
{
    findWindow::text.setFillColor(currentThemeColors.text);
    findWindow::matchCaseText.setFillColor(currentThemeColors.text);
    findWindow::wholeWordText.setFillColor(currentThemeColors.text);
    findWindow::matchCountText.setFillColor(currentThemeColors.text);

    findWindow::text.setPosition(40, 14);
    findWindow::inputBox = new InputBox("", sf::Vector2f(40, 34), sf::Vector2f(334, 24));
    findWindow::findButton = new Button("Find", sf::Vector2f(40, 112), true);
    findWindow::nextButton = new Button("Next", sf::Vector2f(126, 112), true);
    findWindow::prevButton = new Button("Previous", sf::Vector2f(212, 112), true);
    findWindow::cancelButton = new Button("Cancel", sf::Vector2f(298, 112), true);

    findWindow::matchCaseCheckBox = new CheckBox(sf::Vector2f(40, 68));
    findWindow::wholeWordCheckBox = new CheckBox(sf::Vector2f(40, 88));
    findWindow::matchCaseText.setPosition(60, 67);
    findWindow::wholeWordText.setPosition(60, 87);

    findWindow::matchCountText.setPosition(40, 146);
}

void findWindow::open()
{
    findWindow::window.create(sf::VideoMode(414, 176), "Find", sf::Style::Titlebar);
    findWindow::window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    findWindow::inputBox->setContent("");
    findWindow::inputBox->setIsActive(true);
    findWindow::matchCountText.setString("");
}

void findWindow::close()
{
    findWindow::window.close();
    findWindow::inputBox->setContent("");
    findWindow::inputBox->setIsActive(false);
}

void findWindow::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::Closed)
        findWindow::close();
    else if (event.type == sf::Event::MouseMoved)
    {
        findWindow::cancelButton->setHoverState(findWindow::cancelButton->isHovering(findWindow::window));
        findWindow::findButton->setHoverState(findWindow::findButton->isHovering(findWindow::window));
        findWindow::nextButton->setHoverState(findWindow::nextButton->isHovering(findWindow::window));
        findWindow::prevButton->setHoverState(findWindow::prevButton->isHovering(findWindow::window));
        findWindow::matchCaseCheckBox->setHoverState(findWindow::matchCaseCheckBox->isHovering(findWindow::window) || findWindow::matchCaseCheckBox->getIsChecked());
        findWindow::wholeWordCheckBox->setHoverState(findWindow::wholeWordCheckBox->isHovering(findWindow::window) || findWindow::wholeWordCheckBox->getIsChecked());
        findWindow::inputBox->setHoverState(findWindow::inputBox->isHovering(findWindow::window));
    }
    else if (event.type == sf::Event::KeyPressed)
    {
        int key = event.key.code;

        if (key == 36)
            findWindow::close();
    }
    if (findWindow::inputBox->getIsActive())
        findWindow::inputBox->handleInput(findWindow::window, event);
}

void findWindow::draw()
{
    findWindow::window.clear(currentThemeColors.background);
    findWindow::window.draw(findWindow::text);
    findWindow::window.draw(findWindow::matchCaseText);
    findWindow::window.draw(findWindow::wholeWordText);
    findWindow::window.draw(findWindow::matchCountText);

    findWindow::inputBox->draw(findWindow::window);
    findWindow::cancelButton->draw(findWindow::window);
    findWindow::findButton->draw(findWindow::window);
    findWindow::nextButton->draw(findWindow::window);
    findWindow::prevButton->draw(findWindow::window);
    findWindow::matchCaseCheckBox->draw(findWindow::window);
    findWindow::wholeWordCheckBox->draw(findWindow::window);

    findWindow::window.display();
}



sf::RenderWindow replaceWindow::window;
sf::Text replaceWindow::text1("Find keyword", globalFont, 12), replaceWindow::text2("Replace keyword", globalFont, 12), replaceWindow::matchCaseText("Match case", globalFont, 12), replaceWindow::wholeWordText("Whole word", globalFont, 12), replaceWindow::matchCountText("", globalFont, 12);
InputBox *replaceWindow::findInputBox, *replaceWindow::replaceInputBox;
Button *replaceWindow::cancelButton, *replaceWindow::findButton, *replaceWindow::nextButton, *replaceWindow::prevButton, *replaceWindow::replaceButton, *replaceWindow::replaceAllButton;
CheckBox *replaceWindow::matchCaseCheckBox, *replaceWindow::wholeWordCheckBox;

void replaceWindow::initialize()
{
    replaceWindow::text1.setFillColor(currentThemeColors.text);
    replaceWindow::text2.setFillColor(currentThemeColors.text);
    replaceWindow::matchCaseText.setFillColor(currentThemeColors.text);
    replaceWindow::wholeWordText.setFillColor(currentThemeColors.text);
    replaceWindow::matchCountText.setFillColor(currentThemeColors.text);

    replaceWindow::text1.setPosition(40, 14);
    replaceWindow::text2.setPosition(40, 68);
    replaceWindow::findInputBox = new InputBox("", sf::Vector2f(40, 34), sf::Vector2f(334, 24));
    replaceWindow::replaceInputBox = new InputBox("", sf::Vector2f(40, 88), sf::Vector2f(334, 24));

    replaceWindow::findButton = new Button("Find", sf::Vector2f(40, 166), true);
    replaceWindow::replaceButton = new Button("Replace", sf::Vector2f(126, 166), true);
    replaceWindow::nextButton = new Button("Next", sf::Vector2f(212, 166), true);
    replaceWindow::prevButton = new Button("Previous", sf::Vector2f(298, 166), true);
    replaceWindow::replaceAllButton = new Button("Replace all", sf::Vector2f(40, 200), true);
    replaceWindow::cancelButton = new Button("Cancel", sf::Vector2f(126, 200), true);

    replaceWindow::matchCaseCheckBox = new CheckBox(sf::Vector2f(40, 122));
    replaceWindow::wholeWordCheckBox = new CheckBox(sf::Vector2f(40, 142));
    replaceWindow::matchCaseText.setPosition(60, 121);
    replaceWindow::wholeWordText.setPosition(60, 141);

    replaceWindow::matchCountText.setPosition(40, 236);
}

void replaceWindow::open()
{
    replaceWindow::window.create(sf::VideoMode(414, 266), "Replace", sf::Style::Titlebar);
    replaceWindow::window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    replaceWindow::findInputBox->setContent("");
    replaceWindow::findInputBox->setIsActive(true);
    replaceWindow::replaceInputBox->setContent("");
    replaceWindow::replaceInputBox->setIsActive(false);
    replaceWindow::matchCountText.setString("");
}

void replaceWindow::close()
{
    replaceWindow::window.close();
    replaceWindow::findInputBox->setContent("");
    replaceWindow::findInputBox->setIsActive(false);
    replaceWindow::replaceInputBox->setContent("");
    replaceWindow::replaceInputBox->setIsActive(false);
}

void replaceWindow::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::Closed)
        replaceWindow::close();
    else if (event.type == sf::Event::MouseMoved)
    {
        replaceWindow::findButton->setHoverState(replaceWindow::findButton->isHovering(replaceWindow::window));
        replaceWindow::replaceButton->setHoverState(replaceWindow::replaceButton->isHovering(replaceWindow::window));
        replaceWindow::nextButton->setHoverState(replaceWindow::nextButton->isHovering(replaceWindow::window));
        replaceWindow::prevButton->setHoverState(replaceWindow::prevButton->isHovering(replaceWindow::window));
        replaceWindow::replaceAllButton->setHoverState(replaceWindow::replaceAllButton->isHovering(replaceWindow::window));
        replaceWindow::cancelButton->setHoverState(replaceWindow::cancelButton->isHovering(replaceWindow::window));
        replaceWindow::matchCaseCheckBox->setHoverState(replaceWindow::matchCaseCheckBox->isHovering(replaceWindow::window) || replaceWindow::matchCaseCheckBox->getIsChecked());
        replaceWindow::wholeWordCheckBox->setHoverState(replaceWindow::wholeWordCheckBox->isHovering(replaceWindow::window) || replaceWindow::wholeWordCheckBox->getIsChecked());
        replaceWindow::findInputBox->setHoverState(replaceWindow::findInputBox->isHovering(replaceWindow::window));
        replaceWindow::replaceInputBox->setHoverState(replaceWindow::replaceInputBox->isHovering(replaceWindow::window));
    }
    else if (event.type == sf::Event::KeyPressed)
    {
        int key = event.key.code;

        if (key == 36)
            replaceWindow::close();
    }
    if (replaceWindow::findInputBox->getIsActive())
        replaceWindow::findInputBox->handleInput(replaceWindow::window, event);
    if (replaceWindow::replaceInputBox->getIsActive())
        replaceWindow::replaceInputBox->handleInput(replaceWindow::window, event);
}

void replaceWindow::draw()
{
    replaceWindow::window.clear(currentThemeColors.background);
    replaceWindow::window.draw(replaceWindow::text1);
    replaceWindow::window.draw(replaceWindow::text2);
    replaceWindow::window.draw(replaceWindow::matchCaseText);
    replaceWindow::window.draw(replaceWindow::wholeWordText);
    replaceWindow::window.draw(replaceWindow::matchCountText);

    replaceWindow::findInputBox->draw(replaceWindow::window);
    replaceWindow::replaceInputBox->draw(replaceWindow::window);
    replaceWindow::findButton->draw(replaceWindow::window);
    replaceWindow::replaceButton->draw(replaceWindow::window);
    replaceWindow::nextButton->draw(replaceWindow::window);
    replaceWindow::prevButton->draw(replaceWindow::window);
    replaceWindow::replaceAllButton->draw(replaceWindow::window);
    replaceWindow::cancelButton->draw(replaceWindow::window);

    replaceWindow::matchCaseCheckBox->draw(replaceWindow::window);
    replaceWindow::wholeWordCheckBox->draw(replaceWindow::window);

    replaceWindow::window.display();
}
