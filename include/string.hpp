#pragma once

#include <bitset>
#include <string>
#include <vector>

#include "globals.hpp"
#include "config.hpp"

namespace String
{

    int getDim(char ch);

    struct Treap
    {
        Treap *L, *R;
        int sumEndline;
        int sumWidth;
        int cnt;
        int priority;
        char ch;
        std::bitset<2> A;

        Treap(char ch = 0, bool cursor = 0);
    };

    extern std::vector<Treap *> freePointers;

    bool getFlagCursor(Treap *&T);

    bool getFlagEndline(Treap *&T);

    int getCh(Treap *&T);

    bool sumCursor(Treap *T);

    int sumEndline(Treap *T);

    int cnt(Treap *T);

    int sumWidth(Treap *T);

    int len(Treap *T);

    void recalculate(Treap *&T);

    void merge(Treap *&T, Treap *L, Treap *R);
    void split(Treap *T, Treap *&L, Treap *&R, int key, int add = 0);

    void print(Treap *T);

    char get(int pos, Treap *&T);

    void del(int pos, Treap *&T);

    void del(Treap *&T);

    void del(int l, int r, Treap *&T);

    void insert(int pos, Treap *&T, Treap *S = new Treap(cursorChar, 1));
    void insert(int pos, Treap *&T, char ch);

    int findCursorPosition(Treap *T, int add = 0);

    int findWidth(Treap *T, int key, int add = 0);

    void construct(Treap *T, std::string &s);

    std::string constructString(Treap *T);
    std::string constructString(int l, int r, Treap *&T);

    int findNumberOfEndlines(int l, int r, Treap *&T);

    int findPrevEndline(Treap *&T, int add = 0);
    int findPrevEndline(int pos, Treap *&T);

    int findNextEndline(Treap *&T, int add = 0);
    int findNextEndline(int pos, Treap *&T);

    int findCurrentWidth(int pos, Treap *&T);
    int findCurrentHeight(Treap *&T);

    int findKthLine(Treap *&T, int k, int lin = 0, int add = 0);
    int findKthLine(int k, Treap *&T);

    int getFirstSeen(Treap *&T, int X, int width = 0, int add = 0);
    int getFirstSeen(int l, int r, int X, Treap *&T);

    int getLastSeen(Treap *&T, int X, int width = 0, int add = 0);
    int getLastSeen(int l, int r, int X, Treap *&T);

    void traverseString(Treap *&T, std::string &txt);
    void traverseString(int l, int r, Treap *&T, std::string &txt);

    void updateWidth(Treap *&T);
    std::string constructRenderedLine(int i, Treap *&T, int Xoffset, int I);
    int findWidth(int l, int r, Treap *&T);
    void heapify(Treap *&T);

    Treap *build(int n, Treap *P);
    Treap *build(int n, const char *data);

    std::string constructRawString(Treap *&T);
    void setW(int pos, int w, Treap *&T);
    void replace(int l, int r, std::string &word, Treap *&T);
    void saveText(FILE *fptr, Treap *&T);
}