#include<iostream>
#include"list.h"
using namespace std;

void addNode(ForwardList* flist, linkedList* target, const string& num, Position pos) {
    linkedList* newNode = new linkedList;
    newNode->node = num;
    newNode->next = nullptr;

    switch (pos) {
    case HEAD:
        newNode->next = flist->head;
        flist->head = newNode;
        break;

    case TAIL:
        if (flist->head == nullptr) {
            flist->head = newNode;
        }
        else {
            linkedList* current = flist->head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        break;

    case AFTER:
        if (target != nullptr) {
            newNode->next = target->next;
            target->next = newNode;
        }
        break;

    case BEFORE:
        if (target != nullptr) {
            if (target == flist->head) {
                newNode->next = flist->head;
                flist->head = newNode;
            }
            else {
                linkedList* current = flist->head;
                while (current->next != nullptr && current->next != target) {
                    current = current->next;
                }
                if (current->next == target) {
                    newNode->next = target;
                    current->next = newNode;
                }
            }
        }
        break;
    }
}

void deleteNode(ForwardList* flist, linkedList* target, const string& num, Position pos) {
    linkedList* toDelete;

    switch (pos) {
    case HEAD: // удаление начала
        if (flist->head != nullptr)
        {
            linkedList* temp = flist->head;
            flist->head = flist->head->next;
            delete temp;
        }
        break;

    case TAIL: // удаление хвоста 
        if (flist->head->next == nullptr) {
            delete flist->head;
            flist->head = nullptr;
        }
        else
        {
            linkedList* current = flist->head;
            while (current->next->next != nullptr) {
                current = current->next;
            }
            delete current->next;
            current->next = nullptr;
        }
        break;

    case AFTER: // удаление после узла target
        if (target != nullptr) {
            if (target->next != nullptr)
            {
                linkedList* toDelete = target->next;
                target->next = toDelete->next;
                delete toDelete;
            }
        }
        break;

    case BEFORE: // удаление до узла target
        if (target != nullptr) {
            // если удаление первого элемента  
            if (target == flist->head) {
                break;
            }

            else if (target != flist->head) {
                linkedList* previous = nullptr;
                linkedList* current = flist->head;

                while (current != target) {
                    previous = current;
                    current = current->next;
                }
                toDelete = previous;

                if (toDelete == flist->head) {
                    flist->head = target;
                }
                else {
                    linkedList* prevPrev = flist->head;
                    while (prevPrev->next != toDelete) {
                        prevPrev = prevPrev->next;
                    }
                    prevPrev->next = target;
                }

                delete toDelete;
            }
        }
        break;
    }
}

bool deleteNodeIndex(ForwardList* flist, const string& num) {
    linkedList* toDelete;
    linkedList* current = flist->head;
    if (flist->head == nullptr)
    {
        return 0;
    }
    else if (flist->head->node == num)
    {
        toDelete = flist->head;
        flist->head = flist->head->next;
        delete toDelete;
        return true;
    }
    else
    {
        while (current->next != nullptr)
        {
            toDelete = current->next;
            if (current->next->node == num)
            {
                current->next = current->next->next;
                delete toDelete;
                return true;
            }
            else
            {
                current = current->next;
            }
        }
        return false;
    }
}

bool findNodeIndex(ForwardList* flist, const string& num) {
    if (flist->head == nullptr) {
        return false;
    }

    if (flist->head->node == num) {
        return true;
    }

    linkedList* current = flist->head->next;
    while (current != nullptr) {
        if (current->node == num) {
            return true;
        }
        current = current->next;
    }

    return false;
}

void printList(const ForwardList& flist) {
    linkedList* current = flist.head;
    cout << "spisok: ";
    while (current != nullptr) {
        cout << current->node << " ";
        current = current->next;
    }
    cout << endl;
}

int countNodes(const ForwardList& flist) {
    int count = 0;
    linkedList* current = flist.head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

linkedList* getNodeByIndex(const ForwardList& flist, int index) {
    if (index < 0) return nullptr;

    linkedList* current = flist.head;
    int currentIndex = 0;

    while (current) {
        if (currentIndex == index) return current;
        current = current->next;
        currentIndex++;
    }

    return nullptr;
}

