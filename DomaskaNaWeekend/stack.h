#pragma once
#ifndef STACK_H
#define STACK_H

struct Stack {
    int* arr;       // ������ ��� �������� ��������� �����
    int capacity;   // ������������ ������ �����
    int topIndex;   // ������ ������� �����
    bool silent;    // ���� ������ ������

    // �����������
    Stack(int size, bool silentMode = false);

    // ����������
    ~Stack();

    // ���������� �������� � ����
    void push(int value);

    // �������� �������� �� �����
    void pop();

    // �������� �������� ��������
    int top();

    // ��������, ���� �� ����
    bool isEmpty();
};

#endif // STACK_H
