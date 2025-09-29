#ifndef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H

#include <iostream>
#include <sstream>
#include <string>
#include "file_operations.h"

using namespace std;

// Глобальные структуры данных
Array globalArray;
ForwardList globalForwardList;
ForwardListTwo globalForwardListTwo;
Queue<int> globalQueue(100, true);  // ТИХИЙ режим по умолчанию
Stack globalStack(100, true);       // ТИХИЙ режим по умолчанию
fullBinaryTree globalTree;

// Флаг для отслеживания первой загрузки
bool firstLoad = true;

// Инициализация глобальных структур
void initGlobalStructures() {
    init(globalArray);
    globalForwardList.head = nullptr;
    globalForwardListTwo.head = nullptr;
    globalForwardListTwo.tail = nullptr;
    globalTree.root = nullptr;
    firstLoad = true;
}

// Функции для работы с массивом
void MPUSH(int value) {
    add(globalArray, value);
    cout << "Добавлен элемент " << value << " в массив" << endl;
}

void MDEL(int index) {
    if (index >= 0 && index < globalArray.size) {
        int value = get(globalArray, index);
        remove(globalArray, index);
        cout << "Удален элемент " << value << " из массива по индексу " << index << endl;
    }
    else {
        cout << "Неверный индекс" << endl;
    }
}

int MGET(int index) {
    if (index >= 0 && index < globalArray.size) {
        int value = get(globalArray, index);
        cout << "Элемент по индексу " << index << ": " << value << endl;
        return value;
    }
    else {
        cout << "Неверный индекс" << endl;
        return -1;
    }
}

// Функции для работы с односвязным списком
void FPUSH(int value, int position = -1) {
    if (position == -1) {
        // Добавление в конец
        addNode(&globalForwardList, nullptr, value, TAIL);
    }
    else {
        // Добавление по индексу
        linkedList* target = getNodeByIndex(globalForwardList, position);
        if (target) {
            addNode(&globalForwardList, target, value, AFTER);
        }
        else {
            cout << "Неверная позиция" << endl;
            return;
        }
    }
    cout << "Добавлен элемент " << value << " в односвязный список" << endl;
}

void FDEL(int value) {
    if (deleteNodeIndex(&globalForwardList, value)) {
        cout << "Удален элемент " << value << " из односвязного списка" << endl;
    }
    else {
        cout << "Элемент не найден" << endl;
    }
}

int FGET(int index) {
    linkedList* node = getNodeByIndex(globalForwardList, index);
    if (node) {
        cout << "Элемент по индексу " << index << ": " << node->node << endl;
        return node->node;
    }
    else {
        cout << "Неверный индекс" << endl;
        return -1;
    }
}

// Функции для работы с двусвязным списком
void LPUSH(int value, int position = -1) {
    if (position == -1) {
        // Добавление в конец
        addNodeTwo(&globalForwardListTwo, nullptr, value, TAILTwo);
    }
    else {
        // Добавление по индексу
        DoublyNode* target = getNodeByIndexTwo(globalForwardListTwo, position);
        if (target) {
            addNodeTwo(&globalForwardListTwo, target, value, AFTERTwo);
        }
        else {
            cout << "Неверная позиция" << endl;
            return;
        }
    }
    cout << "Добавлен элемент " << value << " в двусвязный список" << endl;
}

void LDEL(int value) {
    if (deleteNodeIndexTwo(&globalForwardListTwo, value)) {
        cout << "Удален элемент " << value << " из двусвязного списка" << endl;
    }
    else {
        cout << "Элемент не найден" << endl;
    }
}

int LGET(int index) {
    DoublyNode* node = getNodeByIndexTwo(globalForwardListTwo, index);
    if (node) {
        cout << "Элемент по индексу " << index << ": " << node->node << endl;
        return node->node;
    }
    else {
        cout << "Неверный индекс" << endl;
        return -1;
    }
}

// Функции для работы с очередью
void QPUSH(int value) {
    globalQueue.enqueue(value);
    cout << "Добавлен элемент " << value << " в очередь" << endl;
}

int QPOP() {
    int value = globalQueue.dequeue();
    if (value != int()) {
        cout << "Извлечен элемент " << value << " из очереди" << endl;
    }
    return value;
}

int QGET() {
    int value = globalQueue.front();
    if (value != int()) {
        cout << "Первый элемент очереди: " << value << endl;
    }
    return value;
}

// Функции для работы со стеком
void SPUSH(int value) {
    globalStack.push(value);
    cout << "Добавлен элемент " << value << " в стек" << endl;
}

void SPOP() {
    if (!globalStack.isEmpty()) {
        int value = globalStack.top();
        globalStack.pop();
        cout << "Извлечен элемент " << value << " из стека" << endl;
    }
}

int SGET() {
    if (!globalStack.isEmpty()) {
        int value = globalStack.top();
        cout << "Верхний элемент стека: " << value << endl;
        return value;
    }
    return -1;
}

// Функции для работы с деревом
void TINSERT(int value) {
    insert(&globalTree, value);
    cout << "Добавлен элемент " << value << " в дерево" << endl;
}

void TDEL(int value) {
    deleteNode(&globalTree, value);
}

int TGET(int value) {
    Node* node = BFS(&globalTree, value);
    if (node) {
        cout << "Найден элемент " << value << " в дереве" << endl;
        return node->data;
    }
    else {
        cout << "Элемент " << value << " не найден в дереве" << endl;
        return -1;
    }
}

// Универсальная функция PRINT
// Универсальная функция PRINT
void PRINT(const string& structure) {
    if (structure == "M") {
        cout << "Массив: ";
        print(globalArray);
    }
    else if (structure == "F") {
        cout << "Односвязный список: ";
        printList(globalForwardList);
    }
    else if (structure == "L") {
        cout << "Двусвязный список: ";
        printListTwo(globalForwardListTwo);
    }
    else if (structure == "Q") {
        cout << "Очередь: ";
        if (globalQueue.isEmpty()) {
            cout << "пуста" << endl;
        }
        else {
            // Простой вывод без копирования
            cout << "[первый: " << globalQueue.front() << ", размер: ";

            // Подсчет размера очереди
            Queue<int> tempQueue(100, true);
            int size = 0;
            while (!globalQueue.isEmpty()) {
                int value = globalQueue.dequeue();
                tempQueue.enqueue(value);
                size++;
            }

            // Восстанавливаем очередь
            while (!tempQueue.isEmpty()) {
                globalQueue.enqueue(tempQueue.dequeue());
            }

            cout << size << " элементов]" << endl;
        }
    }
    else if (structure == "S") {
        cout << "Стек: ";
        if (globalStack.isEmpty()) {
            cout << "пуст" << endl;
        }
        else {
            // Простой вывод без копирования - только верхний элемент и размер
            cout << "[верхний: " << globalStack.top() << ", размер: ";

            // Подсчет размера стека
            Stack tempStack(100, true);
            int size = 0;
            while (!globalStack.isEmpty()) {
                int value = globalStack.top();
                tempStack.push(value);
                globalStack.pop();
                size++;
            }

            // Восстанавливаем стек
            while (!tempStack.isEmpty()) {
                globalStack.push(tempStack.top());
                tempStack.pop();
            }

            cout << size << " элементов]" << endl;
        }
    }
    else if (structure == "T") {
        // Вывод дерева разными способами
        cout << "=== ДЕРЕВО ===" << endl;
        cout << "Inorder (симметричный): ";
        inorder(globalTree.root);
        cout << endl;

        cout << "Preorder (прямой): ";
        preorder(globalTree.root);
        cout << endl;

        cout << "Postorder (обратный): ";
        postorder(globalTree.root);
        cout << endl;

        printBFS(&globalTree);
    }
    else if (structure == "T_INORDER") {
        cout << "Дерево (Inorder): ";
        inorder(globalTree.root);
        cout << endl;
    }
    else if (structure == "T_PREORDER") {
        cout << "Дерево (Preorder): ";
        preorder(globalTree.root);
        cout << endl;
    }
    else if (structure == "T_POSTORDER") {
        cout << "Дерево (Postorder): ";
        postorder(globalTree.root);
        cout << endl;
    }
    else if (structure == "T_BFS") {
        printBFS(&globalTree);
    }
    else {
        cout << "Неизвестная структура: " << structure << endl;
    }
}

// Функция сохранения всех данных
void SAVE_ALL() {
    saveArrayToFile(globalArray, "array_data.txt");
    saveForwardListToFile(globalForwardList, "forward_list_data.txt");
    saveForwardListTwoToFile(globalForwardListTwo, "forward_list_two_data.txt");
    saveQueueToFile(globalQueue, "queue_data.txt");
    saveStackToFile(globalStack, "stack_data.txt");
    saveTreeToFile(&globalTree, "tree_data.txt");
    cout << "Все данные сохранены в файлы" << endl;
}

// Функция загрузки всех данных
void LOAD_ALL() {
    // При первой загрузке просто загружаем данные
    if (firstLoad) {
        loadArrayFromFile(globalArray, "array_data.txt");
        loadForwardListFromFile(globalForwardList, "forward_list_data.txt");
        loadForwardListTwoFromFile(globalForwardListTwo, "forward_list_two_data.txt");
        loadQueueFromFile(globalQueue, "queue_data.txt");
        loadStackFromFile(globalStack, "stack_data.txt");
        loadTreeFromFile(&globalTree, "tree_data.txt");
        firstLoad = false;
        cout << "Все данные загружены из файлов" << endl;
    }
    else {
        // При повторной загрузке спрашиваем подтверждение
        cout << "Текущие данные будут потеряны. Продолжить? (y/n): ";
        string answer;
        getline(cin, answer);
        if (answer == "y" || answer == "Y") {
            // Очищаем текущие данные
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

            // Загружаем новые данные
            loadArrayFromFile(globalArray, "array_data.txt");
            loadForwardListFromFile(globalForwardList, "forward_list_data.txt");
            loadForwardListTwoFromFile(globalForwardListTwo, "forward_list_two_data.txt");
            loadQueueFromFile(globalQueue, "queue_data.txt");
            loadStackFromFile(globalStack, "stack_data.txt");
            loadTreeFromFile(&globalTree, "tree_data.txt");
            cout << "Все данные загружены из файлов" << endl;
        }
        else {
            cout << "Загрузка отменена" << endl;
        }
    }
}

// Функция очистки всех данных
void CLEAR_ALL() {
    // Очищаем структуры в памяти
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

    cout << "Все данные очищены из памяти" << endl;
}

// Интерфейс командной строки
void processCommand(const string& command) {
    istringstream iss(command);
    string cmd;
    iss >> cmd;

    // Проверка команд через if-else цепочку вместо map
    if (cmd == "MPUSH") {
        int value;
        if (iss >> value) MPUSH(value);
        else cout << "Неверный формат команды: MPUSH <value>" << endl;
    }
    else if (cmd == "MDEL") {
        int index;
        if (iss >> index) MDEL(index);
        else cout << "Неверный формат команды: MDEL <index>" << endl;
    }
    else if (cmd == "MGET") {
        int index;
        if (iss >> index) MGET(index);
        else cout << "Неверный формат команды: MGET <index>" << endl;
    }
    else if (cmd == "FPUSH") {
        int value, position = -1;
        if (iss >> value) {
            if (iss >> position) FPUSH(value, position);
            else FPUSH(value);
        }
        else cout << "Неверный формат команды: FPUSH <value> [position]" << endl;
    }
    else if (cmd == "FDEL") {
        int value;
        if (iss >> value) FDEL(value);
        else cout << "Неверный формат команды: FDEL <value>" << endl;
    }
    else if (cmd == "FGET") {
        int index;
        if (iss >> index) FGET(index);
        else cout << "Неверный формат команды: FGET <index>" << endl;
    }
    else if (cmd == "LPUSH") {
        int value, position = -1;
        if (iss >> value) {
            if (iss >> position) LPUSH(value, position);
            else LPUSH(value);
        }
        else cout << "Неверный формат команды: LPUSH <value> [position]" << endl;
    }
    else if (cmd == "LDEL") {
        int value;
        if (iss >> value) LDEL(value);
        else cout << "Неверный формат команды: LDEL <value>" << endl;
    }
    else if (cmd == "LGET") {
        int index;
        if (iss >> index) LGET(index);
        else cout << "Неверный формат команды: LGET <index>" << endl;
    }
    else if (cmd == "QPUSH") {
        int value;
        if (iss >> value) QPUSH(value);
        else cout << "Неверный формат команды: QPUSH <value>" << endl;
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
        else cout << "Неверный формат команды: SPUSH <value>" << endl;
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
        else cout << "Неверный формат команды: TINSERT <value>" << endl;
    }
    else if (cmd == "TDEL") {
        int value;
        if (iss >> value) TDEL(value);
        else cout << "Неверный формат команды: TDEL <value>" << endl;
    }
    else if (cmd == "TGET") {
        int value;
        if (iss >> value) TGET(value);
        else cout << "Неверный формат команды: TGET <value>" << endl;
    }
    else if (cmd == "PRINT") {
        string structure;
        if (iss >> structure) PRINT(structure);
        else cout << "Неверный формат команды: PRINT <structure>" << endl;
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
        // Автоматическое сохранение при выходе
        SAVE_ALL();
        exit(0);
    }
    else if (cmd == "HELP") {
        cout << "Доступные команды:" << endl;
        cout << "MPUSH <value> - добавить в массив" << endl;
        cout << "MDEL <index> - удалить из массива по индексу" << endl;
        cout << "MGET <index> - получить элемент массива по индексу" << endl;
        cout << "FPUSH <value> [position] - добавить в односвязный список" << endl;
        cout << "FDEL <value> - удалить из односвязного списка по значению" << endl;
        cout << "FGET <index> - получить элемент односвязного списка по индексу" << endl;
        cout << "LPUSH <value> [position] - добавить в двусвязный список" << endl;
        cout << "LDEL <value> - удалить из двусвязного списка по значению" << endl;
        cout << "LGET <index> - получить элемент двусвязного списка по индексу" << endl;
        cout << "QPUSH <value> - добавить в очередь" << endl;
        cout << "QPOP - извлечь из очереди" << endl;
        cout << "QGET - посмотреть первый элемент очереди" << endl;
        cout << "SPUSH <value> - добавить в стек" << endl;
        cout << "SPOP - извлечь из стека" << endl;
        cout << "SGET - посмотреть верхний элемент стека" << endl;
        cout << "TINSERT <value> - добавить в дерево" << endl;
        cout << "TDEL <value> - удалить из дерева" << endl;
        cout << "TGET <value> - найти в дереве" << endl;
        cout << "PRINT <structure> - вывести структуру (M,F,L,Q,S,T)" << endl;
        cout << "PRINT T_INORDER - вывести дерево Inorder" << endl;
        cout << "PRINT T_PREORDER - вывести дерево Preorder" << endl;
        cout << "PRINT T_POSTORDER - вывести дерево Postorder" << endl;
        cout << "PRINT T_BFS - вывести дерево BFS" << endl;
        cout << "PRINT <structure> - вывести структуру (M,F,L,Q,S,T)" << endl;
        cout << "SAVE_ALL - сохранить все данные в файлы" << endl;
        cout << "LOAD_ALL - загрузить все данные из файлов" << endl;
        cout << "CLEAR_ALL - очистить все данные" << endl;
        cout << "EXIT/QUIT - выход (с автосохранением)" << endl;

    }
    else {
        cout << "Неизвестная команда. Введите HELP для списка команд." << endl;
    }
}

#endif