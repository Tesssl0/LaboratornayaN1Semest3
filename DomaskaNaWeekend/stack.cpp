#include "Stack.h"
#include <iostream>
using namespace std;

// �����������
Stack::Stack(int size, bool silentMode) {
    capacity = size;
    arr = new int[capacity];
    topIndex = -1; // ���� ������
    silent = silentMode;
}

// ����������
Stack::~Stack() {
    delete[] arr;
}

// ���������� �������� � ����
void Stack::push(int value) {
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
int Stack::top() {
    if (topIndex < 0) {
        if (!silent) {
            cout << "���� ����!" << endl;
        }
        return -1; // ��� ����� ������ ����������
    }
    return arr[topIndex];
}

// ��������, ���� �� ����
bool Stack::isEmpty() {
    return topIndex < 0;
}

