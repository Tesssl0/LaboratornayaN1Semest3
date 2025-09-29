#ifndef ARRAY_H
#define ARRAY_H

struct Array {
    int* data;    // указатель на массив
    int size;     // текущий размер
    int capacity; // максимальная вместимость
};

void init(Array& arr, int initialCapacity = 10);
void destroy(Array& arr);
void resize(Array& arr);
void add(Array& arr, int value);
void addAt(Array& arr, int index, int value);
int get(const Array& arr, int index);
void remove(Array& arr, int index);
void set(Array& arr, int index, int value);
int length(const Array& arr);
void print(const Array& arr);

#endif 
