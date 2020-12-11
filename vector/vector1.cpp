#include "vector1.h"

vector1::vector1(int s) : sz(s), elem(new double[s])
{
    for (int i = 0; i < s; ++i)
        elem[i] = 0;
}

