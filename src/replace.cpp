#include <iostream>

#include "replace.hpp"
#include "bit.hpp"
#include "globals.hpp"

void Replace::KMP(std::string &s, std::string &word, std::vector<int> &positions, bool &wholeWord)
{
    std::vector<int> PI(word.size());
    std::vector<int> pi(s.size());
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
}

bool Replace::isApOnScreen(int ap, int sz)
{
    for (int i = 0; i < sizeRLines; i++)
    {
        int l = segmOnScreen[i].first;
        int r = segmOnScreen[i].second;

        if (l == -1)
            continue;

        if (l <= ap && ap <= r && ap + sz - 1 <= r)
            return 1;
    }

    return 0;
}

bool Replace::isValid(char ch)
{
    return ch != 10 && ch != ' ';
}

void Replace::delAp(int idx, std::vector<int> &prv, std::vector<int> &nxt, std::vector<int> &bit, std::vector<int> &gone, std::set<int> &notRemoved, int vl)
{
    Bit::upd(idx, vl, bit);

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

int Replace::findLastReplace(int idx, std::vector<int> &bit)
{
    int l = 0, r = idx - 1, ans = -1, mid = 0;
    int value = Bit::get(idx, bit);

    if (value == 0)
        return -1;

    while (l <= r)
    {
        mid = (l + r) / 2;

        if (Bit::get(mid, bit) >= value)
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }

    return ans;
}

int Replace::findNextReplace(int idx, std::vector<int> &bit)
{
    int l = idx + 1, r = bit.size() - 1, mid = 0, ans = -1;
    int value = Bit::get(idx, bit) + 1;

    while (l <= r)
    {
        mid = (l + r) / 2;

        if (Bit::get(mid, bit) >= value)
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }

    return ans;
}

bool Replace::canReplace(int idx, std::vector<int> &bit, std::vector<int> &positions, std::vector<int> &gone, std::string &rword, std::string &word)
{
    if (gone[idx])
        return 0;

    int p1 = findLastReplace(idx, bit);
    int p2 = findNextReplace(idx, bit);

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

int Replace::findNextValidAppearance(int idx, std::vector<int> &bit, std::vector<int> &positions, std::vector<int> &gone, std::string &rword, std::string &word, std::vector<int> &prv, std::vector<int> &nxt, std::set<int> &notRemoved)
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

int Replace::findPrevValidAppearance(int idx, std::vector<int> &bit, std::vector<int> &positions, std::vector<int> &gone, std::string &rword, std::string &word, std::vector<int> &prv, std::vector<int> &nxt, std::set<int> &notRemoved)
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

int Replace::findRealPosition(int idx, std::vector<int> &positions, std::vector<int> &bit, std::string &word, std::string &rword)
{
    int sub = Bit::get(idx, bit);
    return positions[idx] - sub * word.size() + sub * rword.size();
}

int Replace::traceFirstApToRender(int idx, std::vector<int> &positions, std::vector<int> &bit, std::set<int> &notRemoved, std::string &word, std::string &rword)
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