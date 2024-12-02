#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

using namespace std;

int pos;

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
    sf::RenderWindow window(sf::VideoMode(DIM , DIM), "Text Editor");
    sf::View view;

    string s , sRaw = "|", t;
    int fontSize = 50;
    bool ctrl = 0;
    bool plus = 0;
    bool minus = 0;
    bool sKey = 0;
    int offset = 0;
    ///1 - 0 26 - 35
    ///a - z 0 - 25
    /// enter - 36
    /// caps - 76
    /// shift - 128
    ///ctrl - 37
    ///< - 71 > - 72
   // return 0;
    sf::Text text;
    sf::Font font;
    // font.loadFromFile("arial.ttf");
    // text.setFont(font);
    // text.setFillColor(sf::Color::Red);
    sf::Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close(); 

            if (event.type == sf::Event::KeyPressed)
            {
                cerr << event.key.code << ' ';
                if (event.key.code == 37) ctrl = 1;
                if (event.key.code == 55) plus = 1;
                if (event.key.code == 56) minus = 1;
                if (event.key.code == 74) offset += unit;
                if (event.key.code == 73) offset -= unit;
                if (event.key.code == 18) sKey = 1;
                if (event.key.code == 71)
                {
                    if (pos) swap(sRaw[pos], sRaw[pos - 1]) , pos--;
                }
                if (event.key.code == 72)
                {
                    if(pos + 1 < sRaw.size()) swap(sRaw[pos] , sRaw[pos + 1]) , pos++;
                }

                break;
            }

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == 37) ctrl = 0;
                if (event.key.code == 55) plus = 0;
                if (event.key.code == 56) minus = 0;
                if (event.key.code == 18) sKey = 0;
                break;
            }

            if (event.type == sf::Event::TextEntered)
            {
                if (ctrl == 1) break;
                int ch = event.text.unicode;

              //  std::cout << ch << '\n';
              //  modify(ch , s);
                modify(ch , sRaw);
                break;
            }
        }

        fontSize += (plus & ctrl) * 1; ///font++
        fontSize -= (minus & ctrl) * 1;///font--
        fontSize = max(1, fontSize);
        text.setString(s);
        text.setCharacterSize(fontSize);

        if (ctrl == 1 && sKey == 1) ///save
        {
            fptr = fopen("text.txt", "w");

            for (auto i : sRaw)
                fprintf(fptr, "%c", i);

            fclose(fptr);
        }

        int W = text.getLocalBounds().width;

        //if (W >= DIM || minus == 1 && ctrl == 1)
        {
            s.clear();
            t.clear();

            for (auto i : sRaw)
            {
                s += i;
                t += i;
                text.setString(t);
                if (text.getLocalBounds().width >= DIM)
                {
                    s.back() = 10;
                    s += i;
                    t.clear();
                    t += i;
                }
            }

            text.setString(s);
        }


        view.reset(sf::FloatRect(0 , 0 + offset , DIM , DIM));
        window.setView(view);

        window.clear();
        window.draw(text);
        window.display();
    }

    return 0;
}