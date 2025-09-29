#include<iostream>
#include"listTwo.h"
using namespace std;

void addNodeTwo(ForwardListTwo* flist, DoublyNode* target, int num, PositionTwo pos) {
    DoublyNode* newNode = new DoublyNode;
    newNode->node = num;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    switch (pos) {
    case HEADTwo: // вставка в начало
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

    case TAILTwo: // вставка в хвост
        newNode->next = nullptr;       // новый узел — последний, после него нет ничего
        newNode->prev = flist->tail;   // предыдущий — старый хвост


        if (flist->tail != nullptr) {
            flist->tail->next = newNode; // старый хвост теперь указывает на новый узел
        }

        flist->tail = newNode;          // обновляем хвост списка

        if (flist->head == nullptr) {
            flist->head = newNode;      // если список был пуст, голова тоже новый узел
        }

        break;

    case AFTERTwo:
        if (target != nullptr) {
            newNode->next = target->next;
            newNode->prev = target;
            if (target->next != nullptr)
                target->next->prev = newNode;
            else
                flist->tail = newNode; // <-- добавьте это
            target->next = newNode;
        }
        break;


    case BEFORETwo: // вставка до узла target
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
    case HEADTwo: // удаление начала
        if (flist->head != nullptr) {
            toDelete = flist->head;
            flist->head = flist->head->next;
            if (flist->head != nullptr) {
                flist->head->prev = nullptr;
            }
            else {
                flist->tail = nullptr; // если список стал пустым
            }
            delete toDelete;
        }
        break;

    case TAILTwo: // удаление хвоста
        if (flist->tail != nullptr) {
            toDelete = flist->tail;
            flist->tail = flist->tail->prev;
            if (flist->tail != nullptr) {
                flist->tail->next = nullptr;
            }
            else {
                flist->head = nullptr; // если список стал пустым
            }
            delete toDelete;
        }
        break;

    case AFTERTwo: // удаление после узла target
        if (target != nullptr && target->next != nullptr) {
            toDelete = target->next;
            target->next = toDelete->next;
            if (toDelete->next != nullptr) {
                toDelete->next->prev = target;
            }
            else {
                flist->tail = target; // если удалили последний узел
            }
            delete toDelete;
        }
        break;

    case BEFORETwo: // удаление перед узлом target
        if (target != nullptr && target->prev != nullptr) {
            toDelete = target->prev;
            target->prev = toDelete->prev;
            if (toDelete->prev != nullptr) {
                toDelete->prev->next = target;
            }
            else {
                flist->head = target; // если удалили первый узел
            }
            delete toDelete;
        }
        break;
    }
}

bool deleteNodeIndexTwo(ForwardListTwo* flist, int num) {
    if (flist->head == nullptr) return false;

    DoublyNode* current = flist->head;

    // ищем узел с нужным значением
    while (current != nullptr && current->node != num) {
        current = current->next;
    }

    if (current == nullptr) return false; // узел не найден

    // удаляем current
    if (current->prev != nullptr)
        current->prev->next = current->next;
    else
        flist->head = current->next; // если удаляем голову

    if (current->next != nullptr)
        current->next->prev = current->prev;
    else
        flist->tail = current->prev; // если удаляем хвост

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
    cout << "Список: ";
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

    return nullptr; // индекс за пределами списка
}


