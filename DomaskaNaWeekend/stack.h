#pragma once
#ifndef STACK_H
#define STACK_H

#include <string>

class Stack {
public:
    std::string* arr;       // ������ ��� �������� ��������� �����
    int capacity;   // ������������ ������ �����
    int topIndex;   // ������ ������� �����
    bool silent;    // ���� ������ ������

    // �����������
    Stack(int size, bool silentMode = false);

    // ����������� �����������
    Stack(const Stack& other);

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