#include<iostream>
#include"listTwo.h"
using namespace std;

void addNodeTwo(ForwardListTwo* flist, DoublyNode* target, int num, PositionTwo pos) {
    DoublyNode* newNode = new DoublyNode;
    newNode->node = num;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    switch (pos) {
    case HEADTwo: // ������� � ������
        newNode->next = flist->head;
        newNode->prev = nullptr;

        if (flist->head != nullptr)
        {
            flist->head->prev = newNode;
        }
        flist->head = newNode;

        if (flist->tail == nullptr)
        {
            flist->tail = newNode;
        }
        break;

    case TAILTwo: // ������� � �����
        newNode->next = nullptr;       // ����� ���� � ���������, ����� ���� ��� ������
        newNode->prev = flist->tail;   // ���������� � ������ �����


        if (flist->tail != nullptr) {
            flist->tail->next = newNode; // ������ ����� ������ ��������� �� ����� ����
        }

        flist->tail = newNode;          // ��������� ����� ������

        if (flist->head == nullptr) {
            flist->head = newNode;      // ���� ������ ��� ����, ������ ���� ����� ����
        }

        break;

    case AFTERTwo:
        if (target != nullptr) {
            newNode->next = target->next;
            newNode->prev = target;
            if (target->next != nullptr)
                target->next->prev = newNode;
            else
                flist->tail = newNode; // <-- �������� ���
            target->next = newNode;
        }
        break;


    case BEFORETwo: // ������� �� ���� target
        if (target != nullptr) {
            newNode->next = target;
            newNode->prev = target->prev;
            if (target->prev != nullptr) {
                target->prev->next = newNode;
            }
            else {
                flist->head = newNode;
            }
            target->prev = newNode;
        }
        break;
    }
}

void deleteNodeTwo(ForwardListTwo* flist, DoublyNode* target, int num, PositionTwo pos) {
    DoublyNode* toDelete = nullptr;

    switch (pos) {
    case HEADTwo: // �������� ������
        if (flist->head != nullptr) {
            toDelete = flist->head;
            flist->head = flist->head->next;
            if (flist->head != nullptr) {
                flist->head->prev = nullptr;
            }
            else {
                flist->tail = nullptr; // ���� ������ ���� ������
            }
            delete toDelete;
        }
        break;

    case TAILTwo: // �������� ������
        if (flist->tail != nullptr) {
            toDelete = flist->tail;
            flist->tail = flist->tail->prev;
            if (flist->tail != nullptr) {
                flist->tail->next = nullptr;
            }
            else {
                flist->head = nullptr; // ���� ������ ���� ������
            }
            delete toDelete;
        }
        break;

    case AFTERTwo: // �������� ����� ���� target
        if (target != nullptr && target->next != nullptr) {
            toDelete = target->next;
            target->next = toDelete->next;
            if (toDelete->next != nullptr) {
                toDelete->next->prev = target;
            }
            else {
                flist->tail = target; // ���� ������� ��������� ����
            }
            delete toDelete;
        }
        break;

    case BEFORETwo: // �������� ����� ����� target
        if (target != nullptr && target->prev != nullptr) {
            toDelete = target->prev;
            target->prev = toDelete->prev;
            if (toDelete->prev != nullptr) {
                toDelete->prev->next = target;
            }
            else {
                flist->head = target; // ���� ������� ������ ����
            }
            delete toDelete;
        }
        break;
    }
}

bool deleteNodeIndexTwo(ForwardListTwo* flist, int num) {
    if (flist->head == nullptr) return false;

    DoublyNode* current = flist->head;

    // ���� ���� � ������ ���������
    while (current != nullptr && current->node != num) {
        current = current->next;
    }

    if (current == nullptr) return false; // ���� �� ������

    // ������� current
    if (current->prev != nullptr)
        current->prev->next = current->next;
    else
        flist->head = current->next; // ���� ������� ������

    if (current->next != nullptr)
        current->next->prev = current->prev;
    else
        flist->tail = current->prev; // ���� ������� �����

    delete current;
    return true;
}

bool findNodeIndexTwo(ForwardListTwo* flist, int num) {
    DoublyNode* current = flist->head;
    while (current != nullptr) {
        if (current->node == num) return true;
        current = current->next;
    }
    return false;
}

void printListTwo(const ForwardListTwo& flist) {
    DoublyNode* current = flist.head;
    cout << "������: ";
    while (current != nullptr) {
        cout << current->node << " ";
        current = current->next;
    }
    cout << endl;
}

int countNodesTwo(const ForwardListTwo& flist) {
    int count = 0;
    DoublyNode* current = flist.head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

DoublyNode* getNodeByIndexTwo(ForwardListTwo& flist, int index) {
    if (index < 0) return nullptr;

    DoublyNode* current = flist.head;
    int currentIndex = 0;

    while (current != nullptr) {
        if (currentIndex == index) return current;
        current = current->next;
        currentIndex++;
    }

    return nullptr; // ������ �� ��������� ������
}


