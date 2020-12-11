#ifndef VECTOR1_H
#define VECTOR1_H

class vector1 // Объявление класса vector1
{
    int sz; // Размер вектора
    double* elem; // Указатель для первого элемента вектора
public:
    vector1 (int); // Конструктор
    int size() const { return sz; } // Константная функция-член для вывода размера
    double get(int n) const { return elem[n]; } // Получение значения по индексу
    void set(int n, double v) { elem[n] = v; } // Ввод элемента по индексу
    ~vector1() { delete[] elem; } // Деструктор
};

#endif // VECTOR1_H
