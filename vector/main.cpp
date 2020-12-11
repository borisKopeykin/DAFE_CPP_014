#include <iostream>
#include "std_lib.h"
//#include "vector1.h"
//#include "vector2.h"
//#include "vector3.h"

template<typename T, typename A = std::allocator<T>> class vector3
{
    int sz; // Размер

    A all;

    T* elem; // Указатель на элементы (или 0)

    int space; // Количество элементов плюс количество свободных слотов

public:
    vector3() : sz{0}, elem{nullptr}, space{0} { }

    T& at(int n)
    {
            if (n < 0 || sz <= n) throw out_of_range();
            return elem[n];
    }

    const T& at(int n) const
    {
            if (n < 0 || sz <= n) throw out_of_range();
            return elem[n];
    }

    explicit vector3(int s):sz{s}, elem{new T[s]}, space{s}
    {
        for (int i = 0; i < sz; ++i)  // Элементы
            elem[i] = 0;              // инициализированы
    }

    vector3(std::initializer_list<T> lst):sz{lst.size()}, elem{new T[sz]}, space{lst.size()}{
               std::copy(lst.begin(), lst.end(), elem);
           }

    vector3(const vector3& copy_vector):sz{copy_vector.size()}, elem{new T[sz]}, space{copy_vector.capacity()} {
               std::copy(copy_vector.elements, copy_vector.elements + sz, elem);
           }

    // Копирующие конструктор и присваивание:
//    vector3(const vector3&);
//    vector3& operator=(const vector3&);

    // Перемещающие конструктор и присваивание:
//    vector3(vector3&&);
//    vector3& operator=(vector3&&);

    ~vector3() { delete[] elem; } // Деструктор

    T& operator[] (int n) {return elem[n];} // Доступ для неконстантного вектора
    T operator[] (int n) const {return elem[n];} // Доступ для
                                                             // константного вектора
    int size() const { return sz; } // Возвращает значение размера вектора

//    void reserve(int newallock); // Добавление памяти для новых элементов

    int capacity() const { return space; } // Возвращает размер доступной памяти

//    void resize(int newsize); // Устанавливает размер вектора

//    void push_back(double d); // Добавление элемента в конец вектора



T *p = new T[copy_vector.size()]
{
        for (int i=0; i < copy_vector.size(); i++)
            p[i] = copy_vector.elem[i];
        delete[] elem;
        elem = p;
        space = sz = copy_vector.size();
        return *this;
}

vector3(vector3&& a):sz{a.size()}, elem{ a.elem}, space{a.capacity()}
{
        a.sz = 0;
        a.space = 0;
        a.elem = nullptr;
}

// Перемещающий конструктор:
vector3(vector3&& a)
    :sz{a.sz}, elem{a.elem}
{
    a.sz = 0;
    a.elem = nullptr;
}


// Копирующее присваивание:
vector3& operator=(const vector3& copy_vector)
{
    if (this == &copy_vector) return *this;

    if (copy_vector.size() <= space){
        for (int i(0); i < copy_vector.size(); i++)
            elem[i] = copy_vector.elements[i];
        sz = copy_vector.size();
        return *this;
}


// Перемещающее присваивание:
vector3& operator=(vector3&& a)
{
    delete[] elem;
    elem = a.elem;
    sz = a.sz();
    space = a.capacity();
    a.elem = nullptr;
    a.sz = 0;
    a.space = 0;
    return *this;
}


// Добавление памяти для записи новых элементов:
void reserve(int newallock)
{
    if (newallock <= space) return;
    T* p = all.allocate(newallock);
    for (int i=0; i<sz; ++i)
        all.construct(&p[i], elem[i]);
    for (int i=0; i<sz; ++i)
        all.destroy(&elem[i]);
    all.deallocate(elem, space);
    elem = p;
    space = newallock;
}


// Установка размера вектора:
void resize(int newsize, T value = T())
{
    reserve(newsize);
    for (int i=sz; i<newsize; ++i)
        all.construct(&elem[i], value);
    for (int i=sz; i<newsize; ++i)
        all.destroy(&elem[i]);
    sz = newsize;
}


// Добавление элемента в конец вектора:
void push_back(const T& value)
{
    if (space==0)
        reserve(8);
    else if (sz==space)
        reserve (2*space);
    all.construct(&elem[sz], value);
    ++sz;
}

};


int main()
{
    vector3 v2(12);
    v2.reserve(15);
    v2[0] = 10;
    std::cout << v2[10] << std::endl;
    std::cout << v2.capacity() - v2.size();
    return 0;
}

