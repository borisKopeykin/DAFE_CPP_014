#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>

class vector2
{
    int sz; // Size

    double* elem; // Pointer for elements

public:

    vector2(const vector2&); // Copying constructor

    vector2& operator=(const vector2&); // Copying assignment

    vector2(vector2&& a); // Moving constructor

    vector2& operator=(vector2&&); // Moving assignment

    vector2(int);

    vector2(std::initializer_list<double>);

    double& operator[] (int);// Operator [] for non-const vector

    double operator[] (int) const;// Operator [] for constant vector

    int size() const { return sz; }

    double get(int n) const { return elem[n]; }

    void set(int n, double v) { elem[n] = v; }

    ~vector2() { delete[] elem; }
};

#endif // VECTOR2_H
