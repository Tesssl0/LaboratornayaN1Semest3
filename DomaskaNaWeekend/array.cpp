#include <iostream>
#include "array.h"
using namespace std;

// ������������� �������
void init(Array& arr, int initialCapacity) {
    arr.capacity = initialCapacity;
    arr.size = 0;
    arr.data = new string[arr.capacity];
}

// ������������ ������
void destroy(Array& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

// ���������� ������� �������
void resize(Array& arr) {
    arr.capacity *= 2;
    string* newData = new string[arr.capacity];
    for (int i = 0; i < arr.size; i++) {
        newData[i] = arr.data[i];
    }
    delete[] arr.data;
    arr.data = newData;
}

// ���������� �������� � �����
void add(Array& arr, const string& value) {
    if (arr.size == arr.capacity) {
        resize(arr);
    }
    arr.data[arr.size++] = value;
}

// ���������� �������� �� �������
void addAt(Array& arr, int index, const string& value) {
    if (arr.size == arr.capacity) {
        resize(arr);
    }
    for (int i = arr.size; i > index; i--) {
        arr.data[i] = arr.data[i - 1];
    }
    arr.data[index] = value;
    arr.size++;
}

// ��������� �������� �� �������
string get(const Array& arr, int index) {
    return arr.data[index];
}

// �������� �������� �� �������
void remove(Array& arr, int index) {
    for (int i = index; i < arr.size - 1; i++) {
        arr.data[i] = arr.data[i + 1];
    }
    arr.size--;
}

// ������ �������� �� �������
void set(Array& arr, int index, const string& value) {
    arr.data[index] = value;
}

// ��������� ����� �������
int length(const Array& arr) {
    return arr.size;
}

// ������ ���� ���������
void print(const Array& arr) {
    for (int i = 0; i < arr.size; i++) {
        cout << arr.data[i] << " ";
    }
    cout << endl;
}

// ����� �������� �� ��������
int findInArray(const Array& arr, const std::string& value) {
    for (int i = 0; i < arr.size; i++) {
        if (arr.data[i] == value) {
            return i;
        }
    }
    return -1;
}