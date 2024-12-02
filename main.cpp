#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

using namespace std;

const int C = 500;

int pos;
int charSize[C][C];
int charHeight[C][C];
int rev[C * C] , dis[C * C];

const int DIM = 1000;
const int unit = 100;
const int fontUnit = 10;
const int timeUnit = 3000;

int fontSize = 20;
int offset = 0;
int textOffset = 15;

void modify(char ch , string &s) ///adauga noul caracter introdus (incluzand si backspace
{
    if (ch == 27) /// escape
        return;

    if (ch == 8)
    {
        if (pos)
        {
            s.erase(s.begin() + pos - 1);
            pos--;
        }
        return;
    }

    s.insert(pos + s.begin(), ch);
    if (s[pos] == 13) s[pos] = 10;

    pos++;
}

int findPrevEndLine(string &s , int pos)///gaseste cel mai apropiat endline mai mic ca pozitia curenta a cursorului
{
    if (pos < 0)
        return -1;

    for (int i = pos; i >= 0; i--)
        if (s[i] == 10)
            return i;

    return -1;
}

int findNextEndLine(string &s , int pos)///gaseste cel mai apropiat endline mai mare ca pozitia curenta a cursorului
{
    if (pos >= s.size())
        return s.size();

    for (int i = pos ; i < s.size(); i++)
        if (s[i] == 10)
            return i;

    return s.size();
}

int moveTextBar(int source , int destination , string &s) ///permuta cursorul la pozitia dorita
{
    int sgn = (source < destination ? +1 : -1);

    for (int i = source; i != destination; i += sgn)
    {
        swap(s[i], s[i + sgn]);
    }

    return destination;
}

int updateTextOnDisplay(string &sRaw , string &s)///recalculeaza daca textul mai are nevoie de endline-uri pentru a incapea perfect pe orizontala
{
    s.clear();
    int currWidth = 0;
    int currPos = 0;
    int posOnScreen = -1;

    for (auto i : sRaw)
    {
        s += i;
        currWidth += charSize[fontSize][i];
        if (i == 10) currWidth = 0;

        if (currWidth >= DIM)
        {
            s.back() = 10;
            s += i;
            currWidth = charSize[fontSize][i];
        }

        if (currPos == pos)
            posOnScreen = s.size() - 1;

        rev[s.size() - 1] = currPos;
        dis[currPos] = s.size() - 1;
        currPos++;
    }

    return posOnScreen;
}

int findNumberOfLines(string &s , int pos)
{
    int nr = 1;

    for (int i = 0; i <= pos; i++)
        if (s[i] == 10)
            nr++;

    return nr;
}

string getPathFromUser()///ia path-ul introdus de catre utilizator pentru a salva fisierul
{
    const int DIM = 200;
    sf::RenderWindow window(sf::VideoMode(DIM * 4, DIM / 4 - 10), "Save AS");
    sf::Image mainIcon;
    mainIcon.loadFromFile("assets/fonts/main_icon.png");
    window.setIcon(mainIcon.getSize().x, mainIcon.getSize().y, mainIcon.getPixelsPtr());

    sf::Event event;
    sf::Text text, pth;
    sf::Font font;

    font.loadFromFile("assets/fonts/arial.ttf");

    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setString("EnterPath: ");

    pth.setFont(font);
    pth.setFillColor(sf::Color::Green);
    pth.setString("");
    pth.setPosition(150, 0);

    string path;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                //cerr << event.key.code << ' ';
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
                else path += ch;

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

string getStringFromUser()///citeste cuvantul pe care vrea user-ul sa-l caute
{
    const int DIM = 200;
    sf::RenderWindow window(sf::VideoMode(DIM * 4, DIM / 4 - 10), "Save AS");
    sf::Image mainIcon;
    mainIcon.loadFromFile("assets/images/main_icon.png");
    window.setIcon(mainIcon.getSize().x, mainIcon.getSize().y, mainIcon.getPixelsPtr());

    sf::Event event;
    sf::Text text, pth;
    sf::Font font;

    font.loadFromFile("assets/fonts/arial.ttf");

    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setString("Enter keyword: ");

    pth.setFont(font);
    pth.setFillColor(sf::Color::Green);
    pth.setString("");
    pth.setPosition(210 , 0);

    string path;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                //cerr << event.key.code << ' ';
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
                else path += ch;

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

void throwMessage(string message)///ia path-ul introdus de catre utilizator pentru a salva fisierul
{
    const int DIM = 200;
    sf::RenderWindow window(sf::VideoMode(DIM * 4, DIM / 4 - 10) , "");

    sf::Event event;
    sf::Text text;
    sf::Font font;

    font.loadFromFile("assets/fonts/arial.ttf");

    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setString(message);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                //cerr << event.key.code << ' ';
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

int findRealWidth(string& s, int spos)
{
    int w = 0;

    for (int i = spos - 1; i >= 0 && s[i] != 10; i--)
        w += charSize[fontSize][s[i]];

    return w;
}

sf::RectangleShape selectCharacterInString(string& s, int posOnScreen) ///creeaza un dreptunghi pe caracterul indicat de pozitian posOnScreen din s
{
    int width = posOnScreen - findPrevEndLine(s, posOnScreen);
    int height = findNumberOfLines(s, posOnScreen);
    int unitWidth = charSize[fontSize]['|'];
    int unitHeight = charHeight[fontSize]['|'];

    int xBox = findRealWidth(s , posOnScreen);
    int yBox = unitHeight * (height - 1);

    sf::RectangleShape box;
    box.setPosition(xBox , yBox + textOffset);
    box.setSize(sf::Vector2f(unitWidth , unitHeight));
    box.setFillColor(sf::Color(100 , 100, 100, 100));

    cerr << xBox << ' ' << yBox << '\n';
    return box;
}

sf::RectangleShape selectCharacterVisual(sf::Vector2i localPosition) ///creeaza un dreptunghi pe caracterul unde se afla cursorul 
{
    int unitWidth = charSize[fontSize]['|'];
    int unitHeight = charHeight[fontSize]['|'];

    int width = (localPosition.x) / unitWidth;
    int height = (localPosition.y - textOffset) / unitHeight;

    int xCoord = unitWidth * (width);
    int yCoord = unitHeight * (height);

    sf::RectangleShape box;
    box.setPosition(xCoord, yCoord + textOffset);
    box.setSize(sf::Vector2f(unitWidth, unitHeight));

    box.setFillColor(sf::Color(73, 252, 3 , 100));
    return box;
}

int searchForBox(sf::RectangleShape box , string &s)
{
    int unitWidth = charSize[fontSize]['|'];
    int unitHeight = charHeight[fontSize]['|'];

    int xBox = box.getPosition().x;
    int yBox = box.getPosition().y;

    int X = 0, Y = 0 + textOffset;
    int cnd = -1;
    int cndE = -1;
    int nr = 0;

    for (int i = 0; i < s.size(); i++)
    {
        if (X == xBox && Y == yBox)
            return i;

        if (Y == yBox) 
            nr++ , cndE = i;

        if (Y == yBox && s[i] != 10)
            cnd = i;

        if (s[i] == 10)
        {
            X = 0;
            Y += unitHeight;
        }
        else X += unitWidth;
    }

    if (nr == 1) return cndE - 1;
    return cnd;
}

namespace debug
{
    void printEndLines(string& s)
    {
        cerr << "ENDL positions: ";

        for (int i = 0; i < s.size(); i++)
            if (s[i] == 10)
                cerr << i << ' ';

        cerr << '\n';
    }

    void Test()
    {
        const int DIM = 200;
        sf::RenderWindow window(sf::VideoMode(DIM, DIM), "Text Editor");

        sf::Event event;
        sf::Text text;
        sf::Font font;

        font.loadFromFile("assets/fonts/arial.ttf");
        text.setFont(font);
        text.setFillColor(sf::Color::Red);
        text.setString("abc");

        sf::Text TEXT;
        TEXT.setFont(font);
        TEXT.setFillColor(sf::Color::Green);
        TEXT.setString("pup");

        while (window.isOpen())
        {
            while (window.pollEvent(event))
            {

            }



            window.clear();
            window.draw(TEXT);
            window.draw(text);
            window.display();
        }
    }
}

int main()
{
    FILE* fptr;

    string s, sRaw = " ", t;

    sf::RenderWindow window(sf::VideoMode(DIM , DIM), "Text Editor");
    sf::View view;
    sf::Image mainIcon;
    mainIcon.loadFromFile("assets/images/main_icon.png");
    window.setIcon(mainIcon.getSize().x, mainIcon.getSize().y, mainIcon.getPixelsPtr());
    sf::RectangleShape button1(sf::Vector2f(50.f , 25.f));
    sf::RectangleShape button2(sf::Vector2f(50.f , 25.f));
    sf::RectangleShape button3(sf::Vector2f(50.f , 25.f));
    sf::RectangleShape button4(sf::Vector2f(50.f , 25.f));
    sf::RectangleShape button5(sf::Vector2f(50.f , 25.f));
    sf::RectangleShape button6(sf::Vector2f(50.f , 25.f));
    sf::RectangleShape button7(sf::Vector2f(50.f , 25.f));
    sf::RectangleShape button8(sf::Vector2f(50.f , 25.f));

    sf::Texture texture1;
    sf::Texture texture2;
    sf::Texture texture3;
    sf::Texture texture4;
    sf::Texture texture5;
    sf::Texture texture6;
    sf::Texture texture7;
    sf::Texture texture8;

    texture1.loadFromFile("assets/images/plus.png");
    texture2.loadFromFile("assets/images/minus.png");
    texture3.loadFromFile("assets/images/save_as.png");
    texture4.loadFromFile("assets/images/find.png");
    texture5.loadFromFile("assets/images/select.png");
    texture6.loadFromFile("assets/images/deselect.png");
    texture7.loadFromFile("assets/images/paste.png");
    texture8.loadFromFile("assets/images/copy.png");
 
    button1.setPosition(0 , 0);
    button2.setPosition(50 , 0);
    button3.setPosition(100, 0);
    button4.setPosition(150, 0);
    button5.setPosition(200, 0);
    button6.setPosition(250, 0);
    button7.setPosition(300, 0);
    button8.setPosition(350, 0);

    button1.setFillColor(sf::Color::White);
    button2.setFillColor(sf::Color::White);
    button3.setFillColor(sf::Color::White);
    button4.setFillColor(sf::Color::White);
    button5.setFillColor(sf::Color::White);
    button6.setFillColor(sf::Color::White);
    button7.setFillColor(sf::Color::White);
    button8.setFillColor(sf::Color::White);
    
    button1.setTexture(&texture1);
    button2.setTexture(&texture2);
    button3.setTexture(&texture3);
    button4.setTexture(&texture4);
    button5.setTexture(&texture5);
    button6.setTexture(&texture6);
    button7.setTexture(&texture7);
    button8.setTexture(&texture8);

    sf::Event event;
    sf::Text text;
    sf::Font font;

    font.loadFromFile("assets/fonts/cour.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::Black);

    sf::RectangleShape cursor;
    sf::Color cursorColors[2];

    cursorColors[0] = sf::Color(0, 0, 0, 255);
    cursorColors[1] = sf::Color(0, 0, 0, 0);

    int Timer = 0;
    vector < sf::RectangleShape > boxes;

    for (int fnt = 0 ; fnt < C ; fnt += fontUnit) ///precalculeaza width-urile si height-urile caracterilor in functie de marimea fontului 
    {
        for (int i = 0; i <= 140 ; i++)
        {
            t = (char)i;
            text.setString(t);
            text.setCharacterSize(fnt);
            int sz1 = text.getLocalBounds().width;
            t += (char)i;
            text.setString(t);
            int sz2 = text.getLocalBounds().width - sz1;
            charSize[fnt][i] = max(sz2, sz1);

            int h1 = text.getLocalBounds().height;
            t += "\n";
            t += i;
            text.setString(t);
            int h2 = text.getLocalBounds().height;
            charHeight[fnt][i] = max(h1 , h2 - h1);
        }
    }

    int nr = 0;
    string path , selectedString;
    bool selectFlag = 0;

    while (window.isOpen())
    {
        bool recalculate = 0;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                int key = event.key.code;
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
              
                if (key == 0 && button1.getGlobalBounds().contains(window.mapPixelToCoords(localPosition))) ///font++
                {
                    fontSize += fontUnit;
                    fontSize = min(fontSize, C - 1);
                    recalculate = 1;
                    break;
                }

                if (key == 0 && button2.getGlobalBounds().contains(window.mapPixelToCoords(localPosition))) ///font--
                {
                    fontSize -= fontUnit;
                    fontSize = max(10 , fontSize);
                    recalculate = 1;
                    break;
                }

                if (key == 0 && button3.getGlobalBounds().contains(window.mapPixelToCoords(localPosition))) ///save as
                {
                    path = getPathFromUser();
                    fptr = fopen(path.c_str(), "w");

                    if (fptr == NULL)
                    {
                        throwMessage("Invalid Path!");
                        break;
                    }

                    int currPos = 0;

                    for (auto i : sRaw)
                    {   
                        if (currPos != pos)
                            fprintf(fptr, "%c", i);

                        currPos++;
                    }

                    fclose(fptr);
                    break;
                }

                if (key == 0 && button4.getGlobalBounds().contains(window.mapPixelToCoords(localPosition))) ///find 
                {   
                    cerr << sRaw << '\n';
                    string word = getStringFromUser();
                    cerr << word << ' ' << word.size() << '\n';
                    if (word == "") break;
                    int ind = 0;
                    int pos = 0;

                    boxes.clear();
                    updateTextOnDisplay(sRaw , s);
                    int matches = 0;

                    while ((pos = sRaw.find(word , ind)) < sRaw.size())
                    {
                        matches++;
                        for (int i = pos; i < pos + word.size(); i++)
                        {
                            boxes.push_back(selectCharacterInString(s, dis[i]));
                        }

                        ind = pos + word.size();
                    }

                    throwMessage("There are " + to_string(matches) + " matches!");

                    break;
                }

                if (key == 0 && button5.getGlobalBounds().contains(window.mapPixelToCoords(localPosition))) ///select
                {
                    boxes.clear();
                    selectedString.clear();
                    selectFlag = 1;
                    break;
                }

                if (key == 0 && button6.getGlobalBounds().contains(window.mapPixelToCoords(localPosition))) ///deselect 
                {
                    selectFlag = 0;
                    boxes.clear();
                    break;
                }

                if (key == 0 && button7.getGlobalBounds().contains(window.mapPixelToCoords(localPosition))) ///paste 
                {
                    for (auto ch : selectedString)
                        modify(ch, sRaw);

                    recalculate = 1;
                    break;
                }

                if (key == 0 && button8.getGlobalBounds().contains(window.mapPixelToCoords(localPosition))) ///copy 
                {
                    break;
                }

                if (key == 0) ///click random pe ecran ca sa schimbi unde e cursorul
                {
                    cerr << localPosition.x << ' ' << localPosition.y << '\n';

                    if (selectFlag == 0)
                    {
                        sf::RectangleShape box = selectCharacterVisual(localPosition);

                        updateTextOnDisplay(sRaw, s);
                        int spos = searchForBox(box, s);

                        pos = moveTextBar(pos, rev[spos] + (pos > rev[spos]), sRaw);
                        recalculate = 1;
                    }
                    else
                    {
                        updateTextOnDisplay(sRaw, s);
                        sf::RectangleShape box = selectCharacterVisual(localPosition);
                        int spos = searchForBox(box, s);
                        selectedString += s[spos];
                        boxes.push_back(selectCharacterVisual(localPosition));
                    }
                    break;
                }

                break;
            }

            if (event.type == sf::Event::MouseWheelMoved) ///scroll up and down
            {
                int direction = event.mouseWheel.delta;

                if (direction == +1) offset -= unit , offset = max(0 , offset);
                if (direction == -1) offset += unit;
                
                break;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                // cerr << event.key.code << ' ';
                int key = event.key.code;

                if (key == 36) ///escape
                {
                    if (boxes.size()) boxes.clear();
                    else window.close();

                    break;
                }
                else if (key == 73) ///up arrow
                {
                    int spos = updateTextOnDisplay(sRaw, s);
                    int posPrev = findPrevEndLine(s , spos);

                    if (posPrev != -1)
                    {
                        int characters = spos - posPrev - 1;
                        int ante = findPrevEndLine(s, posPrev - 1);
                        int prvLineCh = posPrev - ante - 1;
                        int newPosBarOnScreen = ante + min(characters, prvLineCh) + 1;
                        pos = moveTextBar(pos, rev[newPosBarOnScreen], sRaw);
                        recalculate = 1;
                    }
                }
                else if (key == 74) ///down arrow
                {
                    int spos = updateTextOnDisplay(sRaw, s);
                    int posPrv = findPrevEndLine(s, spos);
                    int posNxt = findNextEndLine(s, spos);
                  
                    if (posNxt != s.size())
                    {
                        int characters = spos - posPrv - 1;
                        int post = findNextEndLine(s, posNxt + 1);
                        int nxtLineCh = post - posNxt - 1;
                       
                        int newPosBarOnScreen = posNxt + min(characters, nxtLineCh);
                        pos = moveTextBar(pos, rev[newPosBarOnScreen], sRaw);
                        recalculate = 1;
                    }
                }
                else if (key == 71) ///left arrow
                { 
                    if (pos) 
                       swap(sRaw[pos], sRaw[pos - 1]), pos--, recalculate = 1; 
                }
                else if (key == 72)  ///right arrow
                { 
                    if (pos + 1 < sRaw.size()) 
                        swap(sRaw[pos], sRaw[pos + 1]), pos++, recalculate = 1; 
                }

                break;
            }

            if (event.type == sf::Event::KeyReleased)
            {
                int key = event.key.code;
                break;
            }

            if (event.type == sf::Event::TextEntered) ///ce scrie user-ul
            {
                int ch = event.text.unicode;
                cerr << ch << ' ';
                recalculate = 1;
                modify(ch, sRaw);

                break;
            }
        }

        text.setCharacterSize(fontSize);

        if (recalculate || Timer == 0)
        {
            int posOnScreen = updateTextOnDisplay(sRaw, s);
            int width = posOnScreen - findPrevEndLine(s, posOnScreen);
            int height = findNumberOfLines(s , posOnScreen);
            int unitWidth = charSize[fontSize]['|'];
            int unitHeight = charHeight[fontSize]['|'];

            int xTextBar = findRealWidth(s, posOnScreen);
            int yTextBar = unitHeight * (height - 1);

            cursor.setPosition(unitWidth / 2 + xTextBar, yTextBar + textOffset);
            cursor.setSize(sf::Vector2f(unitWidth / 8 , unitHeight));
        }

        Timer++;

        if (Timer == timeUnit)
        {
            swap(cursorColors[0], cursorColors[1]);
            Timer = 0;
        }

        cursor.setFillColor(cursorColors[0]);

        text.setString(s);
        button1.setPosition(0, 0 + offset); ///mentine butoanele cand dai scroll
        button2.setPosition(50, 0 + offset);
        button3.setPosition(100, 0 + offset);
        button4.setPosition(150, 0 + offset);
        button5.setPosition(200, 0 + offset);
        button6.setPosition(250, 0 + offset);
        button7.setPosition(300, 0 + offset);
        button8.setPosition(350, 0 + offset);

        view.reset(sf::FloatRect(0 , 0 + offset , DIM , DIM)); 
        window.setView(view);
        textOffset = charHeight[fontSize]['a'] + 30; ///offset-ul initial pentru a nu intra in butoane textul
        text.setPosition(0, textOffset);

        window.clear(sf::Color::White);
        window.draw(cursor);
        window.draw(text);
        window.draw(button1);
        window.draw(button2);
        window.draw(button3);
        window.draw(button4);
        window.draw(button5);
        window.draw(button6);
        window.draw(button7);
        window.draw(button8);
        for (auto i : boxes) window.draw(i);
        window.display();
    }

    return 0;
}
/// |abcd ab|cd
///abcd| a|bcd