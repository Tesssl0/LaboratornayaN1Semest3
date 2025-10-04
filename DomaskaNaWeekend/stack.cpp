#include "Stack.h"
#include <iostream>
using namespace std;

// �����������
Stack::Stack(int size, bool silentMode) {
    capacity = size;
    arr = new string[capacity];
    topIndex = -1;
    silent = silentMode;
}

// ����������
Stack::~Stack() {
    delete[] arr;
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