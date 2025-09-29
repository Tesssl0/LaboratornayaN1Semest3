#include "Stack.h"
#include <iostream>
using namespace std;

// Конструктор
Stack::Stack(int size, bool silentMode) {
    capacity = size;
    arr = new int[capacity];
    topIndex = -1; // стек пустой
    silent = silentMode;
}

// Деструктор
Stack::~Stack() {
    delete[] arr;
}

// Добавление элемента в стек
void Stack::push(int value) {
    if (topIndex >= capacity - 1) {
        if (!silent) {
            cout << "Стек переполнен!" << endl;
        }
        return;
    }
    topIndex++;
    arr[topIndex] = value;
    if (!silent) {
        cout << "Элемент " << value << " добавлен в стек" << endl;
    }
}

// Удаление элемента из стека
void Stack::pop() {
    if (topIndex < 0) {
        if (!silent) {
            cout << "Стек пуст!" << endl;
        }
        return;
    }
    if (!silent) {
        cout << "Элемент " << arr[topIndex] << " удалён из стека" << endl;
    }
    topIndex--;
}

// Просмотр верхнего элемента
int Stack::top() {
    if (topIndex < 0) {
        if (!silent) {
            cout << "Стек пуст!" << endl;
        }
        return -1; // или можно кинуть исключение
    }
    return arr[topIndex];
}

// Проверка, пуст ли стек
bool Stack::isEmpty() {
    return topIndex < 0;
}

