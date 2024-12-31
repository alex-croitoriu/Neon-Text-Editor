#include "bit.hpp"

void Bit::reset(std::vector<int> &bit)
{
    for (int i = 0; i < bit.size(); i++)
        bit[i] = 0;
}

void Bit::upd(int p, int v, std::vector<int> &bit)
{
    if (p == 0)
        bit[p] += v;

    for (; p && p < bit.size(); p += p & -p)
        bit[p] += v;
}

int Bit::get(int p, std::vector<int> &bit)
{
    int ans = bit[0];

    for (; p; p -= p & -p)
        ans += bit[p];

    return ans;
}
