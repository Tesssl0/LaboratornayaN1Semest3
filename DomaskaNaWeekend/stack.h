#pragma once
#ifndef STACK_H
#define STACK_H

struct Stack {
    int* arr;       // массив для хранения элементов стека
    int capacity;   // максимальный размер стека
    int topIndex;   // индекс вершины стека
    bool silent;    // флаг тихого режима

    // Конструктор
    Stack(int size, bool silentMode = false);

    // Деструктор
    ~Stack();

    // Добавление элемента в стек
    void push(int value);

    // Удаление элемента из стека
    void pop();

    // Просмотр верхнего элемента
    int top();

    // Проверка, пуст ли стек
    bool isEmpty();
};

#endif // STACK_H
