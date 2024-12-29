#pragma once

#include <vector>

namespace Bit
{
    void reset(std::vector<int> &bit);
    void upd(int p, int v, std::vector<int> &bit);
    int get(int p, std::vector<int> &bit);
}