#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <chrono>
#include <random>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int C = 400;
const int fontUnit = 30;
const int scrollUnit = 10;

int charWidth[C][C], charHeight[C][C];
int fontSize = fontUnit;

namespace String
{
    void precalculateCharDim()
    {
        sf::Text text;
        sf::Font font;

        font.loadFromFile("cour.ttf");
        text.setFont(font);

        for (int fnt = fontUnit ; fnt < 2 * fontUnit; fnt += fontUnit) ///precalculeaza width-urile si height-urile caracterilor in functie de marimea fontului 
        {
            text.setCharacterSize(fnt);
            text.setString("Êg");
            int H = text.getLocalBounds().height + 10;
            int mx = -1, ch = 0;

            for (int i = 0; i <= 255; i++)
            {
                string t;

                for (int it = 1; it <= 30; it++)
                    t += (char)i;

                text.setString(t);
                charWidth[fnt][i] = ceil(text.getLocalBounds().width / 30.0);

                if (mx < charWidth[fnt][i] && i != 9)
                {
                    mx = charWidth[fnt][i];
                    ch = i;
                }

                charHeight[fnt][i] = H;
            }

           // cerr << mx << ' ' << ch << '\n';
        }
    }
    
    int getDim(char ch)
    {
        return charWidth[fontSize][ch];
    }

    struct Treap
    {
        char ch;
        Treap *L , *R;
        bool flagCursor = 0;
        bool flagEndline = 0;
        int width;
        int sumCursor;
        int sumEndline;
        int sumWidth;
        int cnt;
        int priority;

        Treap(char ch , bool flagCursor = 0)
        {
            this->ch = ch;
            L = R = 0;
            this->sumCursor = this->flagCursor = flagCursor;
            this->sumEndline = this->flagEndline = (ch == 10);
            cnt = 1;
            width = getDim(ch);
            priority = rng();
        }
    };

    int sumCursor(Treap* T)
    {
        if (T == 0) return 0;
        return T->sumCursor;
    }

    int sumEndline(Treap* T)
    {
        if (T == 0) return 0;
        return T->sumEndline;
    }

    int cnt(Treap* T)
    {
        if (T == 0) return 0;
        return T->cnt;
    }

    int sumWidth(Treap* T)
    {
        if (T == 0) return 0;
        return T->sumWidth;
    }

    int len(Treap* T)
    {
        if (T == 0) return 0;
        return T->cnt;
    }

    void recalculate(Treap*& T)
    {
        if (T == 0) cerr << "flag!!!" , exit(0);
        T->sumCursor = sumCursor(T->L) + sumCursor(T->R) + T->flagCursor;
        T->sumEndline= sumEndline(T->L) + sumEndline(T->R) + T->flagEndline;
        T->sumWidth = sumWidth(T->L) + sumWidth(T->R) + T->width;
        T->cnt = cnt(T->L) + cnt(T->R) + 1;
    }

    void merge(Treap*& T, Treap* L, Treap* R)
    {
        if (L == 0 || R == 0)
            return T = (L ? L : R), void();

        if (L->priority > R->priority)
        {
            T = L;
            merge(T->R, T->R, R);
        }
        else
        {
            T = R;
            merge(T->L, L, T->L);
        }

        recalculate(T);
    }

    void split(Treap* T, Treap*& L, Treap*& R , int key , int add = 0)
    {
        if (T == 0)
            return L = R = 0, void();

        int currKey = add + cnt(T->L) + 1;

        if (currKey <= key)
        {
            L = T;
            split(T->R, T->R, R, key, currKey);
        }
        else
        {
            R = T;
            split(T->L, L, T->L, key, add);
        }

        recalculate(T);
    }

    void print(Treap* T)
    {
        if (T == 0) return;
        print(T->L);
        cerr << T->ch << ' ';
        print(T->R);
    }

    char get(int pos , Treap *&T)
    {
        if (pos > len(T) || pos <= 0)
            cerr << "flag";

        Treap* t1 = 0 , *t2 = 0 , *t3 = 0;
        split(T,t2, t3, pos);
        split(t2, t1, t2, pos - 1);
        char ch = t2->ch;
        merge(T, t1, t2);
        merge(T, T, t3);
        return ch;
    }

    void del(int pos, Treap *&T)
    {
        Treap* t1 = 0, * t2 = 0, * t3 = 0;
        split(T, t2, t3, pos);
        split(t2, t1, t2, pos - 1);
        if (t2) delete t2;
        merge(T, t1, t3);
    }

    void insert(int pos, Treap* &T, Treap* S = new Treap('|' , 1))
    {
        Treap* t1 = 0, * t2 = 0;
        split(T, t1, t2, pos - 1);
        merge(T, t1, S);
        merge(T, T, t2);
    }

    void insert(int pos, Treap* &T, char ch)
    {
        Treap* c = new Treap(ch);
        insert(pos, T, c);
    }

    int findCursorPosition(Treap* T , int add = 0)
    {
        int curr = add + cnt(T->L) + 1;

        if (T->flagCursor == 1)
            return curr;
        else if (sumCursor(T->L) == 1)
            return findCursorPosition(T->L, add);
        else return findCursorPosition(T->R, curr);
    }

    int findWidth(Treap* T, int key, int add = 0)
    {
        if (T == 0) 
            return 0;

        int currKey = add + 1 + cnt(T->L);

        if (currKey <= key)
            return findWidth(T->R, key, currKey) + sumWidth(T->L) + T->width;
        else return findWidth(T->L, key, add);
    }

    void construct(Treap *T , string& s)
    {
        if (T == 0) return;
        construct(T->L, s);
        s += T->ch;
        construct(T->R, s);
    }

    string constructString(Treap* T)
    {
        string S;
        construct(T, S);
        return S;
    }

    int findNumberOfEndlines(int l, int r, Treap*& T)
    {
        if (l > r) return 0;
        Treap* t1 = 0, * t2 = 0, * t3 = 0;
        split(T, t2, t3, r);
        split(t2, t1, t2, l - 1);
        int ans = sumEndline(t2);
        merge(T, t1, t2);
        merge(T, T, t3);
        return ans;
    }

    int findPrevEndline(int pos, Treap*& T)
    {
        int l = 1, r = pos - 1, ans = 0, mid = 0;
        int nr = findNumberOfEndlines(1, pos - 1, T);
       // cerr << nr << '\n';

        while (l <= r)
        {
            mid = (l + r) / 2;

            if (findNumberOfEndlines(1, mid, T) >= nr)
                ans = mid, r = mid - 1;
            else l = mid + 1;
        }

        if (ans && get(ans , T) != 10) ans = 0;
        return ans;
    }

    int findNextEndline(int pos, Treap*& T)
    {
        int n = len(T);
        int l = pos + 1, r = n;
        int ans = n + 1 , mid = 0;
        int nr = findNumberOfEndlines(1, pos, T) + 1;

        while (l <= r)
        {
            mid = (l + r) / 2;

            if (findNumberOfEndlines(1, mid, T) >= nr)
                ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        

        if (ans != n + 1 && get(ans, T) != 10) ans = n + 1;
        return ans;
    }

    int findCurrentWidth(int pos, Treap*& T)
    {
        int p = findPrevEndline(pos, T);
        Treap* t1, * t2, * t3;
        split(T, t2, t3, pos);
        split(t2, t1, t2, p);
        int ans = sumWidth(t2);
        merge(T, t1, t2);
        merge(T, T, t3);
        return ans;
    }

    int findCurrentHeight(Treap *&T)
    {
        int lines = findNumberOfEndlines(1, findCursorPosition(T), T) + 1;
       // cerr << lines << '\n';
        int globalHeight = lines * charHeight[fontSize][106];
        return globalHeight;
    }

    int findKthLine(int k, Treap*& T)
    {
        if (k == 1) return 1;
        int l = 1, r = len(T), mid = 0, ans = 0;

        while (l <= r)
        {
            mid = (l + r) / 2;

            if (findNumberOfEndlines(1, mid, T) >= k - 1)
                ans = mid, r = mid - 1;
            else l = mid + 1;
        }

        return ans + 1;
    }
    
    int getFirstSeen(int l, int r, int X , Treap *&T)
    {
        Treap* t1 = 0 , * t2 = 0, * t3 = 0;
        split(T, t2, t3, r);
        split(t2, t1, t2, l - 1);

        int L = 1, R = r - l + 1, mid = 0, ans = -1;

        while (L <= R)
        {
            mid = (L + R) / 2;

            if (findWidth(t2, mid) >= X)
                ans = mid, R = mid - 1;
            else L = mid + 1;
        }

        merge(T, t1, t2);
        merge(T, T, t3);

        if (ans != -1) ans += l - 1;
        return ans;
    }

    int getLastSeen(int l, int r, int X, Treap*& T)
    {
        Treap* t1 = 0, * t2 = 0, * t3 = 0;
        split(T, t2, t3, r);
        split(t2, t1, t2, l - 1);

        int L = 1, R = r - l + 1, mid = 0, ans = -1;

        while (L <= R)
        {
            mid = (L + R) / 2;

            if (findWidth(t2, mid) <= X)
                ans = mid, L = mid + 1;
            else R = mid - 1;
        }

        merge(T, t1, t2);
        merge(T, T, t3);

        if (ans != -1) ans += l - 1;
        return ans;
    }
}

const int HEIGHT = 1000;
const int WIDTH = 1000;

void updateViewX(String::Treap*& S, int& Xoffset , int scrollUnitX)
{
    int currLineWidth = String::findCurrentWidth(String::findCursorPosition(S), S);
    bool modif = 0;

    while (currLineWidth <= Xoffset)
        Xoffset -= scrollUnitX, modif = 1;

    if (modif) Xoffset -= scrollUnitX;
    Xoffset = max(0, Xoffset);

    while (currLineWidth > Xoffset + WIDTH)
        Xoffset += scrollUnitX;
}

void updateViewY(String::Treap*& S, int& Yoffset , int scrollUnitY)
{
    int globalHeight = String::findCurrentHeight(S);
    bool modif = 0;

    while (globalHeight < Yoffset)
        Yoffset -= scrollUnitY, modif = 1;

   // if (modif) Yoffset -= scrollUnitY;
    Yoffset = max(0, Yoffset);

    while (globalHeight > Yoffset + HEIGHT)
        Yoffset += scrollUnitY;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(HEIGHT, WIDTH), "Text Editor");
    sf::View view;
    sf::Image mainIcon;

    mainIcon.loadFromFile("main icon.png");
    window.setIcon(mainIcon.getSize().x, mainIcon.getSize().y, mainIcon.getPixelsPtr());

    sf::Event event;
    sf::Text text;
    sf::Font font;

    font.loadFromFile("cour.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(fontSize);

    String::precalculateCharDim();
    String::Treap* S = new String::Treap('|', 1); ///string doar cu pointer-ul de text

    int Yoffset = 0, Xoffset = 0;
    int scrollUnitX = charWidth[fontSize][0], scrollUnitY = charHeight[fontSize]['a'];

    string txt;
    bool firstExec = 1;

    while (window.isOpen())
    {
        bool flag = 0;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                 cerr << event.key.code << ' ';
                int key = event.key.code;

                if (key == 36) ///escape
                {
                    window.close();

                    break;
                }
                else if (key == 73) ///up arrow
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
                    }
                }
                else if (key == 74) ///down arrow
                {
                    int posCursor = String::findCursorPosition(S);
                    int p1 = String::findNextEndline(posCursor, S);
                    int p0 = String::findPrevEndline(posCursor, S);

                    if (p1 <= len(S))
                    {
                        int p2 = String::findNextEndline(p1, S);
                        int chCurr = posCursor - p0 - 1;
                        int chNext = p2 - p1 - 1;
                        // cerr << chCurr << ' ' << chNext << '\n';
                        String::del(posCursor, S);
                        String::insert(p1 + min(chCurr, chNext) + 1 - 1, S);
                    }
                }
                else if (key == 71) ///left arrow
                {
                    int posCursor = String::findCursorPosition(S);

                    if (posCursor > 1)
                    {
                        String::del(posCursor, S);
                        String::insert(posCursor - 1, S);
                    }
                }
                else if (key == 72)  ///right arrow
                {
                    int posCursor = String::findCursorPosition(S);

                    if (posCursor < String::len(S))
                    {
                        String::del(posCursor, S);
                        String::insert(posCursor + 1, S);
                    }
                }
                else if (key == 58)
                {
                    /*
                    FILE* fptr = fopen("text.txt", "r");
                    char ch;
                    int nr = 0;

                    while ((ch = fgetc(fptr)) != EOF)
                    {
                        int posCursor = String::findCursorPosition(S);
                        String::insert(posCursor, S, ch);
                        nr++;
                       // cerr << ch << '\n';
                    }

                    cerr << "done" << ' ' << nr << '\n';
                    //return 0;
                    */
                }
                else break;

                updateViewX(S, Xoffset , scrollUnitX);
                updateViewY(S, Yoffset , scrollUnitY);

                flag = 1;

                break;
            }

            if (event.type == sf::Event::TextEntered) ///ce scrie user-ul
            {
                int ch = event.text.unicode;

                if (ch == 27)
                    break;

                int posCursor = String::findCursorPosition(S);

                if (ch == 8)
                {
                    if (posCursor > 1)
                        String::del(posCursor - 1, S);
                }
                else
                {
                    if (ch == 13) ch = 10;
                    String::insert(posCursor, S, ch);
                }
                
                updateViewX(S, Xoffset, scrollUnitX);
                updateViewY(S, Yoffset, scrollUnitY);

                flag = 1;

                break;
            }
        }
       
        window.clear(sf::Color::White);
       
        if (flag || firstExec)
        {
            firstExec = 0;
            txt.clear();
            int l1 = min(String::findNumberOfEndlines(1, String::len(S), S) + 1 , Yoffset / scrollUnitY + 1);
            int l2 = min(String::findNumberOfEndlines(1 , String::len(S) , S) + 1 , (Yoffset + HEIGHT) / scrollUnitY);
            
            for (int i = l1; i <= l2 && l1 >= Yoffset / scrollUnitY + 1 && l2 <= (Yoffset + HEIGHT) / scrollUnitY ; i++)
            {
                int p1 = String::findKthLine(i, S);

                if (String::len(S) + 1 == p1 || String::get(p1, S) == 10)
                {
                    txt += '\n';
                    continue;
                }

                int p2 = String::findNextEndline(p1, S) - 1;

                int t1 = String::getFirstSeen(p1, p2, Xoffset, S);
                int t2 = String::getLastSeen(p1, p2, Xoffset + WIDTH, S);
               
                if (flag) cerr << t1 << ' ' << t2 << '\n';

                if (t1 == -1 || t2 == -1) 
                    txt += '\n';
                else
                {
                    for (int j = t1; j <= t2; j++)
                    {
                        txt += String::get(j, S);
                    }

                    txt += '\n';
                }
            }
            
            text.setString(txt);
        }
        
        window.draw(text);
        window.display();
    }

    return 0;
}

