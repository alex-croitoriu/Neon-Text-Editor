#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <random>
#include <windows.h>
#include <commdlg.h>
#include <ctime>
#include <cassert>
#include <set>
#include <bitset>

#include "helpers.hpp"
#include "globals.hpp"
#include "config.hpp"
#include "button.hpp"
#include "menu.hpp"
#include "string.hpp"

using namespace std;

sf::RenderTexture text1, text2, text3;
sf::Sprite img1, img2, img3;

vector<sf::RectangleShape> selectedBoxes;

sf::Event event;
sf::Text text, ptext1, ptext2;

int cursorHeight = 0, cursorWidth = 0;
int lineNumbersMaxDigits = 3;

vector<string> renderLines(maxRows);

namespace Windows
{
    string getPathFromUser(string name) /// ia path-ul introdus de catre utilizator pentru a salva fisierul
    {
        const int DIM = 200;
        sf::RenderWindow window(sf::VideoMode(DIM * 4, DIM / 4 - 10), name);
        sf::Image mainIcon;
        mainIcon.loadFromFile("assets/images/main_icon.png");
        window.setIcon(mainIcon.getSize().x, mainIcon.getSize().y, mainIcon.getPixelsPtr());

        sf::Event event;
        sf::Text text, pth;

        text.setFont(font);
        text.setFillColor(sf::Color::Black);
        text.setString("Enter path: ");

        pth.setFont(font);
        pth.setFillColor(sf::Color::Green);
        pth.setPosition(200, 0);

        string path;

        while (window.isOpen())
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    int key = event.key.code;

                    if (key == 58 || key == 36)
                        window.close();

                    break;
                }
                if (event.type == sf::Event::TextEntered)
                {
                    int ch = event.text.unicode;

                    if (ch == 8)
                    {
                        if (path.size())
                            path.pop_back();
                    }
                    else
                        path += ch;

                    break;
                }
            }

            pth.setString(path);
            window.clear(sf::Color::White);
            window.draw(text);
            window.draw(pth);
            window.display();
        }

        return path;
    }

    string getStringFromUser(string name) /// citeste cuvantul pe care vrea user-ul sa-l caute
    {
        const int DIM = 200;
        sf::RenderWindow window(sf::VideoMode(DIM * 4, DIM / 4 - 10), name);
        sf::Image mainIcon;
        mainIcon.loadFromFile("assets/images/main_icon.png");
        window.setIcon(mainIcon.getSize().x, mainIcon.getSize().y, mainIcon.getPixelsPtr());

        sf::Event event;
        sf::Text text, pth;

        text.setFont(font);
        text.setFillColor(sf::Color::Black);
        text.setString("Enter keyword: ");

        pth.setFont(font);
        pth.setFillColor(sf::Color::Green);
        pth.setString("");
        pth.setPosition(250, 0);

        string path;

        while (window.isOpen())
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    int key = event.key.code;

                    if (key == 58 || key == 36)
                    {
                        window.close();
                    }

                    break;
                }
                if (event.type == sf::Event::TextEntered)
                {
                    int ch = event.text.unicode;

                    if (ch == 8)
                    {
                        if (path.size())
                            path.pop_back();
                    }
                    else
                        path += ch;

                    break;
                }
            }

            pth.setString(path);
            window.clear(sf::Color::White);
            window.draw(text);
            window.draw(pth);
            window.display();
        }

        return path;
    }

    void throwMessage(string message)
    {
        const int DIM = 200;
        sf::RenderWindow window(sf::VideoMode(DIM * 4, DIM / 4 - 10), "");

        sf::Event event;
        sf::Text text;

        text.setFont(font);
        text.setFillColor(sf::Color::Black);
        text.setString(message);

        while (window.isOpen())
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    int key = event.key.code;

                    if (key == 58 || key == 36)
                    {
                        window.close();
                    }

                    break;
                }
            }

            window.clear(sf::Color::White);
            window.draw(text);
            window.display();
        }
    }

    string saveAS()
    {
        OPENFILENAMEA ofn;
        char szFile[260];      // Buffer for full file path
        char szFileTitle[260]; // Buffer for file title (file name only)

        // Initialize the OPENFILENAME structure
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL; // Handle to the owner window
        ofn.lpstrFile = szFile;
        ofn.lpstrFile[0] = '\0';                           // Initialize the file buffer with an empty string
        ofn.nMaxFile = sizeof(szFile) / sizeof(szFile[0]); // Wide chars
        ofn.lpstrFileTitle = szFileTitle;
        ofn.lpstrFileTitle[0] = '\0';                                     // Initialize file title buffer
        ofn.nMaxFileTitle = sizeof(szFileTitle) / sizeof(szFileTitle[0]); // Wide chars
        ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.TXT\0";          // Wide character filter
        ofn.nFilterIndex = 1;                                             // Default filter index
        ofn.lpstrInitialDir = NULL;                                       // Initial directory
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;              // Overwrite prompt for save dialog

        if (GetOpenFileNameA(&ofn) == TRUE)
        {
            // File selected and dialog confirmed
            std::cout << "Selected file: " << ofn.lpstrFile << std::endl;
            return ofn.lpstrFile;
        }
        else
        {
            // Dialog was canceled or an error occurred
            std::cout << "Open file dialog canceled or failed." << std::endl;
            return "";
        }
    }

    string open()
    {
        OPENFILENAMEA ofn;
        char szFile[260];      // Buffer for full file path
        char szFileTitle[260]; // Buffer for file title (file name only)

        // Initialize the OPENFILENAME structure
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL; // Handle to the owner window
        ofn.lpstrFile = szFile;
        ofn.lpstrFile[0] = '\0'; // Initialize the file buffer with an empty string
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFileTitle = szFileTitle;
        ofn.lpstrFileTitle[0] = '\0'; // Initialize file title buffer
        ofn.nMaxFileTitle = sizeof(szFileTitle);
        ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.TXT\0"; // ANSI character filter
        ofn.nFilterIndex = 1;                                    // Default filter index
        ofn.lpstrInitialDir = NULL;                              // Initial directory
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        // Display the Open dialog box
        if (GetOpenFileNameA(&ofn) == TRUE)
        {
            // File selected and dialog confirmed
            std::cout << "Selected file: " << ofn.lpstrFile << std::endl;
            return ofn.lpstrFile;
        }
        else
        {
            // Dialog was canceled or an error occurred
            std::cout << "Open file dialog canceled or failed." << std::endl;
            return "";
        }
    }
    
    int saveModal() 
    { ///am invatat de la cei mai buni
        int result = MessageBox(
            NULL,                            
            "Do you want to save changes?",  
            "Save Changes",                  
            MB_YESNOCANCEL | MB_ICONQUESTION 
        );

        return result;
    }
}

int sizeRLines = 0;
string txt1, txt2, txt, all;

namespace Render
{
    bool updateViewX(String::Treap *&S, int &Xoffset, int scrollUnitX)
    {
        int currLineWidth = String::findCurrentWidth(String::findCursorPosition(S), S);
        bool modif = 0;

        while (currLineWidth <= Xoffset)
            Xoffset -= scrollUnitX, modif = 1;

        if (modif)
            Xoffset -= scrollUnitX;
        Xoffset = max(0, Xoffset);

        while (currLineWidth >= Xoffset + windowWidth - marginLeft - scrollUnitX)
            Xoffset += scrollUnitX, modif = 1;

        return modif;
    }

    bool updateViewY(String::Treap *&S, int &Yoffset, int scrollUnitY)
    {
        int globalHeight = String::findCurrentHeight(S);
        int height = Helpers::getLineHeight();
        bool modif = 0;

        while (globalHeight - height < Yoffset)
            Yoffset -= scrollUnitY, modif = 1;

        Yoffset = max(0, Yoffset);

        while (globalHeight > Yoffset + windowHeight - marginBottom - marginTop)
            Yoffset += scrollUnitY, modif = 1;

        return modif;
    }

    void updateTextLine(int line, vector<string> &renderLines, string L)
    {
        if (line == sizeRLines)
            renderLines[sizeRLines++] = L;
        else
            renderLines[line] = L;
    }

    int findLineOnScreen(float y)
    {
        return (int)((y - marginTop) / lineHeight) + 1;
    }

    int moveCursorToClick(sf::Vector2i localPosition, String::Treap *&S, int scrollUnitY, int l1, int l2, int Xoffset)
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

    void centerText(sf::Text &text, string s, float startY, float startX = marginLeft + paddingLeft)
    {
        bool empty = 0;
        s += "|";
        text.setString(s);
        int centerConst = ((float)lineHeight - text.getGlobalBounds().height) / 2;
        s.pop_back();
        text.setString(s);
        text.setPosition(startX, (int)startY + centerConst);
    }

    void updateSmartRender(sf::Text &text, int l1, int l2, int cursorLine, int scrollUnitY)
    {
        txt1.clear(), txt2.clear(), txt.clear();
        int h1 = 0;
        int L = min(l2 - l1 + 1, cursorLine - l1);

        text.setCharacterSize(fontSize);
        text.setLetterSpacing(0.7);
        text.setFillColor(currentThemeColors.lineNumbersText);

        text1.clear(sf::Color(0, 0, 0, 0));
        text2.clear(sf::Color(0, 0, 0, 0));
        text3.clear(sf::Color(0, 0, 0, 0));

        int lastHeight = -lineHeight;

        for (int i = l1; i <= l2; i++)
        {
            string line = "";
            string number = to_string(i);
            if (number.length() > lineNumbersMaxDigits)
                lineNumbersMaxDigits = number.length();
            for (int j = 0; j < lineNumbersMaxDigits - number.length(); j++)
                line += " ";
            line += number;
            centerText(text, line, marginTop + lastHeight + lineHeight, 5);
            text3.draw(text);
            lastHeight += lineHeight;
        }

        marginLeft = showLineNumbers * (lineNumbersMaxDigits + 1) * charWidth[fontSize]['9'];
        paddingLeft = 0.5 * charWidth[fontSize]['a'];

        lineNumbersBackground.setSize(sf::Vector2f(marginLeft, windowHeight));
        statusBarBackground.setSize(sf::Vector2f(windowWidth, marginBottom));
        toolBarBackground.setSize(sf::Vector2f(windowWidth, marginTop));

        text.setLetterSpacing(1);
        text.setFillColor(currentThemeColors.text);

        lastHeight = -lineHeight;

        for (int i = 0; i < L; i++)
        {
            centerText(text, renderLines[i], marginTop + lastHeight + lineHeight);
            text1.draw(text);
            lastHeight += lineHeight;
        }

        int textHeight = lastHeight;

        if (l1 <= cursorLine && cursorLine <= l2)
            txt = renderLines[cursorLine - l1];
        else
            txt = "";

        if (txt.size())
            lastHeight += lineHeight;

        for (int i = max(0, cursorLine - l1 + 1); i < sizeRLines; i++)
        {
            centerText(text, renderLines[i], marginTop + lastHeight + lineHeight);
            text2.draw(text);
            lastHeight += lineHeight;
        }

        img1.setTexture(text1.getTexture());
        img2.setTexture(text2.getTexture());
        img3.setTexture(text3.getTexture());

        centerText(text, txt, marginTop + textHeight + lineHeight);

        text1.display();
        text2.display();
        text3.display();
    }

    float splitCursorLine(sf::Text &text, sf::Text &h1, sf::Text &h2, string &txt, int posCursorOnScreen, int fp)
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

        string s1, s2;

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

    void render(int &l1, int &l2, String::Treap *&S, int Yoffset, int Xoffset, int cursorLine, sf::Text &text, int scrollUnitY)
    {
        int numberOfLines = String::findNumberOfEndlines(1, String::len(S), S) + 1;

        l1 = max(1, (Yoffset) / scrollUnitY + 1);
        l2 = min(numberOfLines, max(1, (Yoffset + windowHeight - marginBottom - marginTop) / scrollUnitY));

        sizeRLines = 0;

        for (int i = l1; l1 > 0 && l2 > 0 && l1 <= l2 && i <= l2 + (l2 < numberOfLines); i++)
        {
            updateTextLine(sizeRLines, renderLines, String::constructRenderedLine(i, S, Xoffset, i - l1));
            // cerr << renderLines[sizeRLines - 1] << ' ' << '\n';
        }
        updateSmartRender(text, l1, l2 + (l2 < numberOfLines), cursorLine, scrollUnitY);
    }
}

namespace ReplaceFind
{
    void KMP(string &s, string &word, vector<int> &positions, bool &wholeWord)
    {
        vector<int> PI(word.size());
        vector<int> pi(s.size());
        positions.clear();

        PI[0] = 0;

        for (int i = 1; i < word.size(); i++)
        {
            int t = PI[i - 1];

            while (t && word[i] != word[t])
                t = PI[t - 1];

            t += word[i] == word[t];
            PI[i] = t;
        }

        for (int i = 0; i < s.size(); i++)
        {
            int t = (i == 0 ? 0 : pi[i - 1]);

            while (t && (t == word.size() || s[i] != word[t]))
                t = PI[t - 1];

            t += word[t] == s[i];
            pi[i] = t;

            if (t == word.size())
            {
                if (wholeWord == 0 || ((i - word.size() + 1 == 0 || s[i - word.size()] == ' ' || s[i - word.size()] == '\n') && (i == s.size() - 1 || s[i + 1] == ' ' || s[i + 1] == '\n')))
                    positions.push_back(i - word.size() + 1 + 1);
            }
        }

        // cerr << "positions are: "; for (auto i : positions) cerr << i << ' ';
        // cerr << '\n';
    }

    bool isApOnScreen(int ap, int sz)
    {
        for (int i = 0; i < sizeRLines; i++)
        {
            int l = segmOnScreen[i].first;
            int r = segmOnScreen[i].second;

            if (l == -1)
                continue;

            cerr << "Line: " << i + 1 << ": " << l << ' ' << r << '\n';

            if (l <= ap && ap <= r && ap + sz - 1 <= r)
                return 1;
        }

        cerr << '\n';
        return 0;
    }

    bool isValid(char ch)
    {
        return ch != 10 && ch != ' ';
    }

    namespace BIT
    {
        void reset(vector<int> &bit)
        {
            for (int i = 0; i < bit.size(); i++)
                bit[i] = 0;
        }

        void upd(int p, int v, vector<int> &bit)
        {
            if (p == 0)
                bit[p] += v;

            for (; p && p < bit.size(); p += p & -p)
                bit[p] += v;
        }

        int get(int p, vector<int> &bit)
        {
            int ans = bit[0];

            for (; p; p -= p & -p)
                ans += bit[p];

            return ans;
        }
    }

    void delAp(int idx, vector<int> &prv, vector<int> &nxt, vector<int> &bit, vector<int> &gone, set<int> &notRemoved, int vl = 1)
    {
        BIT::upd(idx, vl, bit);

        gone[idx] = 1;
        notRemoved.erase(idx);

        int P = prv[idx];
        int N = nxt[idx];

        if (P != -1)
            nxt[P] = N;
        if (N != -1)
            prv[N] = P;

        // prv[idx] = nxt[idx] = -1;
    }

    int findLastReplace(int idx, vector<int> &bit)
    {
        int l = 0, r = idx - 1, ans = -1, mid = 0;
        int value = BIT::get(idx, bit);

        if (value == 0)
            return -1;

        while (l <= r)
        {
            mid = (l + r) / 2;

            if (BIT::get(mid, bit) >= value)
                ans = mid, r = mid - 1;
            else
                l = mid + 1;
        }

        return ans;
    }

    int findNextReplace(int idx, vector<int> &bit)
    {
        int l = idx + 1, r = bit.size() - 1, mid = 0, ans = -1;
        int value = BIT::get(idx, bit) + 1;

        while (l <= r)
        {
            mid = (l + r) / 2;

            if (BIT::get(mid, bit) >= value)
                ans = mid, r = mid - 1;
            else
                l = mid + 1;
        }

        return ans;
    }

    bool canReplace(int idx, vector<int> &bit, vector<int> &positions, vector<int> &gone, string &rword, string &word)
    {
        if (gone[idx])
            return 0;

        int p1 = findLastReplace(idx, bit);
        //   cerr << "              working\n" << '\n';
        int p2 = findNextReplace(idx, bit);
        //  cerr << idx << ' ' << p1 << ' ' << p2 << '\n';

        if (p1 != -1)
        {
            if (positions[p1] + (int)word.size() - 1 >= positions[idx])
                return 0;
        }

        if (p2 != -1)
        {
            if (positions[idx] + (int)word.size() - 1 >= positions[p2])
                return 0;
        }

        return 1;
    }

    int findNextValidAppearance(int idx, vector<int> &bit, vector<int> &positions, vector<int> &gone, string &rword, string &word, vector<int> &prv, vector<int> &nxt, set<int> &notRemoved)
    {
        int x = nxt[idx];

        while (x != -1 && canReplace(x, bit, positions, gone, rword, word) == 0)
        {
            int y = nxt[x];
            delAp(x, prv, nxt, bit, gone, notRemoved, 0);
            x = y;
        }

        return x;
    }

    int findPrevValidAppearance(int idx, vector<int> &bit, vector<int> &positions, vector<int> &gone, string &rword, string &word, vector<int> &prv, vector<int> &nxt, set<int> &notRemoved)
    {
        int x = prv[idx];

        while (x != -1 && canReplace(x, bit, positions, gone, rword, word) == 0)
        {
            int y = prv[x];
            delAp(x, prv, nxt, bit, gone, notRemoved, 0);
            x = y;
        }

        return x;
    }

    int findRealPosition(int idx, vector<int> &positions, vector<int> &bit, string &word, string &rword)
    {
        int sub = BIT::get(idx, bit);
        return positions[idx] - sub * word.size() + sub * rword.size();
    }

    int traceFirstApToRender(int idx, vector<int> &positions, vector<int> &bit, set<int> &notRemoved, string &word, string &rword)
    {
        int l = 0, r = positions.size() - 1, mid = 0, ans = -1;

        while (l <= r)
        {
            mid = (l + r) / 2;

            auto it = notRemoved.upper_bound(mid);

            if (it == notRemoved.begin())
                l = mid + 1;
            else
            {
                --it;
                if (findRealPosition(*it, positions, bit, word, rword) >= idx)
                    ans = mid, r = mid - 1;
                else
                    l = mid + 1;
            }
        }

        return ans;
    }
}

int main()
{
    window.create(sf::VideoMode(windowWidth, windowHeight), "Text Editor");
    sf::View view;
    sf::Image mainIcon;

    mainIcon.loadFromFile("assets/images/main_icon.png");
    window.setIcon(mainIcon.getSize().x, mainIcon.getSize().y, mainIcon.getPixelsPtr());

    font.loadFromFile("assets/fonts/cour.ttf");

    lineHeight = Helpers::getLineHeight();

    text.setFont(font);
    text.setFillColor(currentThemeColors.text);
    text.setCharacterSize(fontSize);
    text.setStyle(sf::Text::Regular);

    ptext1.setFont(font);
    ptext1.setFillColor(currentThemeColors.text);
    ptext1.setCharacterSize(fontSize);
    ptext1.setStyle(sf::Text::Regular);

    ptext2.setFont(font);
    ptext2.setFillColor(currentThemeColors.text);
    ptext2.setCharacterSize(fontSize);
    ptext2.setStyle(sf::Text::Regular);

    vector<sf::Vector2f> toolBarPositions = Helpers::getToolBarPositions(), statusBarPositions = Helpers::getStatusBarPositions();

    menus = new Menu *[3];
    for (int i = 0; i < 3; i++)
        menus[i] = new Menu(menuLabels[i], menuButtonLabels[i], toolBarPositions[i]);

    Menu *fileMenu = menus[0], *editMenu = menus[1], *optionsMenu = menus[2];
    Button **fileMenuButtons = fileMenu->getButtons(), **editMenuButtons = editMenu->getButtons(), **optionsMenuButtons = optionsMenu->getButtons();

    lineCountTextBox = new TextBox("", statusBarPositions[0]);
    lineColumnTextBox = new TextBox("", statusBarPositions[1]);
    selectedCharacterCountTextBox = new TextBox("", statusBarPositions[2]);
    zoomOutButton = new Button(zoomButtonLabels[0], statusBarPositions[3], ButtonSize::SMALL);
    zoomLevelTextBox = new TextBox("", statusBarPositions[4]);
    zoomInButton = new Button(zoomButtonLabels[1], statusBarPositions[5], ButtonSize::SMALL);

    cursorLineHighlight.setFillColor(currentThemeColors.cursorLineHighlight);

    topSeparator.setPosition(0, marginTop);
    topSeparator.setSize(sf::Vector2f(windowWidth, 1));
    topSeparator.setFillColor(currentThemeColors.separator);

    bottomSeparator.setPosition(0, windowHeight - marginBottom);
    bottomSeparator.setSize(sf::Vector2f(windowWidth, 1));
    bottomSeparator.setFillColor(currentThemeColors.separator);

    lineNumbersBackground.setPosition(0, marginTop);
    lineNumbersBackground.setSize(sf::Vector2f(marginLeft, windowHeight));
    lineNumbersBackground.setFillColor(currentThemeColors.lineNumbersBackground);

    toolBarBackground.setPosition(0, 0);
    toolBarBackground.setSize(sf::Vector2f(windowWidth, marginTop));
    toolBarBackground.setFillColor(currentThemeColors.bar);
    
    statusBarBackground.setPosition(0, windowHeight - marginBottom);
    statusBarBackground.setSize(sf::Vector2f(windowWidth, marginBottom));
    statusBarBackground.setFillColor(currentThemeColors.bar);



    int Yoffset = 0, Xoffset = 0;
    int scrollUnitX = charWidth[fontSize][0], scrollUnitY = Helpers::getLineHeight();

    txt.reserve(100000);
    txt1.reserve(100000);
    txt2.reserve(100000);
    all.reserve(100000);

    bool firstExec = 1;
    int l1 = 0, l2 = 0;
    int lastCursorLine = 0;

    text1.create(maxRows, maxRows);
    text2.create(maxRows, maxRows);
    text3.create(maxRows, maxRows);

    text1.setSmooth(true);
    text2.setSmooth(true);
    text3.setSmooth(true);

    string path = "", buffer = "";
    int timer = 0;
    int cursorTimer = 0;
    bool cursorOnScreen = 0;
    bool cursorLineOnScreen = 1;
    bool leftButtonPressed = 0;
    bool selectFlag = 0;
    bool ctrlX = 0, ctrlV = 0, ctrlC = 0;

    int posCursorOnHold = -1;

    int lastDone = 0;
    int nr = 0;
    int cntX = 0;
    FILE *fptr = NULL;

    vector<int> positions, bit, gone, prv, nxt;
    int currentAppearance = 0;
    bool matchCase = 0, wholeWord = 0, findFlag = 0, replaceFlag = 0, replaceAllFlag = 0;
    string word, rword;
    string param;
    set<int> notRemoved;
    bool fileSaved = 1;
    wordWrap = 0;

    while (window.isOpen())
    {
        bool flag = 0;
        bool fontChanged = 0;
        bool renderAgain = 0;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);

            if (!Helpers::isAnyButtonPressed())
            {
                if (localPosition.x >= marginLeft && localPosition.y >= marginTop && localPosition.x < windowWidth && localPosition.y < windowHeight - marginBottom)
                {
                    int posCursor = String::findCursorPosition(S);
                    int newPosCursor = Render::moveCursorToClick(localPosition, S, scrollUnitY, l1, l2, Xoffset);
                    newPosCursor -= (newPosCursor > posCursor);

                    if (leftButtonPressed == 0)
                    {
                        String::del(posCursor, S);
                        leftButtonPressed = 1;
                        selectFlag = 0;

                        String::insert(newPosCursor, S);
                    }
                    else if (newPosCursor != posCursor)
                    {
                        selectFlag = 1;

                        if (newPosCursor < posCursor)
                            segmSelected = {newPosCursor, posCursor - 1};
                        else
                            segmSelected = {posCursor + 1, newPosCursor};
                    }

                    flag = 1;
                    renderAgain = 1;
                }

                if (selectFlag && localPosition.x < marginLeft)
                {
                    Xoffset -= scrollUnitX;
                    Xoffset = max(0, Xoffset);
                    flag = 1;
                    renderAgain = 1;
                }

                if (selectFlag && localPosition.x >= windowWidth)
                {
                    Xoffset += scrollUnitX;
                    flag = 1;
                    renderAgain = 1;
                }

                if (selectFlag && localPosition.y < marginTop)
                {
                    Yoffset -= scrollUnitY;
                    Yoffset = max(0, Yoffset);
                    flag = 1;
                    renderAgain = 1;
                }

                if (selectFlag && localPosition.y >= windowHeight - marginBottom)
                {
                    Yoffset += scrollUnitY;
                    flag = 1;
                    renderAgain = 1;
                }
            }
        }
        else if (selectFlag && ctrlX == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        {
            ctrlX = 1;
            int L = segmSelected.first;
            int R = segmSelected.second;

            String::Treap *s1 = 0, *s2 = 0, *s3 = 0;
            String::split(S, s2, s3, R);
            String::split(s2, s1, s2, L - 1);

            buffer = String::constructString(s2);
            String::copyTextToClipboard(buffer.c_str());
            // delete s2;
            String::del(s2);

            String::merge(S, s1, s3);
            selectFlag = 0;
            findFlag = 0;
            replaceFlag = 0;

            flag = 1;
            renderAgain = 1;
        }
        else if (selectFlag && ctrlC == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        {
            ctrlC = 1;
            int L = segmSelected.first;
            int R = segmSelected.second;

            String::Treap *s1 = 0, *s2 = 0, *s3 = 0;
            String::split(S, s2, s3, R);
            String::split(s2, s1, s2, L - 1);

            buffer = String::constructString(s2);
            String::copyTextToClipboard(buffer.c_str());

            String::merge(S, s1, s2);
            String::merge(S, S, s3);
        }
        else if (ctrlV == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::V))
        {
            int posCursor = String::findCursorPosition(S);
            ctrlV = 1;
            buffer = String::getTextFromClipboard();

            for (auto ch : buffer)
            {
                String::insert(posCursor, S, ch);
                posCursor++;
            }

            flag = 1;
            renderAgain = 1;
            selectFlag = 0;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if (String::len(S) > 1)
            {
                segmSelected = {1, String::len(S) - 1};
                buffer = String::constructRawString(S);
                flag = 1;
                selectFlag = 1;
            }
        }
        else
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    if (fileSaved == 1)
                    {
                        window.close();
                        break;
                    }

                    int closeOption = Windows::saveModal();

                    if (closeOption == IDCANCEL)
                    {
                        break;
                    }
                    else if (closeOption == IDYES)
                    {
                        if (path.size() == 0)
                            path = Windows::saveAS();

                        FILE* fptr = fopen(path.c_str(), "w");

                        if (fptr == NULL)
                        {
                            Windows::throwMessage("Wrong Path!");
                            break;
                        }

                        String::saveText(fptr, S);
                        fileSaved = 1;
                        fclose(fptr);
                        break;
                    }
                    else if (closeOption == IDNO)
                    {
                        window.close();
                        break;
                    }
                }

                if (event.type == sf::Event::MouseMoved)
                {
                    // set hover state for zoom buttons
                    zoomOutButton->setHoverState(zoomOutButton->isHovering());
                    zoomInButton->setHoverState(zoomInButton->isHovering());

                    // open menus if user is hovering over them
                    // set hover state for toggle menu buttons
                    for (int i = 0; i < 3; i++)
                    {
                        Button *toggleButton = menus[i]->getToggleButton();
                        if (toggleButton->isHovering())
                        {
                            toggleButton->setHoverState(true);
                            menus[i]->open();
                            menus[i]->setPosition(toolBarPositions[i]);
                        }
                        else
                            toggleButton->setHoverState(false);
                    }

                    // close menus if user isn't hovering over them anymore
                    for (int i = 0; i < 3; i++)
                        if (menus[i]->getIsOpen() && !menus[i]->isHovering() && !menus[i]->getToggleButton()->isHovering() && menus[i]->getPosition() == toolBarPositions[i])
                            menus[i]->close();

                    // set hover state for buttons inside menus
                    for (int i = 0; i < 3; i++)
                    {
                        Button **buttons = menus[i]->getButtons();
                        for (int j = 0; j < menus[i]->getButtonCount(); j++)
                            buttons[j]->setHoverState(buttons[j]->isHovering());
                    }
                }

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    if (event.key.code == 0)
                        leftButtonPressed = 0;

                    ctrlC = ctrlV = ctrlX = 0;
                }

                if (event.type == sf::Event::KeyReleased)
                {
                    int key = event.key.code;

                    if (key == 23)
                        ctrlX = 0;
                    else if (key == 2)
                        ctrlC = 0;
                    else if (key == 21)
                        ctrlV = 0;

                    break;
                }

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    int key = event.key.code;

                    if (key == 0)
                    {
                        if (zoomOutButton->isHovering())
                        {
                            fontSize -= fontUnit;
                            fontSize = max(fontUnit, fontSize);
                            zoomLevel = 100 * fontSize / 20;
                            zoomLevelTextBox->setContent(to_string(zoomLevel) + "%");
                            lineHeight = Helpers::getLineHeight();

                            String::updateWidth(S);
                            fontChanged = 1;
                            cursorTimer = 0;
                        }
                        else if (zoomInButton->isHovering())
                        {
                            fontSize += fontUnit;
                            fontSize = min(fontSize, maxFontSize);
                            zoomLevel = 100 * fontSize / 20;
                            zoomLevelTextBox->setContent(to_string(zoomLevel) + "%");

                            lineHeight = Helpers::getLineHeight();

                            String::updateWidth(S);
                            fontChanged = 1;
                            cursorTimer = 0;
                        }

                        else if (fileMenu->getIsOpen())
                        {
                            if (fileMenuButtons[0]->isHovering())
                            {
                                fileMenu->close();

                                path = Windows::open();

                                if (path.size() == 0)
                                    break;

                                HANDLE fileHandle = CreateFileA(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

                                if (fileHandle == INVALID_HANDLE_VALUE)
                                {
                                    Windows::throwMessage("Invalid Path");
                                    break;
                                }

                                HANDLE mappingHandle = CreateFileMapping(fileHandle, nullptr, PAGE_READONLY, 0, 0, nullptr);
                                char *data = (char *)(MapViewOfFile(mappingHandle, FILE_MAP_READ, 0, 0, 0));
                                DWORD fileSize = GetFileSize(fileHandle, nullptr);

                                String::del(S);
                                S = String::build(fileSize, data);
                                String::insert(1, S);
                                

                                cerr << "Read: " << fileSize << ' ' << "ch" << '\n';

                                UnmapViewOfFile(data);
                                CloseHandle(mappingHandle);
                                CloseHandle(fileHandle);

                                renderAgain = 1;
                                fileSaved = 1;
                                flag = 1;
                            }
                            else if (fileMenuButtons[1]->isHovering())
                            {
                                fileMenu->close();

                                if (path.size() == 0)
                                    path = Windows::saveAS();

                                FILE *fptr = fopen(path.c_str(), "w");

                                if (fptr == NULL)
                                {
                                    Windows::throwMessage("Wrong Path!");
                                    break;
                                }

                                String::saveText(fptr, S);
                                fileSaved = 1;
                                fclose(fptr);
                            }
                            else if (fileMenuButtons[2]->isHovering())
                            {
                                fileMenu->close();

                                path = Windows::saveAS();

                                if (path.size() == 0)
                                    break;

                                FILE *fptr = fopen(path.c_str(), "w");

                                if (fptr == NULL)
                                {
                                    Windows::throwMessage("Wrong Path!");
                                    break;
                                }

                                String::saveText(fptr, S);
                                fileSaved = 1;
                                fclose(fptr);
                            }
                        }
                        else if (editMenu->getIsOpen())
                        {
                            if (editMenuButtons[0]->isHovering())
                            {
                                editMenu->close();

                                if (selectFlag && ctrlC == 0)
                                {
                                    ctrlC = 1;
                                    int L = segmSelected.first;
                                    int R = segmSelected.second;

                                    String::Treap *s1 = 0, *s2 = 0, *s3 = 0;
                                    String::split(S, s2, s3, R);
                                    String::split(s2, s1, s2, L - 1);

                                    buffer = String::constructString(s2);
                                    String::copyTextToClipboard(buffer.c_str());

                                    String::merge(S, s1, s2);
                                    String::merge(S, S, s3);
                                }
                            }
                            else if (editMenuButtons[1]->isHovering())
                            {
                                editMenu->close();

                                if (ctrlV == 0)
                                {
                                    int posCursor = String::findCursorPosition(S);
                                    ctrlV = 1;

                                    buffer = String::getTextFromClipboard();

                                    for (auto ch : buffer)
                                    {
                                        String::insert(posCursor, S, ch);
                                        posCursor++;
                                    }

                                    flag = 1;
                                    renderAgain = 1;
                                    fileSaved = 0;
                                    selectFlag = findFlag = 0;
                                }
                            }
                            else if (editMenuButtons[2]->isHovering())
                            {
                                editMenu->close();

                                if (selectFlag && ctrlX == 0)
                                {
                                    ctrlX = 1;
                                    int L = segmSelected.first;
                                    int R = segmSelected.second;

                                    String::Treap *s1 = 0, *s2 = 0, *s3 = 0;
                                    String::split(S, s2, s3, R);
                                    String::split(s2, s1, s2, L - 1);

                                    buffer = String::constructString(s2);
                                    String::copyTextToClipboard(buffer.c_str());

                                    String::del(s2);

                                    String::merge(S, s1, s3);
                                    selectFlag = findFlag = 0;
                                    fileSaved = 0;
                                    flag = 1;
                                    renderAgain = 1;
                                }
                            }
                            else if (editMenuButtons[3]->isHovering())
                            {
                                editMenu->close();

                                /// apelat dupa ce faci setarile cu wholeWord si matchCase
                                word = Windows::getStringFromUser("Find");

                                if (word.size() == 0)
                                    break;

                                string s = String::constructRawString(S);

                                if (matchCase == 0)
                                {
                                    for (auto &i : word)
                                        if (i >= 'A' && i <= 'Z')
                                            i = i - 'A' + 'a';

                                    for (auto &i : s)
                                        if (i >= 'A' && i <= 'Z')
                                            i = i - 'A' + 'a';
                                }

                                ReplaceFind::KMP(s, word, positions, wholeWord);

                                if (positions.size() == 0)
                                {
                                    Windows::throwMessage("There are 0 matchings!");
                                    renderAgain = 1;
                                    flag = 1;
                                    break;
                                }

                                cerr << "Found: " << positions.size() << '\n';
                                cerr << "Positions: ";
                                for (auto i : positions)
                                    cerr << i << ' ';
                                cerr << '\n';
                                currentAppearance = 0;
                                findFlag = 1;
                                renderAgain = 1;
                                flag = 1;

                                break;
                            }
                            else if (editMenuButtons[4]->isHovering())
                            {
                                editMenu->close();

                                word = Windows::getStringFromUser("word");
                                rword = Windows::getStringFromUser("word");

                                if (word.size() == 0)
                                    break;

                                string s = String::constructRawString(S);

                                if (matchCase == 0)
                                {
                                    for (auto &i : word)
                                        if (i >= 'A' && i <= 'Z')
                                            i = i - 'A' + 'a';

                                    for (auto &i : s)
                                        if (i >= 'A' && i <= 'Z')
                                            i = i - 'A' + 'a';
                                }

                                ReplaceFind::KMP(s, word, positions, wholeWord);

                                if (positions.size() == 0)
                                {
                                    Windows::throwMessage("There are 0 matchings!");
                                    renderAgain = 1;
                                    flag = 1;
                                    break;
                                }

                                prv.clear();
                                bit.clear();
                                nxt.clear();
                                gone.clear();

                                prv.resize(positions.size(), -1);
                                nxt.resize(positions.size(), -1);
                                gone.resize(positions.size(), 0);
                                bit.resize(positions.size(), 0);
                                notRemoved.clear();

                                for (int i = 1; i < positions.size(); i++)
                                    prv[i] = i - 1;

                                for (int i = 0; i + 1 < positions.size(); i++)
                                    nxt[i] = i + 1;

                                for (int i = 0; i < positions.size(); i++)
                                    notRemoved.insert(i);

                                currentAppearance = 0;
                                replaceFlag = 1;
                                renderAgain = 1;
                                flag = 1;

                                break;
                            }
                            else if (editMenuButtons[5]->isHovering())
                            {
                                editMenu->close();

                                if (String::len(S) > 1)
                                {
                                    segmSelected = {1, String::len(S) - 1};
                                    buffer = String::constructRawString(S);
                                    String::copyTextToClipboard(buffer.c_str());
                                    flag = 1;
                                    selectFlag = 1;
                                    renderAgain = 1;
                                }

                                break;
                            }
                            else
                                editMenu->close();
                        }
                        else if (optionsMenu->getIsOpen())
                        {
                            if (optionsMenuButtons[0]->isHovering())
                            {
                                optionsMenu->close();

                                showLineNumbers = !showLineNumbers;
                                optionsMenuButtons[0]->setLabel(toggleLinesButtonLabels[showLineNumbers]);
                                renderAgain = 1;
                            }
                            else if (optionsMenuButtons[1]->isHovering())
                            {
                                optionsMenu->close();

                                string line = Windows::getStringFromUser("Go to line");
                                int l = min(String::findNumberOfEndlines(1, String::len(S), S) + 1, stoi(line));
                                Xoffset = 0;
                                Yoffset = (l - 1) * lineHeight;
                                renderAgain = 1;
                                flag = 1;
                                break;
                            }
                            else if (optionsMenuButtons[2]->isHovering())
                            {
                                optionsMenu->close();

                                // TODO: let user customize format via modal
                                string data = Helpers::getTime("%I:%M %p %m/%d/%Y");
                                int posCursor = String::findCursorPosition(S);

                                for (auto i : data)
                                {
                                    String::insert(posCursor, S, i);
                                    posCursor++;
                                }

                                flag = 1;
                                renderAgain = 1;
                                fileSaved = 0;
                            }
                            else if (optionsMenuButtons[3]->isHovering())
                            {
                                optionsMenu->close();

                                Helpers::changeTheme(text, ptext1, ptext2);
                                renderAgain = 1;
                            }
                        }
                        // change cursor position inside text visible in the viewport
                        else
                        {
                            cursorTimer = 0;
                            break;
                        }
                    }

                    // right click
                    // set edit menu position to cursor position and then open it
                    else if (key == 1)
                    {
                        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                        editMenu->setPosition(sf::Vector2f(localPosition.x, localPosition.y));
                        editMenu->open();
                        break;
                    }

                    flag = 1;

                    selectFlag = findFlag = 0;

                    renderAgain |= Render::updateViewX(S, Xoffset, scrollUnitX);
                    renderAgain |= Render::updateViewY(S, Yoffset, scrollUnitY);

                    break;
                }

                if (event.type == sf::Event::KeyPressed)
                {
                    int key = event.key.code;
                    cerr << "key is " << key << '\n';

                    if (key == 36) /// escape
                    {
                        if (replaceFlag == 1)
                        {
                            replaceFlag = 0;
                        }
                        else if (findFlag == 1)
                        {
                            findFlag = 0;
                        }
                        else
                            window.close();

                        break;
                    }
                    else if (key == 73) /// up arrow
                    {
                        int posCursor = String::findCursorPosition(S);
                        int p1 = String::findPrevEndline(posCursor, S);

                        if (p1)
                        {
                            int p2 = String::findPrevEndline(p1, S);
                            int chCurr = posCursor - p1 - 1;
                            int chPrev = p1 - p2 - 1;
                            String::del(posCursor, S);
                            String::insert(p2 + min(chCurr, chPrev) + 1, S);
                            renderAgain = 1;
                            cursorTimer = 0;
                        }

                        findFlag = 0;
                        replaceFlag = 0;

                        selectFlag = 0;

                        renderAgain = 1;
                        flag = 1;

                        renderAgain |= Render::updateViewX(S, Xoffset, scrollUnitX);
                        renderAgain |= Render::updateViewY(S, Yoffset, scrollUnitY);

                        break;
                    }
                    else if (key == 74) /// down arrow
                    {
                        int posCursor = String::findCursorPosition(S);
                        int p1 = String::findNextEndline(posCursor, S);
                        int p0 = String::findPrevEndline(posCursor, S);

                        if (p1 <= len(S))
                        {
                            int p2 = String::findNextEndline(p1, S);
                            int chCurr = posCursor - p0 - 1;
                            int chNext = p2 - p1 - 1;
                            String::del(posCursor, S);
                            String::insert(p1 + min(chCurr, chNext) + 1 - 1, S);
                            renderAgain = 1;
                            cursorTimer = 0;
                        }

                        findFlag = 0;
                        replaceFlag = 0;
                        selectFlag = 0;

                        renderAgain = 1;
                        flag = 1;

                        renderAgain |= Render::updateViewX(S, Xoffset, scrollUnitX);
                        renderAgain |= Render::updateViewY(S, Yoffset, scrollUnitY);

                        break;
                    }
                    else if (key == 71) /// left arrow
                    {
                        if (replaceFlag == 1)
                        {
                            int pap = ReplaceFind::findPrevValidAppearance(currentAppearance, bit, positions, gone, rword, word, prv, nxt, notRemoved);

                            if (pap != -1)
                                currentAppearance = pap;
                            else
                                break;

                            renderAgain = 1;
                            flag = 1;

                            selectFlag = 0;
                            findFlag = 0;

                            break;
                        }
                        else if (findFlag == 1)
                        {
                            currentAppearance--;
                            currentAppearance = max(0, currentAppearance);
                            cerr << "After left arrow: " << currentAppearance << '\n';

                            renderAgain = 1;
                            flag = 1;

                            selectFlag = 0;
                            replaceFlag = 0;

                            break;
                        }
                        else
                        {
                            int posCursor = String::findCursorPosition(S);

                            if (posCursor > 1)
                            {
                                String::del(posCursor, S);
                                String::insert(posCursor - 1, S);
                                cursorTimer = 0;
                            }

                            flag = 1;
                            selectFlag = 0;

                            renderAgain |= Render::updateViewX(S, Xoffset, scrollUnitX);
                            renderAgain |= Render::updateViewY(S, Yoffset, scrollUnitY);
                        }

                        break;
                    }
                    else if (key == 72) /// right arrow
                    {
                        if (replaceFlag == 1)
                        {
                            int nap = ReplaceFind::findNextValidAppearance(currentAppearance, bit, positions, gone, rword, word, prv, nxt, notRemoved);
                            if (nap != -1)
                                currentAppearance = nap;
                            else
                                break;

                            renderAgain = 1;
                            flag = 1;

                            selectFlag = 0;
                            findFlag = 0;

                            break;
                        }
                        else if (findFlag == 1)
                        {
                            currentAppearance++;
                            currentAppearance = min((int)positions.size() - 1, currentAppearance);

                            cerr << "After right arrow: " << currentAppearance << '\n';

                            renderAgain = 1;
                            flag = 1;

                            selectFlag = 0;
                            replaceFlag = 0;

                            break;
                        }
                        else
                        {
                            int posCursor = String::findCursorPosition(S);

                            if (posCursor < String::len(S))
                            {
                                String::del(posCursor, S);
                                String::insert(posCursor + 1, S);
                                cursorTimer = 0;
                            }

                            flag = 1;
                            selectFlag = 0;

                            renderAgain |= Render::updateViewX(S, Xoffset, scrollUnitX);
                            renderAgain |= Render::updateViewY(S, Yoffset, scrollUnitY);
                        }

                        break;
                    }
                    else if (key == 43) /// not functional ignora
                    {
                        flag = 1;
                        renderAgain = 1;

                        wordWrap ^= 1;

                        if (wordWrap == 1)
                        {
                            String::setW(String::findCursorPosition(S), 0, S);
                        }
                        else
                        {
                            String::setW(String::findCursorPosition(S), charWidth[fontSize][' '], S);
                        }

                        break;
                    }
                    else if (key == 58)
                    {
                        if (replaceFlag == 0)
                            break;

                        if (currentAppearance == -1)
                        {
                            Windows::throwMessage("There are no more matchings!");
                            renderAgain = 1;
                            flag = 1;
                            replaceFlag = 0;
                            break;
                        }

                        int L = ReplaceFind::findRealPosition(currentAppearance, positions, bit, word, rword);
                        String::replace(L, L + word.size() - 1, rword, S);
                        ReplaceFind::delAp(currentAppearance, prv, nxt, bit, gone, notRemoved);
                        int nxtAppearance = ReplaceFind::findNextValidAppearance(currentAppearance, bit, positions, gone, rword, word, prv, nxt, notRemoved);
                        int prvAppearance = ReplaceFind::findPrevValidAppearance(currentAppearance, bit, positions, gone, rword, word, prv, nxt, notRemoved);

                        nxt[currentAppearance] = prv[currentAppearance] = -1;
                        currentAppearance = max(nxtAppearance, prvAppearance);

                        fileSaved = 0;
                        renderAgain = 1;
                        flag = 1;
                        break;
                    }
                    else if (key == 85)
                    {
                        replaceAllFlag = 1;

                        set<int> snapshot = notRemoved;

                        for (auto currentAppearance : snapshot)
                        {
                            if (ReplaceFind::canReplace(currentAppearance, bit, positions, gone, rword, word) == 0)
                            {
                                continue;
                            }

                            int L = ReplaceFind::findRealPosition(currentAppearance, positions, bit, word, rword);
                            String::replace(L, L + word.size() - 1, rword, S);
                            ReplaceFind::delAp(currentAppearance, prv, nxt, bit, gone, notRemoved);
                        }

                        fileSaved = 0;
                        renderAgain = 1;
                        flag = 1;
                    }
                    else
                        break;

                    break;
                }

                if (event.type == sf::Event::TextEntered) /// ce scrie user-ul
                {
                    int ch = event.text.unicode;

                    cerr << "txt is " << ch << "\n";
                    if (ch == 27 || ch == 24 || ch == 3 || ch == 1 || ch == 22 || ch == 13 && replaceFlag == 1)
                        break;

                    int posCursor = String::findCursorPosition(S);

                    if (ch == 8)
                    {
                        if (selectFlag == 1)
                        {
                            String::del(segmSelected.first, segmSelected.second, S);
                            selectFlag = 0;
                        }
                        else if (posCursor > 1)
                            String::del(posCursor - 1, S);

                        renderAgain = 1;
                    }
                    else
                    {
                        if (selectFlag == 1)
                        {
                            int L = segmSelected.first;
                            int R = segmSelected.second;

                            String::Treap *s1 = 0, *s2 = 0, *s3 = 0;
                            String::split(S, s2, s3, R);
                            String::split(s2, s1, s2, L - 1);

                            String::del(s2);
                            String::merge(S, s1, s3);
                            renderAgain = 1;
                        }

                        if (ch == 13)
                            ch = 10;
                        String::insert(String::findCursorPosition(S), S, ch);
                    }

                    fileSaved = 0;
                    flag = 1;
                    selectFlag = findFlag = 0;

                    renderAgain |= Render::updateViewX(S, Xoffset, scrollUnitX);
                    renderAgain |= Render::updateViewY(S, Yoffset, scrollUnitY);

                    break;
                }

                if (event.type == sf::Event::MouseWheelMoved) /// scroll up and down
                {
                    int direction = event.mouseWheel.delta;

                    if (direction == +1)
                        Yoffset -= scrollUnitY, Yoffset = max(0, Yoffset);
                    if (direction == -1)
                        Yoffset += scrollUnitY;

                    renderAgain = 1;
                    flag = 1;

                    break;
                }

                if (event.type == sf::Event::Resized)
                {
                    // update the view to the new size of the window
                    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    window.setView(sf::View(visibleArea));
                    renderAgain = 1;
                    flag = 1;
                    windowWidth = event.size.width;
                    windowHeight = event.size.height;

                    bottomSeparator.setSize(sf::Vector2f(windowWidth, 1));
                    bottomSeparator.setPosition(0, windowHeight - marginBottom);
                    topSeparator.setSize(sf::Vector2f(windowWidth, 1));
                    topSeparator.setPosition(sf::Vector2f(0, marginTop));

                    lineNumbersBackground.setSize(sf::Vector2f(marginLeft, windowHeight));
                    lineNumbersBackground.setPosition(0, marginTop);
                    statusBarBackground.setSize(sf::Vector2f(windowWidth, marginBottom));
                    statusBarBackground.setPosition(sf::Vector2f(0, windowHeight - marginBottom));
                    toolBarBackground.setPosition(0, 0);
                    toolBarBackground.setSize(sf::Vector2f(windowWidth, marginTop));

                    break;
                }
            }

        window.clear(currentThemeColors.background);

        timer++;
        timer %= timeUnit;

        cursorTimer++;
        cursorTimer %= timeUnit * 2;

        if (cursorTimer % (timeUnit * 2) <= timeUnit)
            cursorBox.setFillColor(currentThemeColors.text);
        else if (cursorTimer % (timeUnit * 2) != 0)
            cursorBox.setFillColor(currentThemeColors.background);

        if (flag || firstExec)
        {
            scrollUnitX = charWidth[fontSize][0], scrollUnitY = Helpers::getLineHeight();

            if (wordWrap == 1)
            {
                if (fontChanged || firstExec)
                {
                    cursorHeight = lineHeight - 2;
                    cursorWidth = 1;
                }

                Xoffset = 0; /// reset de fiecare data pentru ca afisezi de la inceputul liniei
                l1 = max(1, (Yoffset) / scrollUnitY + 1);
                firstExec = 0;
                int linesVisible = (windowHeight - marginBottom - marginTop + lineHeight - 1) / lineHeight;
                int cntLine = 0;
                int noLines = String::findNumberOfEndlines(1, String::len(S), S) + 1;
                int l2;
                int posCursor = String::findCursorPosition(S);
                int cursorLine = 0;

                text.setCharacterSize(fontSize);
                text1.clear(sf::Color(0, 0, 0, 0));
                cursorLineOnScreen = 0;
                cursorOnScreen = 0;

                for (l2 = l1; l2 <= noLines && cntLine <= linesVisible; l2++)
                {
                    int p1 = String::findKthLine(l2, S);
                    /// S[p1] == '\n' caz special

                    string line = "";
                    string number = to_string(l2);

                    if (number.length() > lineNumbersMaxDigits)
                        lineNumbersMaxDigits = number.length();

                    for (int j = 0; j < lineNumbersMaxDigits - number.length(); j++)
                        line += " ";

                    line += number;

                    Render::centerText(text, line, marginTop + cntLine * lineHeight, 5);
                    text.setLetterSpacing(0.7);
                    text1.draw(text);
                    text.setLetterSpacing(1);
                    marginLeft = showLineNumbers * (lineNumbersMaxDigits + 1) * charWidth[fontSize]['9'];
                    paddingLeft = 0.5 * charWidth[fontSize]['a'];

                    if (String::len(S) + 1 == p1 || String::get(p1, S) == 10)
                    {
                        cntLine++;
                        continue;
                    }

                    int p2 = String::findNextEndline(p1, S) - 1;
                    int splitedLines = 0;

                    while (p1 <= p2 && cntLine <= linesVisible)
                    {
                        splitedLines++;
                        int p3 = String::getLastSeen(p1, p2, windowWidth - marginLeft, S);
                        // if (p3 == posCursor && p3 < String::len(S)) p3++;
                        cerr << p3 << ' ';

                        if (p3 != p2)
                        {
                            char ch1 = String::get(p3, S);
                            char ch2 = String::get(p3 + 1, S);

                            if (p3 + 1 == posCursor && p3 + 2 <= String::len(S))
                                ch2 = String::get(p3 + 2, S);

                            while (p3 >= p1 && ReplaceFind::isValid(ch2) && (p3 == posCursor || ReplaceFind::isValid(String::get(p3, S))))
                                p3--;

                            if (p3 < p1)
                            {
                                p3 = String::getLastSeen(p1, p2, windowWidth - marginLeft, S);
                            }
                        }

                        cerr << "current line: " << cntLine << ' ' << p1 << ' ' << p3 << ' ' << posCursor << '\n';

                        cntLine++;
                        string ln = String::constructString(p1, p3, S);
                        Render::centerText(text, ln, marginTop + lineHeight * (cntLine - 1));

                        if (p1 <= posCursor && posCursor <= p3)
                        {
                            float cw = Render::splitCursorLine(text, text, ptext2, ln, posCursor - p1 + 1, 0);
                            cursorLineOnScreen = 1;
                            cerr << "cw is" << ' ' << cw << ' ' << posCursor - p1 + 1 << '\n';
                            cursorLine = l2;
                            cursorBox.setSize(sf::Vector2f(cursorWidth, cursorHeight));
                            cursorBox.setPosition((float)marginLeft + paddingLeft + cw, (cntLine - 1) * lineHeight + marginTop);
                            cursorOnScreen = 1;
                        }

                        text1.draw(text);
                        p1 = p3 + 1;
                    }

                    if (cursorLine == l2)
                    {
                        cursorLineHighlight.setSize(sf::Vector2f(windowWidth, splitedLines * lineHeight));
                        cursorLineHighlight.setPosition(0, marginTop + (cntLine - splitedLines) * lineHeight);
                    }
                }

                img1.setTexture(text1.getTexture());
                text1.display();
            }
            else
            {
                renderAgain |= firstExec;
                renderAgain |= fontChanged;

                if (fontChanged || firstExec)
                {
                    cursorHeight = lineHeight - 2;
                    cursorWidth = 1;
                }

                fontChanged = 0;
                firstExec = 0;

                int posCursor = String::findCursorPosition(S);
                int cursorLine = String::findNumberOfEndlines(1, posCursor, S) + 1;
                int p = String::findKthLine(cursorLine, S);
                int fp = String::getFirstSeen(p, posCursor, Xoffset, S);
                int lp = String::getLastSeen(p, posCursor, Xoffset + windowWidth - marginLeft, S);
                if (lp < posCursor)
                    fp = -1;

                renderAgain |= lastCursorLine != cursorLine;

                if (findFlag == 1)
                {
                    if (currentAppearance < positions.size() && !ReplaceFind::isApOnScreen(positions[currentAppearance], word.size()))
                    {
                        int P = positions[currentAppearance];
                        int L = String::findNumberOfEndlines(1, P, S) + 1;
                        int F = String::findKthLine(L, S);
                        Yoffset = (L - 1) * lineHeight;
                        Xoffset = String::findWidth(F, P - 1, S);
                    }

                    renderAgain = 1;
                }

                if (replaceFlag == 1)
                {

                    Render::render(l1, l2, S, Yoffset, Xoffset, cursorLine, text, scrollUnitY);

                    if (currentAppearance != -1 && currentAppearance < positions.size() && !ReplaceFind::isApOnScreen(ReplaceFind::findRealPosition(currentAppearance, positions, bit, word, rword), word.size()))
                    {
                        int P = ReplaceFind::findRealPosition(currentAppearance, positions, bit, word, rword);
                        int L = String::findNumberOfEndlines(1, P, S) + 1;
                        int F = String::findKthLine(L, S);
                        Yoffset = (L - 1) * lineHeight;
                        Xoffset = String::findWidth(F, P - 1, S);
                    }

                    renderAgain = 1;
                }

                if (renderAgain == 1)
                {
                    Render::render(l1, l2, S, Yoffset, Xoffset, cursorLine, text, scrollUnitY);
                }
                else
                {
                    if (cursorLine >= l1 && cursorLine <= l2)
                    {
                        Render::updateTextLine(cursorLine - l1, renderLines, String::constructRenderedLine(cursorLine, S, Xoffset, cursorLine - l1));
                        text.setString(renderLines[cursorLine - l1]);
                    }
                }

                string cursorTextLine = (cursorLine >= l1 && cursorLine <= l2 ? renderLines[cursorLine - l1] : "");
                float cw = Render::splitCursorLine(text, ptext1, ptext2, cursorTextLine, posCursor - fp + 1, fp);

                if (cursorLine >= l1 && cursorLine <= l2)
                    cursorLineOnScreen = 1;
                else
                    cursorLineOnScreen = 0;

                if (cursorLine >= l1 && cursorLine <= l2 && fp != -1)
                {
                    cursorBox.setSize(sf::Vector2f(cursorWidth, cursorHeight));
                    cursorBox.setPosition((float)marginLeft + cw + paddingLeft, (cursorLine - l1) * lineHeight + marginTop);

                    cursorOnScreen = 1;
                }
                else
                    cursorOnScreen = 0;

                cursorLineHighlight.setSize(sf::Vector2f(windowWidth, lineHeight));
                cursorLineHighlight.setPosition(0, (cursorLine - l1) * lineHeight + marginTop);

                lastCursorLine = cursorLine;

                selectedBoxes.clear();

                if (selectFlag)
                {
                    int L = segmSelected.first;
                    int R = segmSelected.second;

                    for (int i = 0; i < sizeRLines; i++)
                    {
                        int l = segmOnScreen[i].first;
                        int r = segmOnScreen[i].second;

                        int li = max(l, L);
                        int ri = min(r, R);

                        if (li > ri)
                            continue;

                        int y = i * lineHeight + marginTop;
                        int x = marginLeft;

                        int w = String::findWidth(l, li - 1, S);
                        int W = String::findWidth(li, ri, S);

                        box.setPosition(w + marginLeft + paddingLeft + (cursorLine - l1 == i && li == posCursor + 1 ? -charWidth[fontSize][' '] : 0), y);
                        box.setSize(sf::Vector2f(W, lineHeight));
                        box.setFillColor(currentThemeColors.selectHighlight);
                        selectedBoxes.push_back(box);
                    }
                }

                if (findFlag)
                {
                    for (int i = 0; i < sizeRLines; i++)
                    {
                        int l = segmOnScreen[i].first;
                        int r = segmOnScreen[i].second;

                        if (l == -1)
                            continue;

                        int p = lower_bound(positions.begin(), positions.end(), l) - positions.begin();
                        int y = i * lineHeight + marginTop;
                        //  cerr << "On line " << i + 1 << ": ";

                        while (p < positions.size() && positions[p] <= r)
                        {
                            //      cerr << positions[p] << ' ';
                            int w = String::findWidth(l, positions[p] - 1, S);
                            int W = String::findWidth(positions[p], positions[p] + word.size() - 1, S);

                            box.setPosition(marginLeft + w + paddingLeft, y);
                            box.setSize(sf::Vector2f(W, lineHeight));
                            if (p != currentAppearance)
                                box.setFillColor(sf::Color(255, 255, 0, 128));
                            else
                                box.setFillColor(sf::Color(255, 187, 0, 128));
                            selectedBoxes.push_back(box);
                            p++;
                        }

                        // cerr << '\n';
                    }

                    // cerr << "\n\n";
                }

                if (replaceFlag)
                {
                    for (int i = 0; i < sizeRLines; i++)
                    {
                        int l = segmOnScreen[i].first;
                        int r = segmOnScreen[i].second;

                        if (l == -1)
                            continue;

                        int p = ReplaceFind::traceFirstApToRender(l, positions, bit, notRemoved, word, rword);
                        int y = i * lineHeight + marginTop;
                        // cerr << "On line " << i + 1 << ": " << p;

                        while (p != -1 && p < positions.size() && ReplaceFind::findRealPosition(p, positions, bit, word, rword) <= r)
                        {
                            int P = ReplaceFind::findRealPosition(p, positions, bit, word, rword);
                            int w = String::findWidth(l, P - 1, S);
                            int W = String::findWidth(P, P + word.size() - 1, S);

                            box.setPosition(marginLeft + w + paddingLeft, y);
                            box.setSize(sf::Vector2f(W, lineHeight));
                            if (p != currentAppearance)
                                box.setFillColor(sf::Color(255, 255, 0, 128));
                            else
                                box.setFillColor(sf::Color(255, 187, 0, 128));
                            selectedBoxes.push_back(box);
                            p = ReplaceFind::findNextValidAppearance(p, bit, positions, gone, rword, word, prv, nxt, notRemoved);
                            //   cerr << p << ' ';
                        }
                        // cerr << '\n';
                    }
                    // cerr << "\n\n";
                }
            }
        }

        if (wordWrap == 0)
        {
            if ((findFlag | replaceFlag) && flag == 1)
            {
                int highlighted = 0;

                for (int i = 0; i < selectedBoxes.size(); i++)
                {
                    if (selectedBoxes[i].getFillColor() == sf::Color(255, 187, 0, 128))
                        highlighted = i;
                }

                for (int i = 0; i < highlighted; i++)
                {
                    if (selectedBoxes[i].getPosition().y == selectedBoxes[i + 1].getPosition().y)
                    {
                        selectedBoxes[i].setSize(sf::Vector2f(min(selectedBoxes[i + 1].getPosition().x - selectedBoxes[i].getPosition().x, selectedBoxes[i].getSize().x), lineHeight));
                    }
                }

                for (int i = highlighted + 1; i < selectedBoxes.size(); i++)
                {
                    if (selectedBoxes[i].getPosition().y == selectedBoxes[i - 1].getPosition().y)
                    {
                        int oldX = selectedBoxes[i].getPosition().x;
                        selectedBoxes[i].setPosition(max(selectedBoxes[i].getPosition().x, selectedBoxes[i - 1].getPosition().x + selectedBoxes[i - 1].getSize().x), selectedBoxes[i].getPosition().y);
                        selectedBoxes[i].setSize(sf::Vector2f(selectedBoxes[i].getSize().x - (selectedBoxes[i].getPosition().x - oldX), lineHeight));
                    }
                }
            }

            if (selectFlag | findFlag | replaceFlag)
                for (auto box : selectedBoxes)
                    window.draw(box);

            window.draw(lineNumbersBackground);
            if (showLineNumbers)
                window.draw(img3);

            if (cursorOnScreen)
                window.draw(cursorBox);
            if (cursorLineOnScreen && selectFlag == 0 && findFlag == 0 && replaceFlag == 0)
                window.draw(cursorLineHighlight);

            window.draw(img1);
            window.draw(ptext1);
            window.draw(img2);
        }
        else
        {
            if (cursorOnScreen)
                window.draw(cursorBox);

            if (cursorLineOnScreen)
                window.draw(cursorLineHighlight);

            window.draw(img1);
        }

        Helpers::updateStatusBarInfo();
        Helpers::updateStatusBarPositions();
    
        window.draw(statusBarBackground);
        window.draw(toolBarBackground);
        lineCountTextBox->draw();
        lineColumnTextBox->draw();
        if (selectedBoxes.size())
            selectedCharacterCountTextBox->draw();
        zoomLevelTextBox->draw();

        zoomOutButton->draw();
        zoomInButton->draw();

        window.draw(topSeparator);
        window.draw(bottomSeparator);

        for (int i = 0; i < 3; i++)
            menus[i]->draw();

        window.display();
    }

    return 0;
}
