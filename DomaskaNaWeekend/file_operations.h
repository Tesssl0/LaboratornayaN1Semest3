#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <fstream>
#include <string>
#include <sstream>
#include "array.h"
#include "list.h"
#include "listTwo.h"
#include "queue.h"
#include "stack.h"
#include "fullBinaryTree.h"

using namespace std;

// Базовые функции для работы с файлами
void saveToFile(const string& filename, const string& data) {
    ofstream file(filename);
    if (file.is_open()) {
        file << data;
        file.close();
    }
}

string readFromFile(const string& filename) {
    ifstream file(filename);
    string data, line;
    if (file.is_open()) {
        while (getline(file, line)) {
            data += line + "\n";
        }
        file.close();
    }
    return data;
}

// Массив
void saveArrayToFile(const Array& arr, const string& filename) {
    string data;
    for (int i = 0; i < arr.size; i++) {
        data += arr.data[i] + " ";
    }
    saveToFile(filename, data);
}

void loadArrayFromFile(Array& arr, const string& filename) {
    string data = readFromFile(filename);
    if (data.empty()) return;

    destroy(arr);
    init(arr);

    stringstream ss(data);
    string value;
    while (ss >> value) {
        add(arr, value);
    }
}

// Односвязный список
void saveForwardListToFile(const ForwardList& flist, const string& filename) {
    string data;
    linkedList* current = flist.head;
    while (current != nullptr) {
        data += current->node + " ";
        current = current->next;
    }
    saveToFile(filename, data);
}

void loadForwardListFromFile(ForwardList& flist, const string& filename) {
    string data = readFromFile(filename);
    if (data.empty()) return;

    while (flist.head != nullptr) {
        linkedList* temp = flist.head;
        flist.head = flist.head->next;
        delete temp;
    }

    stringstream ss(data);
    string value;
    while (ss >> value) {
        addNode(&flist, nullptr, value, TAIL);
    }
}

// Двусвязный список
void saveForwardListTwoToFile(const ForwardListTwo& flist, const string& filename) {
    string data;
    DoublyNode* current = flist.head;
    while (current != nullptr) {
        data += current->node + " ";
        current = current->next;
    }
    saveToFile(filename, data);
}

void loadForwardListTwoFromFile(ForwardListTwo& flist, const string& filename) {
    string data = readFromFile(filename);
    if (data.empty()) return;

    while (flist.head != nullptr) {
        DoublyNode* temp = flist.head;
        flist.head = flist.head->next;
        delete temp;
    }
    flist.tail = nullptr;

    stringstream ss(data);
    string value;
    while (ss >> value) {
        addNodeTwo(&flist, nullptr, value, TAILTwo);
    }
}

// Очередь
template<typename T>
void saveQueueToFile(Queue<T>& queue, const string& filename) {
    string data;

    Queue<T> tempQueue(100, true);

    while (!queue.isEmpty()) {
        T value = queue.dequeue();
        data += value + " ";
        tempQueue.enqueue(value);
    }

    while (!tempQueue.isEmpty()) {
        queue.enqueue(tempQueue.dequeue());
    }

    saveToFile(filename, data);
}

template<typename T>
void loadQueueFromFile(Queue<T>& queue, const string& filename) {
    string data = readFromFile(filename);
    if (data.empty()) return;

    while (!queue.isEmpty()) {
        queue.dequeue();
    }

    stringstream ss(data);
    string value;
    while (ss >> value) {
        queue.enqueue(value);
    }
}

// Стек
void saveStackToFile(Stack& stack, const string& filename) {
    string data;

    Stack tempStack(100, true);
    Stack restoreStack(100, true);

    while (!stack.isEmpty()) {
        string value = stack.top();
        tempStack.push(value);
        stack.pop();
    }

    while (!tempStack.isEmpty()) {
        string value = tempStack.top();
        data += value + " ";
        restoreStack.push(value);
        tempStack.pop();
    }

    while (!restoreStack.isEmpty()) {
        stack.push(restoreStack.top());
        restoreStack.pop();
    }

    saveToFile(filename, data);
}

void loadStackFromFile(Stack& stack, const string& filename) {
    string data = readFromFile(filename);
    if (data.empty()) return;

    while (!stack.isEmpty()) {
        stack.pop();
    }

    Stack tempStack(100, true);
    stringstream ss(data);
    string value;

    while (ss >> value) {
        tempStack.push(value);
    }

    while (!tempStack.isEmpty()) {
        stack.push(tempStack.top());
        tempStack.pop();
    }
}

// Дерево
void saveTreeToFile(fullBinaryTree* tree, const string& filename) {
    if (!tree->root) {
        saveToFile(filename, "");
        return;
    }

    string data;
    Queue<Node*> q(100, true);
    q.enqueue(tree->root);

    while (!q.isEmpty()) {
        Node* temp = q.dequeue();
        if (temp) {
            data += temp->data + " ";
            if (temp->left) q.enqueue(temp->left);
            if (temp->right) q.enqueue(temp->right);
        }
    }

    saveToFile(filename, data);
}

void loadTreeFromFile(fullBinaryTree* tree, const string& filename) {
    string data = readFromFile(filename);
    if (data.empty()) return;

    tree->root = nullptr;

    stringstream ss(data);
    string value;
    while (ss >> value) {
        insert(tree, value);
    }
}

#endif