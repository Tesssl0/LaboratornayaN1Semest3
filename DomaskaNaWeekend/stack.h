#pragma once
#ifndef STACK_H
#define STACK_H

#include <string>

class Stack {
public:
    std::string* arr;       // массив для хранения элементов стека
    int capacity;   // максимальный размер стека
    int topIndex;   // индекс вершины стека
    bool silent;    // флаг тихого режима

    // Конструктор
    Stack(int size, bool silentMode = false);

    // Конструктор копирования
    Stack(const Stack& other);

    // Оператор присваивания
    Stack& operator=(const Stack& other);

    // Деструктор
    ~Stack();

    // Добавление элемента в стек
    void push(const std::string& value);

    // Удаление элемента из стека
    void pop();

    // Просмотр верхнего элемента
    std::string top();

    // Проверка, пуст ли стек
    bool isEmpty();
};

#endif // STACK_H