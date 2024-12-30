#pragma once

#include <string>
#include <vector>
#include <set>

namespace Replace
{
    void KMP(std::string &s, std::string &word, std::vector<int> &positions, bool &wholeWord);
    bool isApOnScreen(int ap, int sz);
    bool isValid(char ch);
    void delAp(int idx, std::vector<int> &prv, std::vector<int> &nxt, std::vector<int> &bit, std::vector<int> &gone, std::set<int> &notRemoved, int vl = 1);
    int findLastReplace(int idx, std::vector<int> &bit);
    int findNextReplace(int idx, std::vector<int> &bit);
    bool canReplace(int idx, std::vector<int> &bit, std::vector<int> &positions, std::vector<int> &gone, std::string &rword, std::string &word);
    int findNextValidAppearance(int idx, std::vector<int> &bit, std::vector<int> &positions, std::vector<int> &gone, std::string &rword, std::string &word, std::vector<int> &prv, std::vector<int> &nxt, std::set<int> &notRemoved);
    int findPrevValidAppearance(int idx, std::vector<int> &bit, std::vector<int> &positions, std::vector<int> &gone, std::string &rword, std::string &word, std::vector<int> &prv, std::vector<int> &nxt, std::set<int> &notRemoved);
    int findRealPosition(int idx, std::vector<int> &positions, std::vector<int> &bit, std::string &word, std::string &rword);
    int traceFirstApToRender(int idx, std::vector<int> &positions, std::vector<int> &bit, std::set<int> &notRemoved, std::string &word, std::string &rword);
}