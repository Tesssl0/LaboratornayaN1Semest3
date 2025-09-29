#ifndef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H

#include <iostream>
#include <sstream>
#include <string>
#include "file_operations.h"

using namespace std;

// ���������� ��������� ������
Array globalArray;
ForwardList globalForwardList;
ForwardListTwo globalForwardListTwo;
Queue<int> globalQueue(100, true);  // ����� ����� �� ���������
Stack globalStack(100, true);       // ����� ����� �� ���������
fullBinaryTree globalTree;

// ���� ��� ������������ ������ ��������
bool firstLoad = true;

// ������������� ���������� ��������
void initGlobalStructures() {
    init(globalArray);
    globalForwardList.head = nullptr;
    globalForwardListTwo.head = nullptr;
    globalForwardListTwo.tail = nullptr;
    globalTree.root = nullptr;
    firstLoad = true;
}

// ������� ��� ������ � ��������
void MPUSH(int value) {
    add(globalArray, value);
    cout << "�������� ������� " << value << " � ������" << endl;
}

void MDEL(int index) {
    if (index >= 0 && index < globalArray.size) {
        int value = get(globalArray, index);
        remove(globalArray, index);
        cout << "������ ������� " << value << " �� ������� �� ������� " << index << endl;
    }
    else {
        cout << "�������� ������" << endl;
    }
}

int MGET(int index) {
    if (index >= 0 && index < globalArray.size) {
        int value = get(globalArray, index);
        cout << "������� �� ������� " << index << ": " << value << endl;
        return value;
    }
    else {
        cout << "�������� ������" << endl;
        return -1;
    }
}

// ������� ��� ������ � ����������� �������
void FPUSH(int value, int position = -1) {
    if (position == -1) {
        // ���������� � �����
        addNode(&globalForwardList, nullptr, value, TAIL);
    }
    else {
        // ���������� �� �������
        linkedList* target = getNodeByIndex(globalForwardList, position);
        if (target) {
            addNode(&globalForwardList, target, value, AFTER);
        }
        else {
            cout << "�������� �������" << endl;
            return;
        }
    }
    cout << "�������� ������� " << value << " � ����������� ������" << endl;
}

void FDEL(int value) {
    if (deleteNodeIndex(&globalForwardList, value)) {
        cout << "������ ������� " << value << " �� ������������ ������" << endl;
    }
    else {
        cout << "������� �� ������" << endl;
    }
}

int FGET(int index) {
    linkedList* node = getNodeByIndex(globalForwardList, index);
    if (node) {
        cout << "������� �� ������� " << index << ": " << node->node << endl;
        return node->node;
    }
    else {
        cout << "�������� ������" << endl;
        return -1;
    }
}

// ������� ��� ������ � ���������� �������
void LPUSH(int value, int position = -1) {
    if (position == -1) {
        // ���������� � �����
        addNodeTwo(&globalForwardListTwo, nullptr, value, TAILTwo);
    }
    else {
        // ���������� �� �������
        DoublyNode* target = getNodeByIndexTwo(globalForwardListTwo, position);
        if (target) {
            addNodeTwo(&globalForwardListTwo, target, value, AFTERTwo);
        }
        else {
            cout << "�������� �������" << endl;
            return;
        }
    }
    cout << "�������� ������� " << value << " � ���������� ������" << endl;
}

void LDEL(int value) {
    if (deleteNodeIndexTwo(&globalForwardListTwo, value)) {
        cout << "������ ������� " << value << " �� ����������� ������" << endl;
    }
    else {
        cout << "������� �� ������" << endl;
    }
}

int LGET(int index) {
    DoublyNode* node = getNodeByIndexTwo(globalForwardListTwo, index);
    if (node) {
        cout << "������� �� ������� " << index << ": " << node->node << endl;
        return node->node;
    }
    else {
        cout << "�������� ������" << endl;
        return -1;
    }
}

// ������� ��� ������ � ��������
void QPUSH(int value) {
    globalQueue.enqueue(value);
    cout << "�������� ������� " << value << " � �������" << endl;
}

int QPOP() {
    int value = globalQueue.dequeue();
    if (value != int()) {
        cout << "�������� ������� " << value << " �� �������" << endl;
    }
    return value;
}

int QGET() {
    int value = globalQueue.front();
    if (value != int()) {
        cout << "������ ������� �������: " << value << endl;
    }
    return value;
}

// ������� ��� ������ �� ������
void SPUSH(int value) {
    globalStack.push(value);
    cout << "�������� ������� " << value << " � ����" << endl;
}

void SPOP() {
    if (!globalStack.isEmpty()) {
        int value = globalStack.top();
        globalStack.pop();
        cout << "�������� ������� " << value << " �� �����" << endl;
    }
}

int SGET() {
    if (!globalStack.isEmpty()) {
        int value = globalStack.top();
        cout << "������� ������� �����: " << value << endl;
        return value;
    }
    return -1;
}

// ������� ��� ������ � �������
void TINSERT(int value) {
    insert(&globalTree, value);
    cout << "�������� ������� " << value << " � ������" << endl;
}

void TDEL(int value) {
    deleteNode(&globalTree, value);
}

int TGET(int value) {
    Node* node = BFS(&globalTree, value);
    if (node) {
        cout << "������ ������� " << value << " � ������" << endl;
        return node->data;
    }
    else {
        cout << "������� " << value << " �� ������ � ������" << endl;
        return -1;
    }
}

// ������������� ������� PRINT
// ������������� ������� PRINT
void PRINT(const string& structure) {
    if (structure == "M") {
        cout << "������: ";
        print(globalArray);
    }
    else if (structure == "F") {
        cout << "����������� ������: ";
        printList(globalForwardList);
    }
    else if (structure == "L") {
        cout << "���������� ������: ";
        printListTwo(globalForwardListTwo);
    }
    else if (structure == "Q") {
        cout << "�������: ";
        if (globalQueue.isEmpty()) {
            cout << "�����" << endl;
        }
        else {
            // ������� ����� ��� �����������
            cout << "[������: " << globalQueue.front() << ", ������: ";

            // ������� ������� �������
            Queue<int> tempQueue(100, true);
            int size = 0;
            while (!globalQueue.isEmpty()) {
                int value = globalQueue.dequeue();
                tempQueue.enqueue(value);
                size++;
            }

            // ��������������� �������
            while (!tempQueue.isEmpty()) {
                globalQueue.enqueue(tempQueue.dequeue());
            }

            cout << size << " ���������]" << endl;
        }
    }
    else if (structure == "S") {
        cout << "����: ";
        if (globalStack.isEmpty()) {
            cout << "����" << endl;
        }
        else {
            // ������� ����� ��� ����������� - ������ ������� ������� � ������
            cout << "[�������: " << globalStack.top() << ", ������: ";

            // ������� ������� �����
            Stack tempStack(100, true);
            int size = 0;
            while (!globalStack.isEmpty()) {
                int value = globalStack.top();
                tempStack.push(value);
                globalStack.pop();
                size++;
            }

            // ��������������� ����
            while (!tempStack.isEmpty()) {
                globalStack.push(tempStack.top());
                tempStack.pop();
            }

            cout << size << " ���������]" << endl;
        }
    }
    else if (structure == "T") {
        // ����� ������ ������� ���������
        cout << "=== ������ ===" << endl;
        cout << "Inorder (������������): ";
        inorder(globalTree.root);
        cout << endl;

        cout << "Preorder (������): ";
        preorder(globalTree.root);
        cout << endl;

        cout << "Postorder (��������): ";
        postorder(globalTree.root);
        cout << endl;

        printBFS(&globalTree);
    }
    else if (structure == "T_INORDER") {
        cout << "������ (Inorder): ";
        inorder(globalTree.root);
        cout << endl;
    }
    else if (structure == "T_PREORDER") {
        cout << "������ (Preorder): ";
        preorder(globalTree.root);
        cout << endl;
    }
    else if (structure == "T_POSTORDER") {
        cout << "������ (Postorder): ";
        postorder(globalTree.root);
        cout << endl;
    }
    else if (structure == "T_BFS") {
        printBFS(&globalTree);
    }
    else {
        cout << "����������� ���������: " << structure << endl;
    }
}

// ������� ���������� ���� ������
void SAVE_ALL() {
    saveArrayToFile(globalArray, "array_data.txt");
    saveForwardListToFile(globalForwardList, "forward_list_data.txt");
    saveForwardListTwoToFile(globalForwardListTwo, "forward_list_two_data.txt");
    saveQueueToFile(globalQueue, "queue_data.txt");
    saveStackToFile(globalStack, "stack_data.txt");
    saveTreeToFile(&globalTree, "tree_data.txt");
    cout << "��� ������ ��������� � �����" << endl;
}

// ������� �������� ���� ������
void LOAD_ALL() {
    // ��� ������ �������� ������ ��������� ������
    if (firstLoad) {
        loadArrayFromFile(globalArray, "array_data.txt");
        loadForwardListFromFile(globalForwardList, "forward_list_data.txt");
        loadForwardListTwoFromFile(globalForwardListTwo, "forward_list_two_data.txt");
        loadQueueFromFile(globalQueue, "queue_data.txt");
        loadStackFromFile(globalStack, "stack_data.txt");
        loadTreeFromFile(&globalTree, "tree_data.txt");
        firstLoad = false;
        cout << "��� ������ ��������� �� ������" << endl;
    }
    else {
        // ��� ��������� �������� ���������� �������������
        cout << "������� ������ ����� ��������. ����������? (y/n): ";
        string answer;
        getline(cin, answer);
        if (answer == "y" || answer == "Y") {
            // ������� ������� ������
            destroy(globalArray);
            init(globalArray);

            while (globalForwardList.head != nullptr) {
                linkedList* temp = globalForwardList.head;
                globalForwardList.head = globalForwardList.head->next;
                delete temp;
            }

            while (globalForwardListTwo.head != nullptr) {
                DoublyNode* temp = globalForwardListTwo.head;
                globalForwardListTwo.head = globalForwardListTwo.head->next;
                delete temp;
            }
            globalForwardListTwo.tail = nullptr;

            while (!globalQueue.isEmpty()) {
                globalQueue.dequeue();
            }

            while (!globalStack.isEmpty()) {
                globalStack.pop();
            }

            globalTree.root = nullptr;

            // ��������� ����� ������
            loadArrayFromFile(globalArray, "array_data.txt");
            loadForwardListFromFile(globalForwardList, "forward_list_data.txt");
            loadForwardListTwoFromFile(globalForwardListTwo, "forward_list_two_data.txt");
            loadQueueFromFile(globalQueue, "queue_data.txt");
            loadStackFromFile(globalStack, "stack_data.txt");
            loadTreeFromFile(&globalTree, "tree_data.txt");
            cout << "��� ������ ��������� �� ������" << endl;
        }
        else {
            cout << "�������� ��������" << endl;
        }
    }
}

// ������� ������� ���� ������
void CLEAR_ALL() {
    // ������� ��������� � ������
    destroy(globalArray);
    init(globalArray);

    while (globalForwardList.head != nullptr) {
        linkedList* temp = globalForwardList.head;
        globalForwardList.head = globalForwardList.head->next;
        delete temp;
    }

    while (globalForwardListTwo.head != nullptr) {
        DoublyNode* temp = globalForwardListTwo.head;
        globalForwardListTwo.head = globalForwardListTwo.head->next;
        delete temp;
    }
    globalForwardListTwo.tail = nullptr;

    while (!globalQueue.isEmpty()) {
        globalQueue.dequeue();
    }

    while (!globalStack.isEmpty()) {
        globalStack.pop();
    }

    globalTree.root = nullptr;

    cout << "��� ������ ������� �� ������" << endl;
}

// ��������� ��������� ������
void processCommand(const string& command) {
    istringstream iss(command);
    string cmd;
    iss >> cmd;

    // �������� ������ ����� if-else ������� ������ map
    if (cmd == "MPUSH") {
        int value;
        if (iss >> value) MPUSH(value);
        else cout << "�������� ������ �������: MPUSH <value>" << endl;
    }
    else if (cmd == "MDEL") {
        int index;
        if (iss >> index) MDEL(index);
        else cout << "�������� ������ �������: MDEL <index>" << endl;
    }
    else if (cmd == "MGET") {
        int index;
        if (iss >> index) MGET(index);
        else cout << "�������� ������ �������: MGET <index>" << endl;
    }
    else if (cmd == "FPUSH") {
        int value, position = -1;
        if (iss >> value) {
            if (iss >> position) FPUSH(value, position);
            else FPUSH(value);
        }
        else cout << "�������� ������ �������: FPUSH <value> [position]" << endl;
    }
    else if (cmd == "FDEL") {
        int value;
        if (iss >> value) FDEL(value);
        else cout << "�������� ������ �������: FDEL <value>" << endl;
    }
    else if (cmd == "FGET") {
        int index;
        if (iss >> index) FGET(index);
        else cout << "�������� ������ �������: FGET <index>" << endl;
    }
    else if (cmd == "LPUSH") {
        int value, position = -1;
        if (iss >> value) {
            if (iss >> position) LPUSH(value, position);
            else LPUSH(value);
        }
        else cout << "�������� ������ �������: LPUSH <value> [position]" << endl;
    }
    else if (cmd == "LDEL") {
        int value;
        if (iss >> value) LDEL(value);
        else cout << "�������� ������ �������: LDEL <value>" << endl;
    }
    else if (cmd == "LGET") {
        int index;
        if (iss >> index) LGET(index);
        else cout << "�������� ������ �������: LGET <index>" << endl;
    }
    else if (cmd == "QPUSH") {
        int value;
        if (iss >> value) QPUSH(value);
        else cout << "�������� ������ �������: QPUSH <value>" << endl;
    }
    else if (cmd == "QPOP") {
        QPOP();
    }
    else if (cmd == "QGET") {
        QGET();
    }
    else if (cmd == "SPUSH") {
        int value;
        if (iss >> value) SPUSH(value);
        else cout << "�������� ������ �������: SPUSH <value>" << endl;
    }
    else if (cmd == "SPOP") {
        SPOP();
    }
    else if (cmd == "SGET") {
        SGET();
    }
    else if (cmd == "TINSERT") {
        int value;
        if (iss >> value) TINSERT(value);
        else cout << "�������� ������ �������: TINSERT <value>" << endl;
    }
    else if (cmd == "TDEL") {
        int value;
        if (iss >> value) TDEL(value);
        else cout << "�������� ������ �������: TDEL <value>" << endl;
    }
    else if (cmd == "TGET") {
        int value;
        if (iss >> value) TGET(value);
        else cout << "�������� ������ �������: TGET <value>" << endl;
    }
    else if (cmd == "PRINT") {
        string structure;
        if (iss >> structure) PRINT(structure);
        else cout << "�������� ������ �������: PRINT <structure>" << endl;
    }
    else if (cmd == "SAVE_ALL") {
        SAVE_ALL();
    }
    else if (cmd == "LOAD_ALL") {
        LOAD_ALL();
    }
    else if (cmd == "CLEAR_ALL") {
        CLEAR_ALL();
    }
    else if (cmd == "EXIT" || cmd == "QUIT") {
        // �������������� ���������� ��� ������
        SAVE_ALL();
        exit(0);
    }
    else if (cmd == "HELP") {
        cout << "��������� �������:" << endl;
        cout << "MPUSH <value> - �������� � ������" << endl;
        cout << "MDEL <index> - ������� �� ������� �� �������" << endl;
        cout << "MGET <index> - �������� ������� ������� �� �������" << endl;
        cout << "FPUSH <value> [position] - �������� � ����������� ������" << endl;
        cout << "FDEL <value> - ������� �� ������������ ������ �� ��������" << endl;
        cout << "FGET <index> - �������� ������� ������������ ������ �� �������" << endl;
        cout << "LPUSH <value> [position] - �������� � ���������� ������" << endl;
        cout << "LDEL <value> - ������� �� ����������� ������ �� ��������" << endl;
        cout << "LGET <index> - �������� ������� ����������� ������ �� �������" << endl;
        cout << "QPUSH <value> - �������� � �������" << endl;
        cout << "QPOP - ������� �� �������" << endl;
        cout << "QGET - ���������� ������ ������� �������" << endl;
        cout << "SPUSH <value> - �������� � ����" << endl;
        cout << "SPOP - ������� �� �����" << endl;
        cout << "SGET - ���������� ������� ������� �����" << endl;
        cout << "TINSERT <value> - �������� � ������" << endl;
        cout << "TDEL <value> - ������� �� ������" << endl;
        cout << "TGET <value> - ����� � ������" << endl;
        cout << "PRINT <structure> - ������� ��������� (M,F,L,Q,S,T)" << endl;
        cout << "PRINT T_INORDER - ������� ������ Inorder" << endl;
        cout << "PRINT T_PREORDER - ������� ������ Preorder" << endl;
        cout << "PRINT T_POSTORDER - ������� ������ Postorder" << endl;
        cout << "PRINT T_BFS - ������� ������ BFS" << endl;
        cout << "PRINT <structure> - ������� ��������� (M,F,L,Q,S,T)" << endl;
        cout << "SAVE_ALL - ��������� ��� ������ � �����" << endl;
        cout << "LOAD_ALL - ��������� ��� ������ �� ������" << endl;
        cout << "CLEAR_ALL - �������� ��� ������" << endl;
        cout << "EXIT/QUIT - ����� (� ���������������)" << endl;

    }
    else {
        cout << "����������� �������. ������� HELP ��� ������ ������." << endl;
    }
}

#endif