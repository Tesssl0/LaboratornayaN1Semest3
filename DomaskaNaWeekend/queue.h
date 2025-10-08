#pragma once
#include <iostream>
#include <string>

using namespace std;

struct QueueNode {
    string data;
    QueueNode* next;
};

struct Queue {
    QueueNode* frontPtr;
    QueueNode* rearPtr;
    int size;
    bool silent;
};

// ������������� �������
void initQueue(Queue* q, bool silentMode = false);

// �������� ��������
void enqueue(Queue* q, const string& value);
string dequeue(Queue* q);
string front(Queue* q);
bool isEmpty(Queue* q);
int getSize(Queue* q);

// ��������������� �������
void printQueue(Queue* q);
void setSilent(Queue* q, bool mode);
void clearQueue(Queue* q);