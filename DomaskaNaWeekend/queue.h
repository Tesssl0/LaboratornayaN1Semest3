#pragma once
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>
using namespace std;

template<typename T = string>
class Queue {
private:
    T* arr;
    int capacity;
    int frontIndex;
    int rearIndex;
    int size;
    bool silent;

public:
    Queue(int cap = 10, bool silentMode = false) {
        capacity = cap;
        arr = new T[capacity];
        frontIndex = 0;
        rearIndex = -1;
        size = 0;
        silent = silentMode;
    }

    ~Queue() {
        delete[] arr;
    }

    void enqueue(T value) {
        if (size == capacity) {
            int newCapacity = capacity * 2;
            T* newArr = new T[newCapacity];
            for (int i = 0; i < size; i++) {
                newArr[i] = arr[(frontIndex + i) % capacity];
            }
            delete[] arr;
            arr = newArr;
            capacity = newCapacity;
            frontIndex = 0;
            rearIndex = size - 1;
        }
        rearIndex = (rearIndex + 1) % capacity;
        arr[rearIndex] = value;
        size++;
        if (!silent) {
            cout << "Ёлемент " << value << " добавлен в очередь" << endl;
        }
    }

    T dequeue() {
        if (size == 0) {
            if (!silent) {
                cout << "ќчередь пуста!" << endl;
            }
            return T();
        }
        T value = arr[frontIndex];
        if (!silent) {
            cout << "Ёлемент " << value << " удалЄн из очереди" << endl;
        }
        frontIndex = (frontIndex + 1) % capacity;
        size--;
        return value;
    }

    T front() {
        if (size == 0) {
            if (!silent) {
                cout << "ќчередь пуста!" << endl;
            }
            return T();
        }
        return arr[frontIndex];
    }

    bool isEmpty() {
        return size == 0;
    }

    int getSize() {
        return size;
    }
};

#endif