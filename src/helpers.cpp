#include "helpers.hpp"
#include "config.hpp"
#include "string.hpp"
#include "windows.hpp"

float Helpers::getLineHeight(int fnt)
{
    return fnt * 1.5;
}

void Helpers::centerContentInsideContainer(sf::RectangleShape &container, sf::Text &content, bool centerX, bool centerY, int paddingTop, int paddingRight, int paddingBottom, int paddingLeft)
{
    if (centerX && !centerY)
    {
        content.setOrigin(int(content.getGlobalBounds().getSize().x / 2.f + content.getLocalBounds().getPosition().x), 0);
        content.setPosition(int(container.getPosition().x + container.getSize().x / 2.f), int(container.getPosition().y + paddingTop));
    }
    else if (!centerX && centerY)
    {
        content.setOrigin(0, int(content.getGlobalBounds().getSize().y / 2.f + content.getLocalBounds().getPosition().y));
        if (paddingLeft && !paddingRight)
            content.setPosition(int(container.getGlobalBounds().left + paddingLeft), int(container.getPosition().y + container.getSize().y / 2.f));
        else if (!paddingLeft && paddingRight)
            content.setPosition(int(container.getGlobalBounds().left + container.getGlobalBounds().getSize().x - content.getGlobalBounds().getSize().x - paddingRight), int(container.getPosition().y + container.getSize().y / 2.f));
    }
    else if (centerX && centerY)
    {
        content.setOrigin(int(content.getGlobalBounds().getSize().x / 2.f + content.getLocalBounds().getPosition().x), int(content.getGlobalBounds().getSize().y / 2.f + content.getLocalBounds().getPosition().y));
        content.setPosition(int(container.getPosition().x + container.getSize().x / 2.f), int(container.getPosition().y + container.getSize().y / 2.f));
    }
    else if (!centerX && !centerY)
    {
        content.setOrigin(0, 0);
        if (paddingLeft && !paddingRight)
            content.setPosition(int(container.getPosition().x + paddingLeft), int(container.getPosition().y + paddingTop));
        else if (!paddingLeft && paddingRight)
            content.setPosition(int(container.getGlobalBounds().left + container.getGlobalBounds().getSize().x - content.getGlobalBounds().getSize().x - paddingRight), int(container.getPosition().y + paddingTop));
    }
}

void Helpers::changeTheme(Theme _theme, sf::Text &t1, sf::Text &t2)
{
    theme = _theme; 
    currentThemeColors = themeColorsMapping.at(theme);

    t1.setFillColor(currentThemeColors.text);
    t2.setFillColor(currentThemeColors.text);

    zoomInButton->updateThemeColors();
    zoomOutButton->updateThemeColors();

    zoomInButton ->setOutline(theme != Theme::DARK && theme != Theme::NEON_DARK && theme != Theme::SOLARIZED_DARK && theme != Theme::MIDNIGHT && theme != Theme::OBSIDIAN);
    zoomOutButton->setOutline(theme != Theme::DARK && theme != Theme::NEON_DARK && theme != Theme::SOLARIZED_DARK && theme != Theme::MIDNIGHT && theme != Theme::OBSIDIAN);
 
    for (int i = 0; i < 5; i++)
    {
        menus[i]->getToggleButton()->updateThemeColors();
        for (int j = 0; j < menus[i]->getButtonCount(); j++)
            menus[i]->getButtons()[j]->updateThemeColors();
    }

    fileNameTextBox->updateThemeColors();

    lineCountTextBox->updateThemeColors();
    lineColumnTextBox->updateThemeColors();
    selectedCharacterCountTextBox->updateThemeColors();
    zoomLevelTextBox->updateThemeColors();

    lineNumbersBackground.setFillColor(currentThemeColors.lineNumbersBackground);
    toolBarBackground.setFillColor(currentThemeColors.bar);
    statusBarBackground.setFillColor(currentThemeColors.bar);

    topSeparator.setFillColor(currentThemeColors.separator);
    bottomSeparator.setFillColor(currentThemeColors.separator);

    cursorLineHighlight.setFillColor(currentThemeColors.cursorLineHighlight);

    goToLineWindow::cancelButton->updateThemeColors();
    goToLineWindow::goToLineButton->updateThemeColors();
    goToLineWindow::inputBox->updateThemeColors();
    goToLineWindow::text.setFillColor(currentThemeColors.text);

    findWindow::cancelButton->updateThemeColors();
    findWindow::findButton->updateThemeColors();
    findWindow::nextButton->updateThemeColors();
    findWindow::prevButton->updateThemeColors();
    findWindow::inputBox->updateThemeColors();
    findWindow::matchCaseCheckBox->updateThemeColors();
    findWindow::wholeWordCheckBox->updateThemeColors();

    findWindow::text.setFillColor(currentThemeColors.text);
    findWindow::matchCaseText.setFillColor(currentThemeColors.text);
    findWindow::wholeWordText.setFillColor(currentThemeColors.text);
    findWindow::matchCountText.setFillColor(currentThemeColors.text);

    replaceWindow::findButton->updateThemeColors();
    replaceWindow::replaceButton->updateThemeColors();
    replaceWindow::nextButton->updateThemeColors();
    replaceWindow::prevButton->updateThemeColors();
    replaceWindow::replaceAllButton->updateThemeColors();

    replaceWindow::cancelButton->updateThemeColors();

    replaceWindow::findInputBox->updateThemeColors();
    replaceWindow::replaceInputBox->updateThemeColors();

    replaceWindow::matchCaseCheckBox->updateThemeColors();
    replaceWindow::wholeWordCheckBox->updateThemeColors();

    replaceWindow::text1.setFillColor(currentThemeColors.text);
    replaceWindow::text2.setFillColor(currentThemeColors.text);

    replaceWindow::matchCaseText.setFillColor(currentThemeColors.text);
    replaceWindow::wholeWordText.setFillColor(currentThemeColors.text);
    replaceWindow::matchCountText.setFillColor(currentThemeColors.text);
}

void Helpers::changeFont(const std::string& font)
{
    textFont.loadFromFile("assets/fonts/" + font + ".ttf ");
}

bool Helpers::isAnyButtonPressed()
{
    if (zoomOutButton->isHovering() || zoomInButton->isHovering())
        return true;

    for (int i = 0; i < 5; i++)
    {
        if (i <= 2 && menus[i]->getToggleButton()->isHovering())
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

std::string Helpers::getTime(const std::string &format)
{
    time_t timestamp = time(NULL);
    struct tm datetime = *localtime(&timestamp);

    char data[100];
    int len = strftime(data, sizeof(data), format.c_str(), &datetime);

    std::string currTime(data, len);
    return currTime;
}

std::vector<sf::Vector2f> Helpers::getToolBarPositions()
{
    ButtonProperties properties = buttonSizeMapping.at(ButtonSize::MEDIUM);
    return 
    {
        sf::Vector2f(0, properties.size.y),                          // file menu
        sf::Vector2f(properties.size.x, properties.size.y),          // edit menu
        sf::Vector2f(2 * properties.size.x, properties.size.y),      // options menu
        sf::Vector2f(windowWidth - fileNameTextBox->getSize().x, 0)  // file name text box
    };
}

void Helpers::updateToolBarPositions()
{
    std::vector<sf::Vector2f> toolBarPositions = getToolBarPositions();
    fileNameTextBox->setPosition(toolBarPositions[3]);
}

void Helpers::updateToolBarInfo()
{
    fileNameTextBox->setContent((fileSaved ? "" : "*") + getFileName());
}

std::vector<sf::Vector2f> Helpers::getStatusBarPositions()
{
    int buttonWidth = buttonSizeMapping.at(ButtonSize::SMALL).size.x;
    int y = windowHeight - marginBottom;
    return 
    {
        sf::Vector2f(0, y),                                                                                       // line count text box
        sf::Vector2f(int(lineCountTextBox->getSize().x - 1), y),                                                  // line column text box
        sf::Vector2f(int(lineCountTextBox->getSize().x + lineColumnTextBox->getSize().x - 2), y),                 // selected character count text box
        sf::Vector2f(int(std::max(0.0f, windowWidth - 2 * buttonWidth - zoomLevelTextBox->getSize().x + 2)), y),  // zoom out button
        sf::Vector2f(int(std::max(0.0f, windowWidth - buttonWidth - zoomLevelTextBox->getSize().x + 1)), y),      // zoom level text box
        sf::Vector2f(int(std::max(0, windowWidth - buttonWidth)), y)                                              // zoom in button
    };
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

void Helpers::updateStatusBarInfo()
{
    int cursorPosition = String::findCursorPosition(S);
    int cursorLine = String::findNumberOfEndlines(1, cursorPosition, S) + 1;

    int currentLine = String::findNumberOfEndlines(1, cursorPosition, S) + 1;
    int currentColumn = String::findCursorPosition(S) - String::findKthLine(cursorLine , S);
    int selectedCharacterCount = segmSelected.second - segmSelected.first + 1 - String::findNumberOfEndlines(segmSelected.first, segmSelected.second, S);
    int lineCount = String::findNumberOfEndlines(1, String::len(S), S) + 1;

    lineCountTextBox->setContent(std::to_string(lineCount) + (lineCount == 1 ? " line" : " lines"));
    lineColumnTextBox->setContent("Ln " + std::to_string(currentLine) + ", Col " + std::to_string(currentColumn));
    selectedCharacterCountTextBox->setContent(std::to_string(selectedCharacterCount) + " selected");
    zoomLevelTextBox->setContent(std::to_string(zoomLevel) + "%");
}

std::string Helpers::getFileName()
{
    if (path.size() == 0)
        return "New file";

    size_t pos = path.find_last_of("/\\");
    if (pos != std::string::npos)
        return path.substr(pos + 1);

    return path;
}

void Helpers::updateFindMatchCount()
{
    findWindow::matchCountText.setString((positions.size() ? (std::to_string(currentAppearance + 1) + " of ") : "") + std::to_string(positions.size()) + (positions.size() == 1 ? " match" : " matches"));
}

void Helpers::updateReplaceMatchCount()
{
    replaceWindow::matchCountText.setString((positions.size() ? (std::to_string(currentAppearance + 1) + " of ") : "") + std::to_string(positions.size()) + (positions.size() == 1 ? " match" : " matches"));
}

void Helpers::resetFindMatchCount()
{
    findWindow::matchCountText.setString("");
}
void Helpers::resetReplaceMatchCount()
{
    replaceWindow::matchCountText.setString("");
}
