#include "queue.h"

// ������������� �������
void initQueue(Queue* q, bool silentMode) {
    q->frontPtr = nullptr;
    q->rearPtr = nullptr;
    q->size = 0;
    q->silent = silentMode;
}

// ���������� �������� � �������
void enqueue(Queue* q, const string& value) {
    QueueNode* newNode = new QueueNode;
    newNode->data = value;
    newNode->next = nullptr;

    if (isEmpty(q)) {
        // ������� ����� - ����� ������� ���������� � ������ � ���������
        q->frontPtr = newNode;
        q->rearPtr = newNode;
    }
    else {
        // ��������� � ����� �������
        q->rearPtr->next = newNode;
        q->rearPtr = newNode;
    }

    q->size++;

    if (!q->silent) {
        cout << "�������� �������: " << value << endl;
    }
}

// �������� �������� �� �������
string dequeue(Queue* q) {
    if (isEmpty(q)) {
        if (!q->silent) {
            cout << "������� �����!" << endl;
        }
        return "";
    }

    // ��������� ������ ������� ��������
    string value = q->frontPtr->data;

    // ������� ������ �������
    QueueNode* temp = q->frontPtr;
    q->frontPtr = q->frontPtr->next;

    // ���� ������� ����� ������, ��������� rearPtr
    if (q->frontPtr == nullptr) {
        q->rearPtr = nullptr;
    }

    delete temp;
    q->size--;

    if (!q->silent) {
        cout << "�������� �������: " << value << endl;
    }

    return value;
}

// ������ ������� �������� (��� ��������)
string front(Queue* q) {
    if (isEmpty(q)) {
        if (!q->silent) {
            cout << "������� �����!" << endl;
        }
        return "";
    }

    return q->frontPtr->data;
}

// �������� �� �������
bool isEmpty(Queue* q) {
    return q->frontPtr == nullptr;
}

// ��������� ������� �������
int getSize(Queue* q) {
    return q->size;
}

// ����� �������
void printQueue(Queue* q) {
    if (isEmpty(q)) {
        cout << "������� �����" << endl;
        return;
    }

    cout << "������� (������ -> ���������): ";
    QueueNode* current = q->frontPtr;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// ��������� ������ ������
void setSilent(Queue* q, bool mode) {
    q->silent = mode;
}

// ������� �������
void clearQueue(Queue* q) {
    while (!isEmpty(q)) {
        dequeue(q);
    }
}