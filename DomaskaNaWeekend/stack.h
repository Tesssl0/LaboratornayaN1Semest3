#pragma once
#ifndef STACK_H
#define STACK_H

#include <string>

struct Stack {
    std::string* arr;       // ������ ��� �������� ��������� �����
    int capacity;   // ������������ ������ �����
    int topIndex;   // ������ ������� �����
    bool silent;    // ���� ������ ������

    // �����������
    Stack(int size, bool silentMode = false);

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