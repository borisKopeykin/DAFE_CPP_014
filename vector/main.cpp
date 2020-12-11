#include <iostream>
//#include "std_lib.h"
//#include "vector1.h"
//#include "vector2.h"
//#include "vector3.h"


template<typename T, typename A = std::allocator<T>> class vector3
{
    A all;
    int sz;
    T *elem;
    int space;
public:
    vector3(): sz{0}, elem{nullptr}, space{0} {}

     T& at(int k)
     {
        if (k < 0 || sz <= k) throw out_of_range();
        return elem[k];
     }

     const T& at(int k) const
     {
        if (k < 0 || sz <= k) throw out_of_range();
        return elem[k];
     }

    explicit vector3(int s):sz{s}, elem{new T[s]}, space{s}
    {
        for (int i(0); i < s; i++)
            elem[i] = 0;
    }

    vector3(std::initializer_list<T> lst):sz{static_cast<int>(lst.size())},
        elem{new T[sz]}, space{static_cast<int>(lst.size())}
    {
        std::copy(lst.begin(), lst.end(), elem);
    }

    vector3(const vector3& copy_vector):sz{copy_vector.size()}, elem{new T[sz]}, space{copy_vector.capacity()}
    {
        std::copy(copy_vector.elements, copy_vector.elements + sz, elem);
    }

    vector3& operator=(const vector3& copy_vector)
    {
        if (this == &copy_vector) return *this;

        if (copy_vector.size() <= space)
        {
            for (int i(0); i < copy_vector.size(); i++)
                elem[i] = copy_vector.elements[i];
            sz = copy_vector.size();
            return *this;
        }

        T *stor = new T[copy_vector.size()];
        for (int i(0); i < copy_vector.size(); i++)
            stor[i] = copy_vector.elements[i];
        delete[] elem;
        elem = stor;
        space = sz = copy_vector.size();
        return *this;
    }

    vector3(vector3&& trans):sz{trans.size()}, elem{ trans.elem}, space{trans.capacity()}
    {
        trans.vsize = 0;
        trans.space = 0;
        trans.elements = nullptr;
    }

    vector3& operator=(vector3&& trans)
    {
        delete[] elem;
        elem = trans.elements;
        sz = trans.size();
        space = trans.capacity();
        trans.elements = nullptr;
        trans.vsize = 0;
        trans.space = 0;
        return *this;
    }


    T& operator[](int n){return elem[n];}
    T operator[](int n) const {return elem[n];};

    ~vector3() {delete[] elem;}

    void reserve(int newalloc)
    {
        if (newalloc <= space) return;
        T *storage = all.allocate(newalloc);
        for (int i(0); i < sz; i++)
            all.construct(&storage[i],elem[i]);
        for (int i(0); i < sz; i++)
            all.destroy(&elem[i]);
        all.deallocate(elem, space);
        elem = storage;
        space = newalloc;
    }

    void resize(int newsize, T val = T())
    {
        reserve(newsize);
        for (int i(sz); i < newsize; i++)
            all.construct(&elem[i], val);
        for (int i(sz); i < newsize; i++)
            all.destroy(&elem[i]);
        sz = newsize;
    }

    void push_back(const T& val)
    {
        if (space == 0)
            reserve(8);
        else if (sz == space)
            reserve(2*space);
        all.construct(&elem[sz], val);
        sz++;
    }

    int size() const {return sz;}
    int capacity() const {return space;}

};


int main()
{
  vector3<int> v = {3,4,5,3,7,5};
  v.push_back(3);
  std::cout << v.size() << std::endl;;
  for (int i=0; i < static_cast<int>(v.size()); i++)
      std::cout << v[i] << "\t";

}
