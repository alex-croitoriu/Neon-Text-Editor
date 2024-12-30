#include <iostream>
#include <chrono>
#include <random>

#include "string.hpp"
#include <windows.h>

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int String::getDim(char ch)
{
    return charWidth[fontSize][ch];
}

String::Treap::Treap(char ch, bool cursor)
{
    // if (ch == 13) ch = 10;
    this->ch = ch;
    L = R = 0;
    a1 = a2 = cursor;

    //  this-> sumCursor = this-> flagCursor = cursor;
    //  this->sumEndline = this->flagEndline = (ch == 10);
    this->sumEndline = (ch == 10);
    this->sumWidth = getDim(ch) * (1 - cursor);
    cnt = 1;
    priority = rng();
}

std::vector<String::Treap*> String::freePointers;

bool String::getFlagCursor(Treap *&T)
{
    if (T == 0)
        return 0;
    return T->a1;
}

bool String::getFlagEndline(Treap *&T)
{
    if (T == 0)
        return 0;
    return T->ch == 10;
}

int String::getCh(Treap *&T)
{
    if (T == 0)
        return -1;
    return T->ch;
}

bool String::sumCursor(Treap *&T)
{
    if (T == 0)
        return 0;
    return T->a2;
}

int String::sumEndline(Treap *&T)
{
    if (T == 0)
        return 0;
    return T->sumEndline;
}

int String::cnt(Treap *&T)
{
    if (T == 0)
        return 0;
    return T->cnt;
}

int String::sumWidth(Treap *&T)
{
    if (T == 0)
        return 0;
    return T->sumWidth;
}

int String::len(Treap *&T)
{
    if (T == 0)
        return 0;
    return T->cnt;
}

void String::recalculate(Treap *&T)
{
    T->a2 = (sumCursor(T->L) + sumCursor(T->R) + getFlagCursor(T));
    T->sumEndline = sumEndline(T->L) + sumEndline(T->R) + getFlagEndline(T);
    T->sumWidth = sumWidth(T->L) + sumWidth(T->R) + getDim(getCh(T));
    T->cnt = cnt(T->L) + cnt(T->R) + 1;
}

void String::merge(Treap *&T, Treap *L, Treap *R)
{
    if (L == 0 || R == 0)
        return T = (L ? L : R), void();

    if (L->priority > R->priority)
    {
        T = L;
        String::merge(T->R, T->R, R);
    }
    else
    {
        T = R;
        String::merge(T->L, L, T->L);
    }

    String::recalculate(T);
}

void String::split(Treap *T, Treap *&L, Treap *&R, int key, int add)
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

void String::print(Treap *&T)
{
    if (T == 0)
        return;
    print(T->L);
    print(T->R);
}

char String::get(int pos, Treap *&T)
{
    if (pos > len(T) || pos <= 0)
        exit(10);

    Treap *t1 = 0, *t2 = 0, *t3 = 0;
    split(T, t2, t3, pos);
    split(t2, t1, t2, pos - 1);
    char ch = getCh(t2);
    String::merge(T, t1, t2);
    String::merge(T, T, t3);
    return ch;
}

void String::del(int pos, Treap *&T)
{
    Treap *t1 = 0, *t2 = 0, *t3 = 0;
    split(T, t2, t3, pos);
    split(t2, t1, t2, pos - 1);
    if (t2)
        freePointers.push_back(t2);
    merge(T, t1, t3);
}

void String::del(Treap *&T)
{
    if (T == 0)
        return;
    del(T->L);
    del(T->R);
    freePointers.push_back(T);
}

void String::del(int l, int r, Treap *&T)
{
    Treap *t1 = 0, *t2 = 0, *t3 = 0;

    split(T, t2, t3, r);
    split(t2, t1, t2, l - 1);

    del(t2);

    merge(T, t1, t3);
}

void String::insert(int pos, Treap *&T, Treap *S)
{
    Treap *t1 = 0, *t2 = 0;
    split(T, t1, t2, pos - 1);
    merge(T, t1, S);
    merge(T, T, t2);
}

void String::insert(int pos, Treap *&T, char ch)
{
    Treap *c;

    if (freePointers.size())
    {
        c = freePointers.back();
        freePointers.pop_back();
        *c = Treap(ch);
        insert(pos, T, c);
    }
    else
    {
        Treap *P = new Treap[bucketSize];
        for (int i = 0; i < bucketSize; i++)
            freePointers.push_back(&P[i]);

        insert(pos, T, ch);
    }
}

int String::findCursorPosition(Treap *&T, int add)
{
    int curr = add + cnt(T->L) + 1;

    if (getFlagCursor(T) == 1)
        return curr;
    else if (sumCursor(T->L) == 1)
        return findCursorPosition(T->L, add);
    else
        return findCursorPosition(T->R, curr);
}

int String::findWidth(Treap *&T, int key, int add)
{
    if (T == 0)
        return 0;

    int currKey = add + 1 + cnt(T->L);

    if (currKey <= key)
        return findWidth(T->R, key, currKey) + sumWidth(T->L) + getDim(getCh(T));
    else
        return findWidth(T->L, key, add);
}

void String::construct(Treap *&T, std::string &s)
{
    if (T == 0)
        return;
    construct(T->L, s);
    s += getCh(T);
    construct(T->R, s);
}

std::string String::constructString(Treap *&T)
{
    std::string S;
    construct(T, S);
    return S;
}

std::string String::constructString(int l, int r, Treap *&T)
{
    Treap *t1 = 0, *t2 = 0, *t3 = 0;

    split(T, t2, t3, r);
    split(t2, t1, t2, l - 1);

    std::string s = constructString(t2);

    merge(T, t1, t2);
    merge(T, T, t3);

    return s;
}

int String::findNumberOfEndlines(int l, int r, Treap *&T)
{
    if (l > r)
        return 0;
    Treap *t1 = 0, *t2 = 0, *t3 = 0;
    split(T, t2, t3, r);
    split(t2, t1, t2, l - 1);
    int ans = sumEndline(t2);
    merge(T, t1, t2);
    merge(T, T, t3);
    return ans;
}

int String::findPrevEndline(Treap *&T, int add)
{
    if (T == 0)
        return 0;

    int currPos = add + 1 + cnt(T->L);

    if (sumEndline(T->R))
        return findPrevEndline(T->R, currPos);
    else if (getCh(T) == 10)
        return currPos;
    else
        return findPrevEndline(T->L, add);
}

int String::findPrevEndline(int pos, Treap *&T)
{
    Treap *t1 = 0, *t2 = 0;
    split(T, t1, t2, pos - 1);
    int ans = findPrevEndline(t1);
    merge(T, t1, t2);
    return ans;
}

int String::findNextEndline(Treap *&T, int add)
{
    if (T == 0)
        return -1;

    int currPos = add + 1 + cnt(T->L);

    if (sumEndline(T->L))
        return findNextEndline(T->L, add);
    else if (getCh(T) == 10)
        return currPos;
    else
        return findNextEndline(T->R, currPos);
}

int String::findNextEndline(int pos, Treap *&T)
{
    Treap *t1 = 0, *t2 = 0;
    split(T, t1, t2, pos);
    int ans = findNextEndline(t2);
    merge(T, t1, t2);
    if (ans == -1)
        ans = len(T) + 1;
    else
        ans += pos;
    return ans;
}

int String::findCurrentWidth(int pos, Treap *&T)
{
    int p = findPrevEndline(pos, T);
    Treap *t1, *t2, *t3;
    split(T, t2, t3, pos);
    split(t2, t1, t2, p);
    int ans = sumWidth(t2);
    merge(T, t1, t2);
    merge(T, T, t3);
    return ans;
}

int String::findCurrentHeight(Treap *&T)
{
    int lines = findNumberOfEndlines(1, findCursorPosition(T), T) + 1;
    int globalHeight = lines * lineHeight;
    return globalHeight;
}

int String::findKthLine(Treap *&T, int k, int lin, int add)
{
    int currPos = 1 + add + cnt(T->L);
    int currLine = lin + sumEndline(T->L) + (getCh(T) == 10);

    if (currLine == k && getCh(T) == 10)
        return currPos;
    else if (currLine >= k)
        return findKthLine(T->L, k, lin, add);
    else
        return findKthLine(T->R, k, currLine, currPos);
}

int String::findKthLine(int k, Treap *&T)
{
    if (k == 1)
        return 1;
    int ans = findKthLine(T, k - 1);
    return ans + 1;
}

int String::getFirstSeen(Treap *&T, int X, int width, int add)
{
    if (T == 0)
        return INT_MAX;

    int currPos = add + 1 + cnt(T->L);
    int currWidth = width + getDim(getCh(T)) + sumWidth(T->L);

    if (currWidth >= X)
        return std::min(currPos, getFirstSeen(T->L, X, width, add));
    else
        return getFirstSeen(T->R, X, currWidth, currPos);
}

int String::getFirstSeen(int l, int r, int X, Treap *&T)
{
    if (l > r)
        return -1;
    Treap *t1 = 0, *t2 = 0, *t3 = 0;
    split(T, t2, t3, r);
    split(t2, t1, t2, l - 1);

    int ans = -1;
    if (sumWidth(t2) >= X)
        ans = getFirstSeen(t2, X) + l - 1;

    merge(T, t1, t2);
    merge(T, T, t3);

    return ans;
}

int String::getLastSeen(Treap *&T, int X, int width, int add)
{
    if (T == 0)
        return -1;

    int currPos = add + 1 + cnt(T->L);
    int currWidth = width + getDim(getCh(T)) + sumWidth(T->L);

    if (currWidth <= X)
        return std::max(currPos, getLastSeen(T->R, X, currWidth, currPos));
    else
        return getLastSeen(T->L, X, width, add);
}

int String::getLastSeen(int l, int r, int X, Treap *&T)
{
    Treap *t1 = 0, *t2 = 0, *t3 = 0;
    split(T, t2, t3, r);
    split(t2, t1, t2, l - 1);

    int ans = getLastSeen(t2, X);
    if (ans != -1)
        ans += l - 1;

    merge(T, t1, t2);
    merge(T, T, t3);

    return ans;
}

void String::traverseString(Treap *&T, std::string &txt)
{
    if (T == 0)
        return;
    traverseString(T->L, txt);
    txt += getCh(T);
    traverseString(T->R, txt);
}

void String::traverseString(int l, int r, Treap *&T, std::string &txt)
{
    Treap *t1 = 0, *t2 = 0, *t3 = 0;
    split(T, t2, t3, r);
    split(t2, t1, t2, l - 1);

    traverseString(t2, txt);

    merge(T, t1, t2);
    merge(T, T, t3);
}

void String::updateWidth(Treap *&T)
{
    if (T == 0)
        return;

    updateWidth(T->L);
    updateWidth(T->R);
    recalculate(T);
}

std::string String::constructRenderedLine(int i, Treap *&T, int Xoffset, int I)
{
    std::string txt = "";
    int p1 = String::findKthLine(i, T); 
    segmOnScreen[I] = {-1, -1};
    if (String::len(T) + 1 == p1 || String::get(p1, T) == 10)
        return txt;

    int p2 = String::findNextEndline(p1, T) - 1;

    int t1 = String::getFirstSeen(p1, p2, Xoffset, T);
    int t2 = String::getLastSeen(p1, p2, Xoffset + windowWidth - marginLeft, T);

    segmOnScreen[I] = {t1, t2};

    if (t1 == -1 || t2 == -1)
        return segmOnScreen[I] = {-1, -1}, txt;

    String::traverseString(t1, t2, T, txt);
    return txt;
}

int String::findWidth(int l, int r, Treap *&T)
{
    if (l == -1)
        return 0;

    if (l > r)
        return 0;
    Treap *t1 = 0, *t2 = 0, *t3 = 0;
    split(T, t2, t3, r);
    split(t2, t1, t2, l - 1);

    int ans = sumWidth(t2);

    merge(T, t1, t2);
    merge(T, T, t3);

    return ans;
}

void String::heapify(Treap *&T)
{
    if (T == 0)
        return;

    Treap *mx = T;

    if (T->L && T->L->priority > mx->priority)
        mx = T->L;

    if (T->R && T->R->priority > mx->priority)
        mx = T->R;

    if (mx != T)
    {
        std::swap(T->priority, mx->priority);
        heapify(mx);
    }
}

String::Treap* String::build(int n, Treap *P)
{
    if (n == 0)
        return NULL;

    int mid = (n - 1) / 2;
    Treap *T = &P[mid];
    T->L = build(mid, P);
    T->R = build(n - (mid + 1), P + mid + 1);
    heapify(T);
    recalculate(T);
    return T;
}

String::Treap* String::build(int n, const char *data)
{
    Treap *ptr = new Treap[1<<((int)log2(n)+1)];

    for (int i = 0; i < n; i++)
        ptr[i] = Treap(data[i]);

    return build(n, ptr);
}

std::string String::constructRawString(Treap *&T)
{
    int posCursor = findCursorPosition(T);
    Treap *t1 = 0, *t2 = 0, *t3 = 0;
    split(T, t2, t3, posCursor);
    split(t2, t1, t2, posCursor - 1);
    merge(T, t1, t3);

    std::string raw = constructString(T);

    insert(len(T) + 1, T);

    return raw;
}

void String::replace(int l, int r, std::string &word, Treap *&T)
{
    Treap *t1 = 0, *t2 = 0, *t3 = 0;

    split(T, t2, t3, r);
    split(t2, t1, t2, l - 1);

    del(t2);

    t2 = build((int)word.size(), word.c_str());

    merge(T, t1, t2);
    merge(T, T, t3);
}

void String::saveText(FILE *fptr, Treap *&T)
{
    if (T == 0)
        return;
    saveText(fptr, T->L);
    if (getFlagCursor(T) == 0)
    {
        char ch = getCh(T);
        fprintf(fptr, "%c", ch);
    }
    saveText(fptr, T->R);
}

void String::copyTextToClipboard(const char* text) {
    // Open the clipboard
    if (!OpenClipboard(NULL)) {
        std::cerr << "Failed to open clipboard!" << std::endl;
        return;
    }

    // Empty the clipboard
    EmptyClipboard();

    // Calculate the size of the memory to allocate for the text
    size_t len = strlen(text) + 1;  // +1 for the null terminator
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);

    if (!hMem) {
        std::cerr << "Failed to allocate memory!" << std::endl;
        CloseClipboard();
        return;
    }

    // Lock the allocated memory and copy the text to it
    memcpy(GlobalLock(hMem), text, len);
    GlobalUnlock(hMem);

    // Set the clipboard data to the allocated memory (CF_TEXT is the format for text data)
    SetClipboardData(CF_TEXT, hMem);

    // Close the clipboard
    CloseClipboard();

    std::cout << "Text copied to clipboard: " << text << std::endl;
}

// Function to retrieve text from the clipboard
std::string String::getTextFromClipboard() {
    // Open the clipboard
    if (!OpenClipboard(NULL)) {
        std::cerr << "Failed to open clipboard!" << std::endl;
        return "";
    }

    // Get the clipboard data in the CF_TEXT format
    HANDLE hData = GetClipboardData(CF_TEXT);
    if (hData == NULL) {
        std::cerr << "No text in clipboard or failed to retrieve data!" << std::endl;
        CloseClipboard();
        return "";
    }

    // Lock the clipboard data to get a pointer to the text
    char* pszText = static_cast<char*>(GlobalLock(hData));
    if (pszText == NULL) {
        std::cerr << "Failed to lock clipboard data!" << std::endl;
        CloseClipboard();
        return "";
    }

    // Output the clipboard text
    int len = strlen(pszText);
    std::string clipboardText;

    for (int i = 0; i < len; i++)
    {
        clipboardText += pszText[i];
    }

    std::cout << "Clipboard contains: " << pszText << std::endl;

    // Unlock the clipboard data and close the clipboard
    GlobalUnlock(hData);
    CloseClipboard();
    return clipboardText;
}
