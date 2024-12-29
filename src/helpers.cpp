#include <iostream>

#include "helpers.hpp"
#include "config.hpp"
#include "string.hpp"

float Helpers::getLineHeight(int fnt)
{
    return fnt * 1.5;
}

void Helpers::centerContentInsideContainer(sf::RectangleShape &container, sf::Text &content, bool vertical, bool horizontal, int paddingTop, int paddingLeft)
{
    if (!horizontal && vertical)
    {
        content.setOrigin(0, int(content.getGlobalBounds().getSize().y / 2.f + content.getLocalBounds().getPosition().y));
        content.setPosition(int(container.getGlobalBounds().left + paddingLeft), int(container.getPosition().y + container.getSize().y / 2.f));
    }
    else if (!vertical && horizontal)
    {
        content.setOrigin(int(content.getGlobalBounds().getSize().x / 2.f + content.getLocalBounds().getPosition().x), 0);
        content.setPosition(int(container.getPosition().x + container.getSize().x / 2.f), int(container.getPosition().y + paddingTop));
    }
    else if (horizontal && vertical)
    {
        content.setOrigin(int(content.getGlobalBounds().getSize().x / 2.f + content.getLocalBounds().getPosition().x), int(content.getGlobalBounds().getSize().y / 2.f + content.getLocalBounds().getPosition().y));
        content.setPosition(int(container.getPosition().x + container.getSize().x / 2.f), int(container.getPosition().y + container.getSize().y / 2.f));
    }
}

// TODO: make strings global so no need for prop drilling
void Helpers::changeTheme(sf::Text &t1, sf::Text &t2, sf::Text &t3)
{
    if (theme == Theme::LIGHT)
        theme = Theme::DARK;
    else
        theme = Theme::LIGHT;
    currentThemeColors = themeColorsMapping.at(theme);

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

    lineCountTextBox->updateThemeColors();
    lineColumnTextBox->updateThemeColors();
    selectedCharacterCountTextBox->updateThemeColors();
    zoomLevelTextBox->updateThemeColors();

    lineNumbersBackground.setFillColor(currentThemeColors.lineNumbersBackground);
    statusBarBackground.setFillColor(currentThemeColors.background);

    topSeparator.setFillColor(currentThemeColors.separator);
    bottomSeparator.setFillColor(currentThemeColors.separator);
}

bool Helpers::isAnyButtonPressed()
{
    if (zoomOutButton->isHovering() || zoomInButton->isHovering())
        return true;

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

std::string Helpers::getTime(std::string format)
{
    time_t timestamp = time(NULL);
    struct tm datetime = *localtime(&timestamp);

    char data[100];
    int len = strftime(data, sizeof(data), format.c_str(), &datetime);

    if (len == 0)
    {
        std::cerr << "Error: invalid format or buffer size too small\n";
        return "";
    }

    std::string currTime(data, len);
    return currTime;
}

std::vector<sf::Vector2f> Helpers::getToolBarPositions()
{
    ButtonProperties properties = buttonSizeMapping.at(ButtonSize::MEDIUM);
    return 
    {
        // first 3 positions represent the top left corner of the menus themselves, not the top left corner of the toggle menu button
        sf::Vector2f(0, properties.size.y),
        sf::Vector2f(properties.size.x, properties.size.y),
        sf::Vector2f(2 * properties.size.x, properties.size.y),
    };
}

std::vector<sf::Vector2f> Helpers::getStatusBarPositions()
{
    ButtonProperties buttonProperties = buttonSizeMapping.at(ButtonSize::SMALL);
    return 
    {
        sf::Vector2f(0, windowHeight - marginBottom),
        sf::Vector2f(lineCountTextBox->getSize().x - 1, windowHeight - marginBottom),
        sf::Vector2f(lineCountTextBox->getSize().x + lineColumnTextBox->getSize().x - 2, windowHeight - marginBottom),
        sf::Vector2f(std::max(0.0f, windowWidth - 2 * buttonProperties.size.x - zoomLevelTextBox->getSize().x + 2), windowHeight - marginBottom),
        sf::Vector2f(std::max(0.0f, windowWidth - buttonProperties.size.x - zoomLevelTextBox->getSize().x + 1), windowHeight - marginBottom),
        sf::Vector2f(std::max(0.0f, windowWidth - buttonProperties.size.x), windowHeight - marginBottom)
    };
}

void Helpers::updateStatusBarInfo()
{
    int posCursor = String::findCursorPosition(S);
    int cursorLine = String::findNumberOfEndlines(1, posCursor, S) + 1;

    int currentLine = String::findNumberOfEndlines(1, posCursor, S) + 1;
    int currentCol = String::findCursorPosition(S) - String::findKthLine(cursorLine , S);
    int selectedCharacterCount = segmSelected.second - segmSelected.first + 1 - String::findNumberOfEndlines(segmSelected.first, segmSelected.second, S);
    int lineCount = String::findNumberOfEndlines(1, String::len(S), S) + 1;

    lineCountTextBox->setContent(std::to_string(lineCount) + (lineCount == 1 ? " line" : " lines"));
    lineColumnTextBox->setContent("Ln " + std::to_string(currentLine) + ", Col " + std::to_string(currentCol));
    selectedCharacterCountTextBox->setContent(std::to_string(selectedCharacterCount) + " selected");
    zoomLevelTextBox->setContent(std::to_string(zoomLevel) + "%");
}

void Helpers::updateStatusBarPositions()
{
    std::vector<sf::Vector2f> statusBarPositions = getStatusBarPositions();

    lineCountTextBox->setPosition(statusBarPositions[0]);
    lineColumnTextBox->setPosition(statusBarPositions[1]);
    selectedCharacterCountTextBox->setPosition(statusBarPositions[2]);
    zoomOutButton->setPosition(statusBarPositions[3]);
    zoomLevelTextBox->setPosition(statusBarPositions[4]);
    zoomInButton->setPosition(statusBarPositions[5]);
}
