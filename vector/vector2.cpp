#include "vector2.h"

vector2::vector2(int s) : sz(s),
    elem(new double[s])
{
    for (int i = 0; i < s; ++i)
        elem[i] = 0.0;
}

vector2::vector2(std::initializer_list<double> lst) : sz{int(lst.size())},
    elem{new double[sz]}
{
    std::copy(lst.begin(), lst.end(), elem);
}

vector2::vector2(const vector2& arg) : sz{arg.sz},// Copying constructor
    elem{new double[arg.sz]}
{
    std::copy(arg.elem, arg.elem + arg.sz, elem);
}

vector2::vector2(vector2&& a) // Moving constructor
    :sz{a.sz}, elem{a.elem}
{
    a.sz = 0;
    a.elem = nullptr;
}

vector2& vector2::operator=(const vector2& a)// Copying assignment
{
    double* p = new double[a.sz];
    std::copy(a.elem,a.elem+a.sz, p);
    delete[] elem;
    elem = p;
    sz = a.sz;
    return *this;
}

vector2& vector2::operator=(vector2&& a) // Moving assignment
{
    delete[] elem;
    elem = a.elem;
    sz = a.sz;
    a.elem = nullptr;
    a.sz = 0;
    return *this;
}

double& vector2::operator[] (int n) // Operator [] for non-const vector
{
    return elem[n];
}

double vector2::operator[] (int n) const // Operator [] for constant vector
{
    return elem[n];
}
