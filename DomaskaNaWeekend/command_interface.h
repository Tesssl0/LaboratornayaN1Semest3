#ifndef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H

#include <iostream>
#include <sstream>
#include <string>
#include "file_operations.h"

using namespace std;

// Максимальное количество именованных структур
const int MAX_NAMED_STRUCTURES = 100;

// Структура для именованного стека
struct NamedStack {
    string name;
    Stack stack;
    bool used;

    NamedStack() : stack(100, true), used(false) {}
};

// Структура для именованной очереди
struct NamedQueue {
    string name;
    Queue queue;  // Используем обычную структуру, а не указатель
    bool used;

    NamedQueue() : used(false) {
        initQueue(&queue, true);  // Инициализируем очередь
    }
};

// Структура для именованного массива
struct NamedArray {
    string name;
    Array array;
    bool used;

    NamedArray() : used(false) {}
};

// Структура для именованного односвязного списка
struct NamedList {
    string name;
    ForwardList list;
    bool used;

    NamedList() : used(false) {
        list.head = nullptr;
    }
};

// Структура для именованного двусвязного списка
struct NamedListTwo {
    string name;
    ForwardListTwo list;
    bool used;

    NamedListTwo() : used(false) {
        list.head = nullptr;
        list.tail = nullptr;
    }
};

// Структура для именованного дерева
struct NamedTree {
    string name;
    fullBinaryTree tree;
    bool used;

    NamedTree() : used(false) {
        tree.root = nullptr;
    }
};

// Объявления именованных структур
extern NamedStack namedStacks[MAX_NAMED_STRUCTURES];
extern NamedQueue namedQueues[MAX_NAMED_STRUCTURES];
extern NamedArray namedArrays[MAX_NAMED_STRUCTURES];
extern NamedList namedLists[MAX_NAMED_STRUCTURES];
extern NamedListTwo namedListsTwo[MAX_NAMED_STRUCTURES];
extern NamedTree namedTrees[MAX_NAMED_STRUCTURES];

extern int namedStacksCount;
extern int namedQueuesCount;
extern int namedArraysCount;
extern int namedListsCount;
extern int namedListsTwoCount;
extern int namedTreesCount;

extern bool firstLoad;

void initGlobalStructures();

void LOAD_ALL_FROM(const std::string& filename);
void SAVE_ALL_TO(const std::string& filename);

// Функции для работы с именованными стеками
void NAMED_SPUSH(const string& stackName, const string& value);
void NAMED_SPOP(const string& stackName);
void NAMED_SGET(const string& stackName);
void NAMED_PRINT_STACK(const string& stackName);

// Функции для работы с именованными очередями
void NAMED_QPUSH(const string& queueName, const string& value);
void NAMED_QPOP(const string& queueName);
void NAMED_QGET(const string& queueName);
void NAMED_PRINT_QUEUE(const string& queueName);

// Функции для работы с именованными массивами
void NAMED_MPUSH(const string& arrayName, const string& value);
void NAMED_MDEL(const string& arrayName, int index);
void NAMED_MGET(const string& arrayName, int index);
void NAMED_MADDAT(const string& arrayName, int index, const string& value);
void NAMED_MSET(const string& arrayName, int index, const string& value);
void NAMED_MLENGTH(const string& arrayName);
void NAMED_MFIND(const string& arrayName, const string& value);
void NAMED_MCREATE(const string& arrayName);
void NAMED_PRINT_ARRAY(const string& arrayName);

// Функции для работы с именованными односвязными списками
void NAMED_FPUSH(const string& listName, const string& value, int position = -1);
void NAMED_FDEL(const string& listName, const string& value);
void NAMED_FGET(const string& listName, int index);
void NAMED_FFIND(const string& listName, const string& value);
void NAMED_FCOUNT(const string& listName);
void NAMED_PRINT_LIST(const string& listName);

// Новые функции для односвязных списков без switch case
void NAMED_FPUSH_HEAD(const string& listName, const string& value);
void NAMED_FPUSH_TAIL(const string& listName, const string& value);
void NAMED_FPUSH_AFTER(const string& listName, int targetIndex, const string& value);
void NAMED_FPUSH_BEFORE(const string& listName, int targetIndex, const string& value);

void NAMED_FPOP_HEAD(const string& listName);
void NAMED_FPOP_TAIL(const string& listName);
void NAMED_FPOP_AFTER(const string& listName, int targetIndex);
void NAMED_FPOP_BEFORE(const string& listName, int targetIndex);

// Функции для работы с именованными двусвязными списками
void NAMED_LPUSH(const string& listName, const string& value, int position = -1);
void NAMED_LDEL(const string& listName, const string& value);
void NAMED_LGET(const string& listName, int index);
void NAMED_LFIND(const string& listName, const string& value);
void NAMED_LCOUNT(const string& listName);
void NAMED_PRINT_LIST_TWO_REVERSE(const string& listName);
void NAMED_PRINT_LIST_TWO(const string& listName);

// Новые функции для двусвязных списков без switch case
void NAMED_LPUSH_HEAD(const string& listName, const string& value);
void NAMED_LPUSH_TAIL(const string& listName, const string& value);
void NAMED_LPUSH_AFTER(const string& listName, int targetIndex, const string& value);
void NAMED_LPUSH_BEFORE(const string& listName, int targetIndex, const string& value);

void NAMED_LPOP_HEAD(const string& listName);
void NAMED_LPOP_TAIL(const string& listName);
void NAMED_LPOP_AFTER(const string& listName, int targetIndex);
void NAMED_LPOP_BEFORE(const string& listName, int targetIndex);

// Функции для работы с именованными деревьями
void NAMED_TINSERT_BINARY(const string& treeName, const string& value);
void NAMED_TGET(const string& treeName, const string& value);
void NAMED_PRINT_TREE(const string& treeName);

// Универсальная функция PRINT
void PRINT(const string& structure);
void SAVE_ALL();
void LOAD_ALL();
void CLEAR_ALL();
void processCommand(const string& command);

// Вспомогательные функции для работы с именованными структурами
NamedStack* findStackByName(const string& name);
NamedQueue* findQueueByName(const string& name);
NamedArray* findArrayByName(const string& name);
NamedList* findListByName(const string& name);
NamedListTwo* findListTwoByName(const string& name);
NamedTree* findTreeByName(const string& name);
NamedStack* createNewStack(const string& name);
NamedQueue* createNewQueue(const string& name);
NamedArray* createNewArray(const string& name);
NamedList* createNewList(const string& name);
NamedListTwo* createNewListTwo(const string& name);
NamedTree* createNewTree(const string& name);

#endif