#include "Queue.h"

// �����������
Queue::Queue(int cap) {
    capacity = cap;
    arr = new int[capacity];
    frontIndex = 0;
    rearIndex = -1;
    size = 0;
}

// ����������
Queue::~Queue() {
    delete[] arr;
}

// ���������� �������� � �������
void Queue::enqueue(int value) {
    if (size == capacity) {
        cout << "������� �����������!" << endl;
        return;
    }
    rearIndex = (rearIndex + 1) % capacity; // ����������� ��������
    arr[rearIndex] = value;
    size++;
    cout << "������� " << value << " �������� � �������" << endl;
}

// �������� �������� �� �������
void Queue::dequeue() {
    if (size == 0) {
        cout << "������� �����!" << endl;
        return;
    }
    cout << "������� " << arr[frontIndex] << " ����� �� �������" << endl;
    frontIndex = (frontIndex + 1) % capacity; // ����������� ��������
    size--;
}

// �������� ��������� ��������
int Queue::front() {
    if (size == 0) {
        cout << "������� �����!" << endl;
        return -1;
    }
    return arr[frontIndex];
}

// ��������, ������ �� �������
bool Queue::isEmpty() {
    return size == 0;
}
