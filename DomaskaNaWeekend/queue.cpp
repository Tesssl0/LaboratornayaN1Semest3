#include "Queue.h"

// Конструктор
Queue::Queue(int cap) {
    capacity = cap;
    arr = new int[capacity];
    frontIndex = 0;
    rearIndex = -1;
    size = 0;
}

// Деструктор
Queue::~Queue() {
    delete[] arr;
}

// Добавление элемента в очередь
void Queue::enqueue(int value) {
    if (size == capacity) {
        cout << "Очередь переполнена!" << endl;
        return;
    }
    rearIndex = (rearIndex + 1) % capacity; // циклическое смещение
    arr[rearIndex] = value;
    size++;
    cout << "Элемент " << value << " добавлен в очередь" << endl;
}

// Удаление элемента из очереди
void Queue::dequeue() {
    if (size == 0) {
        cout << "Очередь пуста!" << endl;
        return;
    }
    cout << "Элемент " << arr[frontIndex] << " удалён из очереди" << endl;
    frontIndex = (frontIndex + 1) % capacity; // циклическое смещение
    size--;
}

// Просмотр переднего элемента
int Queue::front() {
    if (size == 0) {
        cout << "Очередь пуста!" << endl;
        return -1;
    }
    return arr[frontIndex];
}

// Проверка, пустая ли очередь
bool Queue::isEmpty() {
    return size == 0;
}
