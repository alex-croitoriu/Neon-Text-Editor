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

void modify(char ch , string &s)
{
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

int main()
{
    FILE* fptr = fopen("text.txt", "w");

    const int DIM = 1000;
    const int unit = 100;
    const int fontUnit = 10;
    
    string s, sRaw = "|", t;
    
    int fontSize = 50;
    int offset = 0;
    int textOffset = 15;

    sf::RenderWindow window(sf::VideoMode(DIM , DIM), "Text Editor");
    sf::View view;

    sf::RectangleShape button1(sf::Vector2f(50.f , 25.f));
    sf::RectangleShape button2(sf::Vector2f(50.f , 25.f));
    sf::RectangleShape button3(sf::Vector2f(50.f , 25.f));

    button1.setPosition(0 , 0);
    button2.setPosition(50 , 0);
    button3.setPosition(100, 0);

    button1.setFillColor(sf::Color::Blue);
    button2.setFillColor(sf::Color::Green);
    button3.setFillColor(sf::Color::Magenta);
    
    sf::Event event;
    sf::Text text;
    sf::Font font;

    font.loadFromFile("arial.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::Red);

    for (int fnt = fontSize ; fnt < C ; fnt += fontUnit)
    {
        for (int i = 0; i <= 255; i++)
        {
            t = (char)i;
            text.setString(t);
            text.setCharacterSize(fnt);
            int sz1 = text.getLocalBounds().width;
            t += (char)i;
            text.setString(t);
            int sz2 = text.getLocalBounds().width - sz1;
            charSize[fnt][i] = max(sz2, sz1);
            charHeight[fnt][i] = text.getLocalBounds().height;
        }
    }

    int nr = 0;

    while (window.isOpen())
    {
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
                }

                if (key == 0 && button2.getGlobalBounds().contains(window.mapPixelToCoords(localPosition))) ///font--
                {
                    fontSize -= fontUnit;
                }

                if (key == 0 && button3.getGlobalBounds().contains(window.mapPixelToCoords(localPosition))) ///save
                {
                    fptr = fopen("text.txt", "w");

                    for (auto i : sRaw)
                        if(i != '|')
                             fprintf(fptr, "%c", i);

                    fclose(fptr);
                }
            }

            if (event.type == sf::Event::MouseWheelMoved)
            {
                int direction = event.mouseWheel.delta;

                if (direction == +1) offset -= unit;
                if (direction == -1) offset += unit;
                
                break;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                // cerr << event.key.code << ' ';
                int key = event.key.code;

                if (key == 74) offset += unit;
                else if (key == 73) offset -= unit;
                else if (key == 71) if (pos) swap(sRaw[pos], sRaw[pos - 1]), pos--;
                else if (key == 72) if (pos + 1 < sRaw.size()) swap(sRaw[pos], sRaw[pos + 1]), pos++;

                break;
            }

            if (event.type == sf::Event::KeyReleased)
            {
                int key = event.key.code;
                break;
            }

            if (event.type == sf::Event::TextEntered)
            {
                int ch = event.text.unicode;
                modify(ch, sRaw);

                break;
            }
        }

        text.setCharacterSize(fontSize);
        int W = text.getLocalBounds().width;

        //if (W >= DIM || minus == 1 && ctrl == 1)
        {
            s.clear();
            int currWidth = 0;

            for (auto i : sRaw)
            {
                s += i;
                currWidth += charSize[fontSize][i];

                if (currWidth >= DIM)
                {
                    s.back() = 10;
                    s += i;
                    currWidth = charSize[fontSize][i];
                }
            }

            text.setString(s);
        }


        view.reset(sf::FloatRect(0 , 0 + offset , DIM , DIM));
        window.setView(view);
        textOffset = charHeight[fontSize]['a'] + 30;
        text.setPosition(0, textOffset);

        window.clear();
        window.draw(text);
        window.draw(button1);
        window.draw(button2);
        window.draw(button3);
        window.display();
    }

    return 0;
}