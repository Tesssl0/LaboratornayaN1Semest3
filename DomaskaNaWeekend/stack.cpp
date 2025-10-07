#include "Stack.h"
#include <iostream>
using namespace std;

// �����������
Stack::Stack(int size, bool silentMode) {
    capacity = size;
    arr = new string[capacity];
    topIndex = -1;
    silent = silentMode;

    // �������������� ��� �������� ������� ��������
    for (int i = 0; i < capacity; i++) {
        arr[i] = "";
    }
}

// ����������
Stack::~Stack() {
    if (arr != nullptr) {
        delete[] arr;
        arr = nullptr;
    }
}

// ���������� �������� � ����
void Stack::push(const string& value) {
    if (topIndex >= capacity - 1) {
        if (!silent) {
            cout << "���� ����������!" << endl;
        }
        return;
    }
    topIndex++;
    arr[topIndex] = value;
    if (!silent) {
        cout << "������� " << value << " �������� � ����" << endl;
    }
}

// �������� �������� �� �����
void Stack::pop() {
    if (topIndex < 0) {
        if (!silent) {
            cout << "���� ����!" << endl;
        }
        return;
    }
    if (!silent) {
        cout << "������� " << arr[topIndex] << " ����� �� �����" << endl;
    }
    topIndex--;
}

// �������� �������� ��������
string Stack::top() {
    if (topIndex < 0) {
        if (!silent) {
            cout << "���� ����!" << endl;
        }
        return "";
    }
    return arr[topIndex];
}

// ��������, ���� �� ����
bool Stack::isEmpty() {
    return topIndex < 0;
}

// ����������� �����������
Stack::Stack(const Stack& other) {
    capacity = other.capacity;
    topIndex = other.topIndex;
    silent = other.silent;
    arr = new string[capacity];
    for (int i = 0; i <= topIndex; i++) {
        arr[i] = other.arr[i];
    }
}

// �������� ������������
Stack& Stack::operator=(const Stack& other) {
    if (this != &other) {
        delete[] arr;
        capacity = other.capacity;
        topIndex = other.topIndex;
        silent = other.silent;
        arr = new string[capacity];
        for (int i = 0; i <= topIndex; i++) {
            arr[i] = other.arr[i];
        }
    }
    return *this;
}