#include"list.h"
#include<iostream>
using namespace std;

void addNodeHead(ForwardList* flist, const string& num) {
    linkedList* newNode = new linkedList;
    newNode->node = num;
    newNode->next = flist->head;
    flist->head = newNode;
}

void addNodeTail(ForwardList* flist, const string& num) {
    linkedList* newNode = new linkedList;
    newNode->node = num;
    newNode->next = nullptr;

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
}

void addNodeAfter(ForwardList* flist, linkedList* target, const string& num) {
    if (target != nullptr) {
        linkedList* newNode = new linkedList;
        newNode->node = num;
        newNode->next = nullptr;

        // Поиск target в списке с помощью цикла
        linkedList* current = flist->head;
        while (current != nullptr) {
            if (current == target) {
                // Найден target, вставляем после него
                newNode->next = current->next;
                current->next = newNode;
                return;
            }
            current = current->next;
        }

        
        delete newNode;
    }
}

void addNodeBefore(ForwardList* flist, linkedList* target, const string& num) {
    if (target != nullptr) {
        if (target == flist->head) {
            linkedList* newNode = new linkedList;
            newNode->node = num;
            newNode->next = flist->head;
            flist->head = newNode;
        }
        else {
            linkedList* current = flist->head;
            while (current->next != nullptr && current->next != target) {
                current = current->next;
            }
            if (current->next == target) {
                linkedList* newNode = new linkedList;
                newNode->node = num;
                newNode->next = target;
                current->next = newNode;
            }
        }
    }
}

void deleteNodeHead(ForwardList* flist) {
    if (flist->head != nullptr) {
        linkedList* temp = flist->head;
        flist->head = flist->head->next;
        delete temp;
    }
}

void deleteNodeTail(ForwardList* flist) {
    if (flist->head == nullptr) return;

    if (flist->head->next == nullptr) {
        delete flist->head;
        flist->head = nullptr;
    }
    else {
        linkedList* current = flist->head;
        while (current->next->next != nullptr) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }
}

void deleteNodeAfter(ForwardList* flist, linkedList* target) {
    if (target != nullptr && target->next != nullptr && flist->head != nullptr) {
        // Проверяем, что target действительно в списке
        linkedList* current = flist->head;
        bool targetFound = false;

        while (current != nullptr) {
            if (current == target) {
                targetFound = true;
                break;
            }
            current = current->next;
        }

        if (targetFound) {
            linkedList* toDelete = target->next;
            target->next = toDelete->next;
            delete toDelete;
        }
    }
}

void deleteNodeBefore(ForwardList* flist, linkedList* target) {
    if (target != nullptr && target != flist->head && flist->head != nullptr) {
        // Ищем узел перед target
        linkedList* prev = nullptr;
        linkedList* current = flist->head;

        while (current != nullptr && current != target) {
            prev = current;
            current = current->next;
        }

        // Если нашли target и есть предыдущий узел
        if (current == target && prev != nullptr) {
            // Теперь ищем узел перед prev
            linkedList* prevPrev = flist->head;
            while (prevPrev != nullptr && prevPrev->next != prev) {
                prevPrev = prevPrev->next;
            }

            if (prevPrev != nullptr) {
                prevPrev->next = target;
                delete prev;
            }
        }
    }
}

bool deleteNodeIndex(ForwardList* flist, const string& num) {
    if (flist->head == nullptr) {
        return false;
    }

    // Специальный случай: удаление головы
    if (flist->head->node == num) {
        linkedList* toDelete = flist->head;
        flist->head = flist->head->next;
        delete toDelete;
        return true;
    }

    // Поиск элемента с помощью цикла
    linkedList* current = flist->head;
    while (current->next != nullptr) {
        if (current->next->node == num) {
            linkedList* toDelete = current->next;
            current->next = current->next->next;
            delete toDelete;
            return true;
        }
        current = current->next;
    }

    return false;
}


void deleteNode(ForwardList* flist, linkedList* target, const string& num, Position pos) {
    if (pos == HEAD) {
        deleteNodeHead(flist);
    }
    else if (pos == TAIL) {
        deleteNodeTail(flist);
    }
    else if (pos == AFTER) {
        deleteNodeAfter(flist, target);
    }
    else if (pos == BEFORE) {
        deleteNodeBefore(flist, target);
    }
}

bool deleteNod(ForwardList* flist, const string& num) {
    linkedList* toDelete;
    linkedList* current = flist->head;

    if (flist->head == nullptr) {
        return false;
    }
    else if (flist->head->node == num) {
        toDelete = flist->head;
        flist->head = flist->head->next;
        delete toDelete;
        return true;
    }
    else {
        while (current->next != nullptr) {
            toDelete = current->next;
            if (current->next->node == num) {
                current->next = current->next->next;
                delete toDelete;
                return true;
            }
            else {
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
    cout << "Список: ";
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

