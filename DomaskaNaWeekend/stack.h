#pragma once
#ifndef STACK_H
#define STACK_H

#include <string>

struct Stack {
public:
    std::string* arr;       // ������ ��� �������� ��������� �����
    int capacity;   // ������������ ������ �����
    int topIndex;   // ������ ������� �����
    bool silent;    // ���� ������ ������



    // �����������
    Stack(int size, bool silentMode = false);

    // ����������� �����������
    Stack(const Stack& other);

    int getTopIndex() const { return topIndex; } // ���������� ������ �������
    std::string getAt(int index) const { return arr[index]; } // ���������� ������� �� �������

    // �������� ������������
    Stack& operator=(const Stack& other);

    // ����������
    ~Stack();

    // ���������� �������� � ����
    void push(const std::string& value);

    // �������� �������� �� �����
    void pop();

    // �������� �������� ��������
    std::string top();

    // ��������, ���� �� ����
    bool isEmpty();
};

#endif // STACK_H