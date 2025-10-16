#include "command_interface.h"
#include <iostream>
#include <sstream>
#include <string>
#include "fullBinaryTree.h" 
using namespace std;

// Именованные структуры
NamedStack namedStacks[MAX_NAMED_STRUCTURES];
NamedQueue namedQueues[MAX_NAMED_STRUCTURES];
NamedArray namedArrays[MAX_NAMED_STRUCTURES];
NamedList namedLists[MAX_NAMED_STRUCTURES];
NamedListTwo namedListsTwo[MAX_NAMED_STRUCTURES];
NamedTree namedTrees[MAX_NAMED_STRUCTURES];

int namedStacksCount = 0;
int namedQueuesCount = 0;
int namedArraysCount = 0;
int namedListsCount = 0;
int namedListsTwoCount = 0;
int namedTreesCount = 0;

bool firstLoad = true;

void initializeSystem() {
    initGlobalStructures();
    if (firstLoad) {
        LOAD_ALL_FROM("named_data");  // Используем новую функцию
        firstLoad = false;
    }
}

// Вспомогательные функции для работы с именованными структурами
NamedStack* findStackByName(const string& name) {
    for (int i = 0; i < namedStacksCount; i++) {
        if (namedStacks[i].used && namedStacks[i].name == name) {
            return &namedStacks[i];
        }
    }
    return nullptr;
}

NamedQueue* findQueueByName(const string& name) {
    for (int i = 0; i < namedQueuesCount; i++) {
        if (namedQueues[i].used && namedQueues[i].name == name) {
            return &namedQueues[i];
        }
    }
    return nullptr;
}

NamedArray* findArrayByName(const string& name) {
    for (int i = 0; i < namedArraysCount; i++) {
        if (namedArrays[i].used && namedArrays[i].name == name) {
            return &namedArrays[i];
        }
    }
    return nullptr;
}

NamedList* findListByName(const string& name) {
    for (int i = 0; i < namedListsCount; i++) {
        if (namedLists[i].used && namedLists[i].name == name) {
            return &namedLists[i];
        }
    }
    return nullptr;
}

NamedListTwo* findListTwoByName(const string& name) {
    for (int i = 0; i < namedListsTwoCount; i++) {
        if (namedListsTwo[i].used && namedListsTwo[i].name == name) {
            return &namedListsTwo[i];
        }
    }
    return nullptr;
}

NamedTree* findTreeByName(const string& name) {
    for (int i = 0; i < namedTreesCount; i++) {
        if (namedTrees[i].used && namedTrees[i].name == name) {
            return &namedTrees[i];
        }
    }
    return nullptr;
}

NamedStack* createNewStack(const string& name) {
    NamedStack* existing = findStackByName(name);
    if (existing) {
        cout << "Стек " << name << " уже существует!" << endl;
        return existing;
    }

    if (namedStacksCount >= MAX_NAMED_STRUCTURES) {
        cout << "Достигнут лимит именованных стеков!" << endl;
        return nullptr;
    }

    namedStacks[namedStacksCount].name = name;
    namedStacks[namedStacksCount].used = true;
    namedStacks[namedStacksCount].stack.arr = new string[100];
    namedStacks[namedStacksCount].stack.capacity = 100;
    namedStacks[namedStacksCount].stack.topIndex = -1;
    namedStacks[namedStacksCount].stack.silent = true;

    // Инициализируем массив
    for (int i = 0; i < 100; i++) {
        namedStacks[namedStacksCount].stack.arr[i] = "";
    }

    return &namedStacks[namedStacksCount++];
}

NamedQueue* createNewQueue(const string& name) {
    NamedQueue* existing = findQueueByName(name);
    if (existing) {
        cout << "Очередь " << name << " уже существует!" << endl;
        return existing;
    }

    if (namedQueuesCount >= MAX_NAMED_STRUCTURES) {
        cout << "Достигнут лимит именованных очередей!" << endl;
        return nullptr;
    }

    // Инициализируем очередь
    namedQueues[namedQueuesCount].name = name;
    namedQueues[namedQueuesCount].used = true;
    initQueue(&namedQueues[namedQueuesCount].queue, true);

    
    return &namedQueues[namedQueuesCount++];
}

NamedArray* createNewArray(const string& name) {
    NamedArray* existing = findArrayByName(name);
    if (existing) {
        cout << "Массив " << name << " уже существует!" << endl;
        return existing;
    }

    if (namedArraysCount >= MAX_NAMED_STRUCTURES) {
        cout << "Достигнут лимит именованных массивов!" << endl;
        return nullptr;
    }

    namedArrays[namedArraysCount].name = name;
    namedArrays[namedArraysCount].used = true;
    init(namedArrays[namedArraysCount].array);

    cout << "Создан новый массив: " << name << endl;
    return &namedArrays[namedArraysCount++];
}

NamedList* createNewList(const string& name) {
    NamedList* existing = findListByName(name);
    if (existing) {
        cout << "Односвязный список " << name << " уже существует!" << endl;
        return existing;
    }

    if (namedListsCount >= MAX_NAMED_STRUCTURES) {
        cout << "Достигнут лимит именованных односвязных списков!" << endl;
        return nullptr;
    }

    namedLists[namedListsCount].name = name;
    namedLists[namedListsCount].used = true;
    namedLists[namedListsCount].list.head = nullptr;

    cout << "Создан новый односвязный список: " << name << endl;
    return &namedLists[namedListsCount++];
}

NamedListTwo* createNewListTwo(const string& name) {
    NamedListTwo* existing = findListTwoByName(name);
    if (existing) {
        cout << "Двусвязный список " << name << " уже существует!" << endl;
        return existing;
    }

    if (namedListsTwoCount >= MAX_NAMED_STRUCTURES) {
        cout << "Достигнут лимит именованных двусвязных списков!" << endl;
        return nullptr;
    }

    namedListsTwo[namedListsTwoCount].name = name;
    namedListsTwo[namedListsTwoCount].used = true;
    namedListsTwo[namedListsTwoCount].list.head = nullptr;
    namedListsTwo[namedListsTwoCount].list.tail = nullptr;

    cout << "Создан новый двусвязный список: " << name << endl;
    return &namedListsTwo[namedListsTwoCount++];
}

NamedTree* createNewTree(const string& name) {
    NamedTree* existing = findTreeByName(name);
    if (existing) {
        cout << "Дерево " << name << " уже существует!" << endl;
        return existing;
    }

    if (namedTreesCount >= MAX_NAMED_STRUCTURES) {
        cout << "Достигнут лимит именованных деревьев!" << endl;
        return nullptr;
    }

    namedTrees[namedTreesCount].name = name;
    namedTrees[namedTreesCount].used = true;
    namedTrees[namedTreesCount].tree.root = nullptr;

    cout << "Создано новое дерево: " << name << endl;
    return &namedTrees[namedTreesCount++];
}

// Функции для работы с именованными стеками
void NAMED_SPUSH(const string& stackName, const string& value) {
    NamedStack* stack = findStackByName(stackName);
    if (!stack) {
        stack = createNewStack(stackName);
        if (!stack) return;
    }
    stack->stack.push(value);
    cout << "Добавлен элемент " << value << " в стек " << stackName << endl;
}

void NAMED_SPOP(const string& stackName) {
    NamedStack* stack = findStackByName(stackName);
    if (stack && !stack->stack.isEmpty()) {
        string value = stack->stack.top();
        stack->stack.pop();
        cout << "Извлечен элемент " << value << " из стека " << stackName << endl;
    }
    else {
        cout << "Стек " << stackName << " не найден или пуст" << endl;
    }
}

void NAMED_SGET(const string& stackName) {
    NamedStack* stack = findStackByName(stackName);
    if (stack && !stack->stack.isEmpty()) {
        string value = stack->stack.top();
        cout << "Верхний элемент стека " << stackName << ": " << value << endl;
    }
    else {
        cout << "Стек " << stackName << " не найден или пуст" << endl;
    }
}

void NAMED_PRINT_STACK(const string& stackName) {
    NamedStack* namedStack = findStackByName(stackName);
    if (!namedStack) {
        cout << "Стек " << stackName << " не найден" << endl;
        return;
    }

    if (namedStack->stack.isEmpty()) {
        cout << "Стек " << stackName << ": пуст" << endl;
        return;
    }

    cout << "Стек " << stackName << ": (нижний -> верхний): ";

    Stack tempStack(100, true); // временный стек
    // Переносим элементы в tempStack (реверс)
    while (!namedStack->stack.isEmpty()) {
        tempStack.push(namedStack->stack.top());
        namedStack->stack.pop();
    }

    // Выводим элементы и сразу возвращаем в исходный стек
    Stack restoreStack(100, true);
    while (!tempStack.isEmpty()) {
        string val = tempStack.top();
        cout << val << " ";
        restoreStack.push(val);          // для восстановления исходного стека
        tempStack.pop();
    }

    // Восстанавливаем исходный стек
    while (!restoreStack.isEmpty()) {
        namedStack->stack.push(restoreStack.top());
        restoreStack.pop();
    }

    cout << endl;
}

void NAMED_QPUSH(const string& queueName, const string& value) {
    NamedQueue* queue = findQueueByName(queueName);
    if (!queue) {
        queue = createNewQueue(queueName);
        if (!queue) return;
    }
    enqueue(&queue->queue, value);  // Используем & для передачи указателя
    cout << "Добавлен элемент " << value << " в очередь " << queueName << endl;
}

void NAMED_QPOP(const string& queueName) {
    NamedQueue* queue = findQueueByName(queueName);
    if (queue && !isEmpty(&queue->queue)) {
        string value = dequeue(&queue->queue);
        cout << "Извлечен элемент " << value << " из очереди " << queueName << endl;
    }
    else {
        cout << "Очередь " << queueName << " не найдена или пуста" << endl;
    }
}

void NAMED_QGET(const string& queueName) {
    NamedQueue* queue = findQueueByName(queueName);
    if (queue && !isEmpty(&queue->queue)) {
        string value = front(&queue->queue);
        cout << "Первый элемент очереди " << queueName << ": " << value << endl;
    }
    else {
        cout << "Очередь " << queueName << " не найдена или пуста" << endl;
    }
}

// === НОВЫЕ КОМАНДЫ ДЛЯ МАССИВОВ ===

void NAMED_MADDAT(const string& arrayName, int index, const string& value) {
    NamedArray* array = findArrayByName(arrayName);
    if (array) {
        if (index >= 0 && index <= array->array.size) {
            addAt(array->array, index, value);
            cout << "Добавлен элемент " << value << " в массив " << arrayName << " по индексу " << index << endl;
        }
        else {
            cout << "Неверный индекс" << endl;
        }
    }
    else {
        cout << "Массив " << arrayName << " не найден" << endl;
    }
}

void NAMED_MSET(const string& arrayName, int index, const string& value) {
    NamedArray* array = findArrayByName(arrayName);
    if (array) {
        if (index >= 0 && index < array->array.size) {
            set(array->array, index, value);
            cout << "Заменен элемент по индексу " << index << " на значение " << value << " в массиве " << arrayName << endl;
        }
        else {
            cout << "Неверный индекс" << endl;
        }
    }
    else {
        cout << "Массив " << arrayName << " не найден" << endl;
    }
}

void NAMED_MLENGTH(const string& arrayName) {
    NamedArray* array = findArrayByName(arrayName);
    if (array) {
        int len = length(array->array);
        cout << "Длина массива " << arrayName << ": " << len << " элементов" << endl;
    }
    else {
        cout << "Массив " << arrayName << " не найден" << endl;
    }
}

void NAMED_MFIND(const string& arrayName, const string& value) {
    NamedArray* array = findArrayByName(arrayName);
    if (array) {
        int index = findInArray(array->array, value);
        if (index != -1) {
            cout << "Элемент " << value << " найден в массиве " << arrayName << " по индексу " << index << endl;
        }
        else {
            cout << "Элемент " << value << " не найден в массиве " << arrayName << endl;
        }
    }
    else {
        cout << "Массив " << arrayName << " не найден" << endl;
    }
}

void NAMED_MCREATE(const string& arrayName) {
    NamedArray* array = findArrayByName(arrayName);
    if (!array) {
        array = createNewArray(arrayName);
        if (array) {
            cout << "Массив " << arrayName << " создан" << endl;
        }
    }
    else {
        cout << "Массив " << arrayName << " уже существует" << endl;
    }
}

void NAMED_PRINT_QUEUE(const string& queueName) {
    NamedQueue* queue = findQueueByName(queueName);
    if (!queue) {
        cout << "Очередь " << queueName << " не найдена" << endl;
        return;
    }

    if (isEmpty(&queue->queue)) {
        cout << "Очередь " << queueName << ": пуста" << endl;
    }
    else {
        // Создаем временную очередь для вывода
        Queue tempQueue;
        initQueue(&tempQueue, true);

        cout << "Очередь " << queueName << ": (первый -> последний): ";

        // Перемещаем элементы во временную очередь и выводим
        while (!isEmpty(&queue->queue)) {
            string value = dequeue(&queue->queue);
            cout << value << " ";
            enqueue(&tempQueue, value);
        }

        cout << endl;

        // Возвращаем элементы обратно
        while (!isEmpty(&tempQueue)) {
            string value = dequeue(&tempQueue);
            enqueue(&queue->queue, value);
        }

        // Очищаем временную очередь
        clearQueue(&tempQueue);
    }
}
// === НОВЫЕ КОМАНДЫ ДЛЯ ОДНОСВЯЗНЫХ СПИСКОВ ===

void NAMED_FFIND(const string& listName, const string& value) {
    NamedList* list = findListByName(listName);
    if (list) {
        if (findNodeIndex(&list->list, value)) {
            cout << "Элемент " << value << " найден в списке " << listName << endl;
        }
        else {
            cout << "Элемент " << value << " не найден в списке " << listName << endl;
        }
    }
    else {
        cout << "Список " << listName << " не найден" << endl;
    }
}

void NAMED_FCOUNT(const string& listName) {
    NamedList* list = findListByName(listName);
    if (list) {
        int count = countNodes(list->list);
        cout << "Количество элементов в списке " << listName << ": " << count << endl;
    }
    else {
        cout << "Список " << listName << " не найден" << endl;
    }
}

// === НОВЫЕ КОМАНДЫ ДЛЯ ДВУСВЯЗНЫХ СПИСКОВ ===

void NAMED_LFIND(const string& listName, const string& value) {
    NamedListTwo* list = findListTwoByName(listName);
    if (list) {
        if (findNodeIndexTwo(&list->list, value)) {
            cout << "Элемент " << value << " найден в списке " << listName << endl;
        }
        else {
            cout << "Элемент " << value << " не найден в списке " << listName << endl;
        }
    }
    else {
        cout << "Список " << listName << " не найден" << endl;
    }
}

void NAMED_LCOUNT(const string& listName) {
    NamedListTwo* list = findListTwoByName(listName);
    if (list) {
        int count = countNodesTwo(list->list);
        cout << "Количество элементов в списке " << listName << ": " << count << endl;
    }
    else {
        cout << "Список " << listName << " не найден" << endl;
    }
}

void NAMED_PRINT_LIST_TWO_REVERSE(const string& listName) {
    NamedListTwo* list = findListTwoByName(listName);
    if (!list) {
        cout << "Двусвязный список " << listName << " не найден" << endl;
        return;
    }

    cout << "Двусвязный список " << listName << " (обратный порядок): ";
    DoublyNode* current = list->list.tail;
    while (current != nullptr) {
        cout << current->node << " ";
        current = current->prev;
    }
    cout << endl;
}

// === СИСТЕМНЫЕ КОМАНДЫ ===

void LIST_STRUCTURES() {
    cout << "=== ИМЕНОВАННЫЕ СТРУКТУРЫ ===" << endl;

    cout << "Стеки (" << namedStacksCount << "): ";
    for (int i = 0; i < namedStacksCount; i++) {
        if (namedStacks[i].used) cout << namedStacks[i].name << " ";
    }
    cout << endl;

    cout << "Очереди (" << namedQueuesCount << "): ";
    for (int i = 0; i < namedQueuesCount; i++) {
        if (namedQueues[i].used) cout << namedQueues[i].name << " ";
    }
    cout << endl;

    cout << "Массивы (" << namedArraysCount << "): ";
    for (int i = 0; i < namedArraysCount; i++) {
        if (namedArrays[i].used) cout << namedArrays[i].name << " ";
    }
    cout << endl;

    cout << "Односвязные списки (" << namedListsCount << "): ";
    for (int i = 0; i < namedListsCount; i++) {
        if (namedLists[i].used) cout << namedLists[i].name << " ";
    }
    cout << endl;

    cout << "Двусвязные списки (" << namedListsTwoCount << "): ";
    for (int i = 0; i < namedListsTwoCount; i++) {
        if (namedListsTwo[i].used) cout << namedListsTwo[i].name << " ";
    }
    cout << endl;

    cout << "Деревья (" << namedTreesCount << "): ";
    for (int i = 0; i < namedTreesCount; i++) {
        if (namedTrees[i].used) cout << namedTrees[i].name << " ";
    }
    cout << endl;
}
// Функции для работы с именованными массивами
void NAMED_MPUSH(const string& arrayName, const string& value) {
    NamedArray* array = findArrayByName(arrayName);
    if (!array) {
        array = createNewArray(arrayName);
        if (!array) return;
    }
    add(array->array, value);
    cout << "Добавлен элемент " << value << " в массив " << arrayName << endl;
}

void NAMED_MDEL(const string& arrayName, int index) {
    NamedArray* array = findArrayByName(arrayName);
    if (array) {
        if (index >= 0 && index < array->array.size) {
            string value = get(array->array, index);
            remove(array->array, index);
            cout << "Удален элемент " << value << " из массива " << arrayName << " по индексу " << index << endl;
        }
        else {
            cout << "Неверный индекс" << endl;
        }
    }
    else {
        cout << "Массив " << arrayName << " не найден" << endl;
    }
}

void NAMED_MGET(const string& arrayName, int index) {
    NamedArray* array = findArrayByName(arrayName);
    if (array) {
        if (index >= 0 && index < array->array.size) {
            string value = get(array->array, index);
            cout << "Элемент по индексу " << index << " в массиве " << arrayName << ": " << value << endl;
        }
        else {
            cout << "Неверный индекс" << endl;
        }
    }
    else {
        cout << "Массив " << arrayName << " не найден" << endl;
    }
}

void NAMED_PRINT_ARRAY(const string& arrayName) {
    NamedArray* array = findArrayByName(arrayName);
    if (!array) {
        cout << "Массив " << arrayName << " не найден" << endl;
        return;
    }

    cout << "Массив " << arrayName << ": ";
    print(array->array);
}

void NAMED_FPUSH_HEAD(const string& listName, const string& value) {
    NamedList* list = findListByName(listName);
    if (!list) {
        list = createNewList(listName);
        if (!list) return;
    }
    addNodeHead(&list->list, value);
    cout << "Добавлен элемент " << value << " в начало списка " << listName << endl;
}

void NAMED_FPUSH_TAIL(const string& listName, const string& value) {
    NamedList* list = findListByName(listName);
    if (!list) {
        list = createNewList(listName);
        if (!list) return;
    }
    addNodeTail(&list->list, value);
    cout << "Добавлен элемент " << value << " в конец списка " << listName << endl;
}

void NAMED_FPUSH_AFTER(const string& listName, int targetIndex, const string& value) {
    NamedList* list = findListByName(listName);
    if (!list) {
        list = createNewList(listName);
        if (!list) return;
    }

    linkedList* target = getNodeByIndex(list->list, targetIndex);
    if (target) {
        addNodeAfter(&list->list, target, value);
        cout << "Добавлен элемент " << value << " после индекса " << targetIndex << " в списке " << listName << endl;
    }
    else {
        cout << "Неверный индекс целевого узла" << endl;
    }
}

void NAMED_FPUSH_BEFORE(const string& listName, int targetIndex, const string& value) {
    NamedList* list = findListByName(listName);
    if (!list) {
        list = createNewList(listName);
        if (!list) return;
    }

    linkedList* target = getNodeByIndex(list->list, targetIndex);
    if (target) {
        addNodeBefore(&list->list, target, value);
        cout << "Добавлен элемент " << value << " до индекса " << targetIndex << " в списке " << listName << endl;
    }
    else {
        cout << "Неверный индекс целевого узла" << endl;
    }
}

void NAMED_FPOP_HEAD(const string& listName) {
    NamedList* list = findListByName(listName);
    if (list && list->list.head != nullptr) {
        string value = list->list.head->node;
        deleteNodeHead(&list->list);
        cout << "Удален элемент " << value << " из начала списка " << listName << endl;
    }
    else {
        cout << "Список " << listName << " не найден или пуст" << endl;
    }
}

void NAMED_FPOP_TAIL(const string& listName) {
    NamedList* list = findListByName(listName);
    if (list && list->list.head != nullptr) {
        // Находим последний элемент для вывода значения
        linkedList* current = list->list.head;
        while (current->next != nullptr) {
            current = current->next;
        }
        string value = current->node;

        deleteNodeTail(&list->list);
        cout << "Удален элемент " << value << " из конца списка " << listName << endl;
    }
    else {
        cout << "Список " << listName << " не найден или пуст" << endl;
    }
}

void NAMED_FPOP_AFTER(const string& listName, int targetIndex) {
    NamedList* list = findListByName(listName);
    if (list) {
        linkedList* target = getNodeByIndex(list->list, targetIndex);
        if (target && target->next != nullptr) {
            string value = target->next->node;
            deleteNodeAfter(&list->list, target);
            cout << "Удален элемент " << value << " после индекса " << targetIndex << " в списке " << listName << endl;
        }
        else {
            cout << "Неверный индекс или нет следующего элемента" << endl;
        }
    }
    else {
        cout << "Список " << listName << " не найден" << endl;
    }
}

void NAMED_FPOP_BEFORE(const string& listName, int targetIndex) {
    NamedList* list = findListByName(listName);
    if (list) {
        linkedList* target = getNodeByIndex(list->list, targetIndex);
        if (target && target != list->list.head) {
            // Находим предыдущий элемент для вывода значения
            linkedList* prev = list->list.head;
            while (prev->next != target) {
                prev = prev->next;
            }
            string value = prev->node;

            deleteNodeBefore(&list->list, target);
            cout << "Удален элемент " << value << " до индекса " << targetIndex << " в списке " << listName << endl;
        }
        else {
            cout << "Неверный индекс или нет предыдущего элемента" << endl;
        }
    }
    else {
        cout << "Список " << listName << " не найден" << endl;
    }
}

// === НОВЫЕ ФУНКЦИИ ДЛЯ ДВУСВЯЗНЫХ СПИСКОВ ===

void NAMED_LPUSH_HEAD(const string& listName, const string& value) {
    NamedListTwo* list = findListTwoByName(listName);
    if (!list) {
        list = createNewListTwo(listName);
        if (!list) return;
    }
    addNodeHeadTwo(&list->list, value);
    cout << "Добавлен элемент " << value << " в начало двусвязного списка " << listName << endl;
}

void NAMED_LPUSH_TAIL(const string& listName, const string& value) {
    NamedListTwo* list = findListTwoByName(listName);
    if (!list) {
        list = createNewListTwo(listName);
        if (!list) return;
    }
    addNodeTailTwo(&list->list, value);
    cout << "Добавлен элемент " << value << " в конец двусвязного списка " << listName << endl;
}

void NAMED_LPUSH_AFTER(const string& listName, int targetIndex, const string& value) {
    NamedListTwo* list = findListTwoByName(listName);
    if (!list) {
        list = createNewListTwo(listName);
        if (!list) return;
    }

    DoublyNode* target = getNodeByIndexTwo(list->list, targetIndex);
    if (target) {
        addNodeAfterTwo(&list->list, target, value);
        cout << "Добавлен элемент " << value << " после индекса " << targetIndex << " в двусвязном списке " << listName << endl;
    }
    else {
        cout << "Неверный индекс целевого узла" << endl;
    }
}

void NAMED_LPUSH_BEFORE(const string& listName, int targetIndex, const string& value) {
    NamedListTwo* list = findListTwoByName(listName);
    if (!list) {
        list = createNewListTwo(listName);
        if (!list) return;
    }

    DoublyNode* target = getNodeByIndexTwo(list->list, targetIndex);
    if (target) {
        addNodeBeforeTwo(&list->list, target, value);
        cout << "Добавлен элемент " << value << " до индекса " << targetIndex << " в двусвязном списке " << listName << endl;
    }
    else {
        cout << "Неверный индекс целевого узла" << endl;
    }
}

void NAMED_LPOP_HEAD(const string& listName) {
    NamedListTwo* list = findListTwoByName(listName);
    if (list && list->list.head != nullptr) {
        string value = list->list.head->node;
        deleteNodeHeadTwo(&list->list);
        cout << "Удален элемент " << value << " из начала двусвязного списка " << listName << endl;
    }
    else {
        cout << "Двусвязный список " << listName << " не найден или пуст" << endl;
    }
}

void NAMED_LPOP_TAIL(const string& listName) {
    NamedListTwo* list = findListTwoByName(listName);
    if (list && list->list.tail != nullptr) {
        string value = list->list.tail->node;
        deleteNodeTailTwo(&list->list);
        cout << "Удален элемент " << value << " из конца двусвязного списка " << listName << endl;
    }
    else {
        cout << "Двусвязный список " << listName << " не найден или пуст" << endl;
    }
}

void NAMED_LPOP_AFTER(const string& listName, int targetIndex) {
    NamedListTwo* list = findListTwoByName(listName);
    if (list) {
        DoublyNode* target = getNodeByIndexTwo(list->list, targetIndex);
        if (target && target->next != nullptr) {
            string value = target->next->node;
            deleteNodeAfterTwo(&list->list, target);
            cout << "Удален элемент " << value << " после индекса " << targetIndex << " в двусвязном списке " << listName << endl;
        }
        else {
            cout << "Неверный индекс или нет следующего элемента" << endl;
        }
    }
    else {
        cout << "Двусвязный список " << listName << " не найден" << endl;
    }
}

void NAMED_LPOP_BEFORE(const string& listName, int targetIndex) {
    NamedListTwo* list = findListTwoByName(listName);
    if (list) {
        DoublyNode* target = getNodeByIndexTwo(list->list, targetIndex);
        if (target && target->prev != nullptr) {
            string value = target->prev->node;
            deleteNodeBeforeTwo(&list->list, target);
            cout << "Удален элемент " << value << " до индекса " << targetIndex << " в двусвязном списке " << listName << endl;
        }
        else {
            cout << "Неверный индекс или нет предыдущего элемента" << endl;
        }
    }
    else {
        cout << "Двусвязный список " << listName << " не найден" << endl;
    }
}

// Функции для работы с именованными односвязными списками
void NAMED_FPUSH(const string& listName, const string& value, int position) {
    NamedList* list = findListByName(listName);
    if (!list) {
        list = createNewList(listName);
        if (!list) return;
    }

    if (position == -1) {
        // Добавляем в конец
        addNodeTail(&list->list, value);
    }
    else {
        // Добавляем после указанной позиции
        linkedList* target = getNodeByIndex(list->list, position);
        if (target) {
            addNodeAfter(&list->list, target, value);
        }
        else {
            cout << "Неверная позиция" << endl;
            return;
        }
    }
    cout << "Добавлен элемент " << value << " в односвязный список " << listName << endl;
}

void NAMED_FDEL(const string& listName, const string& value) {
    NamedList* list = findListByName(listName);
    if (list && deleteNodeIndex(&list->list, value)) {
        cout << "Удален элемент " << value << " из односвязного списка " << listName << endl;
    }
    else {
        cout << "Элемент не найден или список не существует" << endl;
    }
}

void NAMED_FGET(const string& listName, int index) {
    NamedList* list = findListByName(listName);
    if (list) {
        linkedList* node = getNodeByIndex(list->list, index);
        if (node) {
            cout << "Элемент по индексу " << index << " в списке " << listName << ": " << node->node << endl;
        }
        else {
            cout << "Неверный индекс" << endl;
        }
    }
    else {
        cout << "Список " << listName << " не найден" << endl;
    }
}

void NAMED_PRINT_LIST(const string& listName) {
    NamedList* list = findListByName(listName);
    if (!list) {
        cout << "Односвязный список " << listName << " не найден" << endl;
        return;
    }
    cout << "Односвязный список " << listName << ": ";
    printList(list->list);
}

// Функции для работы с именованными двусвязными списками
void NAMED_LPUSH(const string& listName, const string& value, int position) {
    NamedListTwo* list = findListTwoByName(listName);
    if (!list) {
        list = createNewListTwo(listName);
        if (!list) return;
    }

    if (position == -1) {
        // Добавляем в конец
        addNodeTailTwo(&list->list, value);
    }
    else {
        // Добавляем после указанной позиции
        DoublyNode* target = getNodeByIndexTwo(list->list, position);
        if (target) {
            addNodeAfterTwo(&list->list, target, value);
        }
        else {
            cout << "Неверная позиция" << endl;
            return;
        }
    }
    cout << "Добавлен элемент " << value << " в двусвязный список " << listName << endl;
}

void NAMED_LDEL(const string& listName, const string& value) {
    NamedListTwo* list = findListTwoByName(listName);
    if (list && deleteNodeIndexTwo(&list->list, value)) {
        cout << "Удален элемент " << value << " из двусвязного списка " << listName << endl;
    }
    else {
        cout << "Элемент не найден или список не существует" << endl;
    }
}

void NAMED_LGET(const string& listName, int index) {
    NamedListTwo* list = findListTwoByName(listName);
    if (list) {
        DoublyNode* node = getNodeByIndexTwo(list->list, index);
        if (node) {
            cout << "Элемент по индексу " << index << " в списке " << listName << ": " << node->node << endl;
        }
        else {
            cout << "Неверный индекс" << endl;
        }
    }
    else {
        cout << "Список " << listName << " не найден" << endl;
    }
}

void NAMED_PRINT_LIST_TWO(const string& listName) {
    NamedListTwo* list = findListTwoByName(listName);
    if (!list) {
        cout << "Двусвязный список " << listName << " не найден" << endl;
        return;
    }
    cout << "Двусвязный список " << listName << ": ";
    printListTwo(list->list);
}

// Функции для работы с именованными деревьями

void NAMED_TINSERT_BINARY(const string& treeName, const string& value) {
    NamedTree* tree = findTreeByName(treeName);
    if (!tree) {
        tree = createNewTree(treeName);
        if (!tree) return;
    }
    insertBST(&tree->tree, value);
    cout << "Добавлен элемент " << value << " в бинарное дерево " << treeName << endl;
}



void NAMED_TGET(const string& treeName, const string& value) {
    NamedTree* tree = findTreeByName(treeName);
    if (tree) {
        Node* node = BFS(&tree->tree, value);
        if (node) {
            cout << "Найден элемент " << value << " в дереве " << treeName << endl;
        }
        else {
            cout << "Элемент " << value << " не найден в дереве " << treeName << endl;
        }
    }
    else {
        cout << "Дерево " << treeName << " не найдено" << endl;
    }
}

// Функция для проверки типа дерева
void NAMED_CHECK_TREE_TYPE(const string& treeName) {
    NamedTree* tree = findTreeByName(treeName);
    if (!tree) {
        cout << "Дерево " << treeName << " не найдено" << endl;
        return;
    }

    checkTreeType(&tree->tree);
}

void NAMED_PRINT_TREE(const string& treeName) {
    NamedTree* tree = findTreeByName(treeName);
    if (!tree) {
        cout << "Дерево " << treeName << " не найдено" << endl;
        return;
    }

    cout << "=== " << treeName << " ===" << endl;
    if (!tree->tree.root) {
        cout << "Дерево пустое" << endl;
        return;
    }

    cout << "Inorder: ";
    inorder(tree->tree.root);
    cout << endl;

    cout << "Preorder: ";
    preorder(tree->tree.root);
    cout << endl;

    cout << "Postorder: ";
    postorder(tree->tree.root);
    cout << endl;

    cout << "BFS: ";
    printBFS(&tree->tree);
}

// Универсальная функция PRINT
void PRINT(const string& structure) {
    cout << "Используйте PRINT <тип> <имя> для именованных структур" << endl;
    cout << "Типы: S (стек), Q (очередь), M (массив), F (односвязный список), L (двусвязный список), T (дерево)" << endl;
}

// Системные функции
void SAVE_ALL() {
    saveNamedStacksToFile("named_data");
    saveNamedQueuesToFile("named_data");
    saveNamedArraysToFile("named_data");
    saveNamedListsToFile("named_data");
    saveNamedListsTwoToFile("named_data");
    saveNamedTreesToFile("named_data");
   
}

void LOAD_ALL() {
    loadNamedStacksFromFile("named_data");
    loadNamedQueuesFromFile("named_data");
    loadNamedArraysFromFile("named_data");
    loadNamedListsFromFile("named_data");
    loadNamedListsTwoFromFile("named_data");
    loadNamedTreesFromFile("named_data");

}

void CLEAR_ALL() {
    for (int i = 0; i < namedStacksCount; i++) {
        namedStacks[i].used = false;
    }
    for (int i = 0; i < namedQueuesCount; i++) {
        namedQueues[i].used = false;
    }
    for (int i = 0; i < namedArraysCount; i++) {
        namedArrays[i].used = false;
    }
    for (int i = 0; i < namedListsCount; i++) {
        namedLists[i].used = false;
    }
    for (int i = 0; i < namedListsTwoCount; i++) {
        namedListsTwo[i].used = false;
    }
    for (int i = 0; i < namedTreesCount; i++) {
        namedTrees[i].used = false;
    }

    namedStacksCount = 0;
    namedQueuesCount = 0;
    namedArraysCount = 0;
    namedListsCount = 0;
    namedListsTwoCount = 0;
    namedTreesCount = 0;


}

void initGlobalStructures() {
    namedStacksCount = 0;
    namedQueuesCount = 0;
    namedArraysCount = 0;
    namedListsCount = 0;
    namedListsTwoCount = 0;
    namedTreesCount = 0;
}

void SAVE_ALL_TO(const string& filename) {
    saveNamedStacksToFile(filename);
    saveNamedQueuesToFile(filename);
    saveNamedArraysToFile(filename);
    saveNamedListsToFile(filename);
    saveNamedListsTwoToFile(filename);
    saveNamedTreesToFile(filename);
    
}

void LOAD_ALL_FROM(const string& filename) {
    CLEAR_ALL();

    // Просто загружаем все данные - функции загрузки сами выводят сообщения
    loadNamedStacksFromFile(filename);
    loadNamedQueuesFromFile(filename);
    loadNamedArraysFromFile(filename);
    loadNamedListsFromFile(filename);
    loadNamedListsTwoFromFile(filename);
    loadNamedTreesFromFile(filename);


}


// Интерфейс командной строки
void processCommand(const string& command) {
    istringstream iss(command);
    string cmd;
    iss >> cmd;

    // Именованные структуры
    if (cmd == "SPUSH") {
        string stackName, value;
        if (iss >> stackName) {
            getline(iss, value);
            if (!value.empty() && value[0] == ' ') {
                value = value.substr(1);
            }
            if (!value.empty()) {
                NAMED_SPUSH(stackName, value);
            }
            else {
                cout << "Неверный формат команды: SPUSH <stack_name> <value>" << endl;
            }
        }
        else {
            cout << "Неверный формат команды: SPUSH <stack_name> <value>" << endl;
        }
    }
    else if (cmd == "SPOP") {
        string stackName;
        if (iss >> stackName) {
            NAMED_SPOP(stackName);
        }
        else {
            cout << "Неверный формат команды: SPOP <stack_name>" << endl;
        }
    }
    else if (cmd == "SGET") {
        string stackName;
        if (iss >> stackName) {
            NAMED_SGET(stackName);
        }
        else {
            cout << "Неверный формат команды: SGET <stack_name>" << endl;
        }
    }
    else if (cmd == "QPUSH") {
        string queueName, value;
        if (iss >> queueName) {
            getline(iss, value);
            if (!value.empty() && value[0] == ' ') {
                value = value.substr(1);
            }
            if (!value.empty()) {
                NAMED_QPUSH(queueName, value);
            }
            else {
                cout << "Неверный формат команды: QPUSH <queue_name> <value>" << endl;
            }
        }
        else {
            cout << "Неверный формат команды: QPUSH <queue_name> <value>" << endl;
        }
    }
    else if (cmd == "QPOP") {
        string queueName;
        if (iss >> queueName) {
            NAMED_QPOP(queueName);
        }
        else {
            cout << "Неверный формат команды: QPOP <queue_name>" << endl;
        }
    }
    else if (cmd == "QGET") {
        string queueName;
        if (iss >> queueName) {
            NAMED_QGET(queueName);
        }
        else {
            cout << "Неверный формат команды: QGET <queue_name>" << endl;
        }
    }
    else if (cmd == "MPUSH") {
        string arrayName, value;
        if (iss >> arrayName) {
            getline(iss, value);
            if (!value.empty() && value[0] == ' ') {
                value = value.substr(1);
            }
            if (!value.empty()) {
                NAMED_MPUSH(arrayName, value);
            }
            else {
                cout << "Неверный формат команды: MPUSH <array_name> <value>" << endl;
            }
        }
        else {
            cout << "Неверный формат команды: MPUSH <array_name> <value>" << endl;
        }
    }
    else if (cmd == "MDEL") {
        string arrayName;
        int index;
        if (iss >> arrayName >> index) {
            NAMED_MDEL(arrayName, index);
        }
        else {
            cout << "Неверный формат команды: MDEL <array_name> <index>" << endl;
        }
    }
    else if (cmd == "MGET") {
        string arrayName;
        int index;
        if (iss >> arrayName >> index) {
            NAMED_MGET(arrayName, index);
        }
        else {
            cout << "Неверный формат команды: MGET <array_name> <index>" << endl;
        }
    }
    else if (cmd == "FPUSH") {
        string listName, value;
        int position = -1;
        if (iss >> listName >> value) {
            iss >> position;
            NAMED_FPUSH(listName, value, position);
        }
        else {
            cout << "Неверный формат команды: FPUSH <list_name> <value> [position]" << endl;
        }
    }
    else if (cmd == "FDEL") {
        string listName, value;
        if (iss >> listName >> value) {
            NAMED_FDEL(listName, value);
        }
        else {
            cout << "Неверный формат команды: FDEL <list_name> <value>" << endl;
        }
    }
    else if (cmd == "FGET") {
        string listName;
        int index;
        if (iss >> listName >> index) {
            NAMED_FGET(listName, index);
        }
        else {
            cout << "Неверный формат команды: FGET <list_name> <index>" << endl;
        }
    }
    else if (cmd == "LPUSH") {
        string listName, value;
        int position = -1;
        if (iss >> listName >> value) {
            iss >> position;
            NAMED_LPUSH(listName, value, position);
        }
        else {
            cout << "Неверный формат команды: LPUSH <list_name> <value> [position]" << endl;
        }
    }
    else if (cmd == "FPUSH_HEAD") {
        string listName, value;
        if (iss >> listName >> value) {
            NAMED_FPUSH_HEAD(listName, value);
        }
        else {
            cout << "Неверный формат команды: FPUSH_HEAD <list_name> <value>" << endl;
        }
    }
    else if (cmd == "FPUSH_TAIL") {
        string listName, value;
        if (iss >> listName >> value) {
            NAMED_FPUSH_TAIL(listName, value);
        }
        else {
            cout << "Неверный формат команды: FPUSH_TAIL <list_name> <value>" << endl;
        }
    }
    else if (cmd == "FPUSH_AFTER") {
        string listName, value;
        int targetIndex;
        if (iss >> listName >> targetIndex >> value) {
            NAMED_FPUSH_AFTER(listName, targetIndex, value);
        }
        else {
            cout << "Неверный формат команды: FPUSH_AFTER <list_name> <target_index> <value>" << endl;
        }
    }
    else if (cmd == "FPUSH_BEFORE") {
        string listName, value;
        int targetIndex;
        if (iss >> listName >> targetIndex >> value) {
            NAMED_FPUSH_BEFORE(listName, targetIndex, value);
        }
        else {
            cout << "Неверный формат команды: FPUSH_BEFORE <list_name> <target_index> <value>" << endl;
        }
    }
    else if (cmd == "FPOP_HEAD") {
        string listName;
        if (iss >> listName) {
            NAMED_FPOP_HEAD(listName);
        }
        else {
            cout << "Неверный формат команды: FPOP_HEAD <list_name>" << endl;
        }
    }
    else if (cmd == "FPOP_TAIL") {
        string listName;
        if (iss >> listName) {
            NAMED_FPOP_TAIL(listName);
        }
        else {
            cout << "Неверный формат команды: FPOP_TAIL <list_name>" << endl;
        }
    }
    else if (cmd == "FPOP_AFTER") {
        string listName;
        int targetIndex;
        if (iss >> listName >> targetIndex) {
            NAMED_FPOP_AFTER(listName, targetIndex);
        }
        else {
            cout << "Неверный формат команды: FPOP_AFTER <list_name> <target_index>" << endl;
        }
    }
    else if (cmd == "FPOP_BEFORE") {
        string listName;
        int targetIndex;
        if (iss >> listName >> targetIndex) {
            NAMED_FPOP_BEFORE(listName, targetIndex);
        }
        else {
            cout << "Неверный формат команды: FPOP_BEFORE <list_name> <target_index>" << endl;
        }
    }

    else if (cmd == "LPUSH_HEAD") {
        string listName, value;
        if (iss >> listName >> value) {
            NAMED_LPUSH_HEAD(listName, value);
        }
        else {
            cout << "Неверный формат команды: LPUSH_HEAD <list_name> <value>" << endl;
        }
    }
    else if (cmd == "LPUSH_TAIL") {
        string listName, value;
        if (iss >> listName >> value) {
            NAMED_LPUSH_TAIL(listName, value);
        }
        else {
            cout << "Неверный формат команды: LPUSH_TAIL <list_name> <value>" << endl;
        }
    }
    else if (cmd == "LPUSH_AFTER") {
        string listName, value;
        int targetIndex;
        if (iss >> listName >> targetIndex >> value) {
            NAMED_LPUSH_AFTER(listName, targetIndex, value);
        }
        else {
            cout << "Неверный формат команды: LPUSH_AFTER <list_name> <target_index> <value>" << endl;
        }
    }
    else if (cmd == "LPUSH_BEFORE") {
        string listName, value;
        int targetIndex;
        if (iss >> listName >> targetIndex >> value) {
            NAMED_LPUSH_BEFORE(listName, targetIndex, value);
        }
        else {
            cout << "Неверный формат команды: LPUSH_BEFORE <list_name> <target_index> <value>" << endl;
        }
    }
    else if (cmd == "LPOP_HEAD") {
        string listName;
        if (iss >> listName) {
            NAMED_LPOP_HEAD(listName);
        }
        else {
            cout << "Неверный формат команды: LPOP_HEAD <list_name>" << endl;
        }
    }
    else if (cmd == "LPOP_TAIL") {
        string listName;
        if (iss >> listName) {
            NAMED_LPOP_TAIL(listName);
        }
        else {
            cout << "Неверный формат команды: LPOP_TAIL <list_name>" << endl;
        }
    }
    else if (cmd == "LPOP_AFTER") {
        string listName;
        int targetIndex;
        if (iss >> listName >> targetIndex) {
            NAMED_LPOP_AFTER(listName, targetIndex);
        }
        else {
            cout << "Неверный формат команды: LPOP_AFTER <list_name> <target_index>" << endl;
        }
    }
    else if (cmd == "LPOP_BEFORE") {
        string listName;
        int targetIndex;
        if (iss >> listName >> targetIndex) {
            NAMED_LPOP_BEFORE(listName, targetIndex);
        }
        else {
            cout << "Неверный формат команды: LPOP_BEFORE <list_name> <target_index>" << endl;
        }
    }
    else if (cmd == "LDEL") {
        string listName, value;
        if (iss >> listName >> value) {
            NAMED_LDEL(listName, value);
        }
        else {
            cout << "Неверный формат команды: LDEL <list_name> <value>" << endl;
        }
    }
    else if (cmd == "LGET") {
        string listName;
        int index;
        if (iss >> listName >> index) {
            NAMED_LGET(listName, index);
        }
        else {
            cout << "Неверный формат команды: LGET <list_name> <index>" << endl;
        }
    }
    // Добавьте в блок обработки деревьев в processCommand
    else if (cmd == "TINSERT_BINARY") {
        string treeName, value;
        if (iss >> treeName >> value) {
            NAMED_TINSERT_BINARY(treeName, value);
        }
        else {
            cout << "Неверный формат команды: TINSERT_BINARY <tree_name> <value>" << endl;
        }
    }

    else if (cmd == "TGET") {
        string treeName, value;
        if (iss >> treeName >> value) {
            NAMED_TGET(treeName, value);
        }
        else {
            cout << "Неверный формат команды: TGET <tree_name> <value>" << endl;
        }
    }
    else if (cmd == "TCHECK") {
        string treeName;
        if (iss >> treeName) {
            NAMED_CHECK_TREE_TYPE(treeName);
        }
        else {
            cout << "Неверный формат команды: TCHECK <tree_name>" << endl;
        }
        }

    // В функции processCommand добавьте:
    else if (cmd == "FFIND") {
        string listName, value;
        if (iss >> listName >> value) {
            NAMED_FFIND(listName, value);
        }
        else {
            cout << "Неверный формат команды: FFIND <list_name> <value>" << endl;
        }
    }
    else if (cmd == "FCOUNT") {
        string listName;
        if (iss >> listName) {
            NAMED_FCOUNT(listName);
        }
        else {
            cout << "Неверный формат команды: FCOUNT <list_name>" << endl;
        }
    }
    else if (cmd == "LFIND") {
        string listName, value;
        if (iss >> listName >> value) {
            NAMED_LFIND(listName, value);
        }
        else {
            cout << "Неверный формат команды: LFIND <list_name> <value>" << endl;
        }
    }
    else if (cmd == "LCOUNT") {
        string listName;
        if (iss >> listName) {
            NAMED_LCOUNT(listName);
        }
        else {
            cout << "Неверный формат команды: LCOUNT <list_name>" << endl;
        }
    }
    else if (cmd == "LPRINT_REVERSE") {
        string listName;
        if (iss >> listName) {
            NAMED_PRINT_LIST_TWO_REVERSE(listName);
        }
        else {
            cout << "Неверный формат команды: LPRINT_REVERSE <list_name>" << endl;
        }
    }
    else if (cmd == "LIST") {
        LIST_STRUCTURES();
    }
    // В функции processCommand добавьте:
    else if (cmd == "MADDAT") {
        string arrayName, value;
        int index;
        if (iss >> arrayName >> index >> value) {
            NAMED_MADDAT(arrayName, index, value);
        }
        else {
            cout << "Неверный формат команды: MADDAT <array_name> <index> <value>" << endl;
        }
    }
    else if (cmd == "MSET") {
        string arrayName, value;
        int index;
        if (iss >> arrayName >> index >> value) {
            NAMED_MSET(arrayName, index, value);
        }
        else {
            cout << "Неверный формат команды: MSET <array_name> <index> <value>" << endl;
        }
    }
    else if (cmd == "MLENGTH") {
        string arrayName;
        if (iss >> arrayName) {
            NAMED_MLENGTH(arrayName);
        }
        else {
            cout << "Неверный формат команды: MLENGTH <array_name>" << endl;
        }
    }
    else if (cmd == "MFIND") {
        string arrayName, value;
        if (iss >> arrayName >> value) {
            NAMED_MFIND(arrayName, value);
        }
        else {
            cout << "Неверный формат команды: MFIND <array_name> <value>" << endl;
        }
    }
    else if (cmd == "MCREATE") {
        string arrayName;
        if (iss >> arrayName) {
            NAMED_MCREATE(arrayName);
        }
        else {
            cout << "Неверный формат команды: MCREATE <array_name>" << endl;
        }
    }
    else if (cmd == "PRINT") {
        string type, name;
        if (iss >> type) {
            if (iss >> name) {
                if (type == "S") {
                    NAMED_PRINT_STACK(name);
                }
                else if (type == "Q") {
                    NAMED_PRINT_QUEUE(name);
                }
                else if (type == "M") {
                    NAMED_PRINT_ARRAY(name);
                }
                else if (type == "F") {
                    NAMED_PRINT_LIST(name);
                }
                else if (type == "L") {
                    NAMED_PRINT_LIST_TWO(name);
                }
                else if (type == "T") {
                    NAMED_PRINT_TREE(name);
                }
                else {
                    cout << "Неизвестный тип структуры: " << type << endl;
                }
            }
            else {
                PRINT(type);
            }
        }
        else {
            cout << "Неверный формат команды: PRINT <type> [name]" << endl;
        }
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
        SAVE_ALL();
        exit(0);
    }
    else if (cmd == "HELP") {
        cout << "Доступные команды (только именованные структуры):" << endl;
        cout << "Именованные структуры:" << endl;
        cout << "  SPUSH <stack_name> <value> - добавить в именованный стек" << endl;
        cout << "  SPOP <stack_name> - извлечь из именованного стека" << endl;
        cout << "  SGET <stack_name> - посмотреть верхний элемент именованного стека" << endl;
        cout << "  QPUSH <queue_name> <value> - добавить в именованную очередь" << endl;
        cout << "  QPOP <queue_name> - извлечь из именованной очереди" << endl;
        cout << "  QGET <queue_name> - посмотреть первый элемент именованной очереди" << endl;
        cout << "  MPUSH <array_name> <value> - добавить в именованный массив" << endl;
        cout << "  MDEL <array_name> <index> - удалить из именованного массива по индексу" << endl;
        cout << "  MGET <array_name> <index> - получить элемент именованного массива по индексу" << endl;
        cout << "  MADDAT <array_name> <index> <value> - добавить в массив по индексу" << endl;
        cout << "  MSET <array_name> <index> <value> - заменить элемент в массиве по индексу" << endl;
        cout << "  MLENGTH <array_name> - получить длину массива" << endl;
        cout << "  MFIND <array_name> <value> - найти элемент в массиве по значению" << endl;
        cout << "  MCREATE <array_name> - создать новый массив" << endl;

        cout << "Односвязные списки:" << endl;
        cout << "  FPUSH <list_name> <value> [position] - добавить в односвязный список" << endl;
        cout << "  FDEL <list_name> <value> - удалить из односвязного списка по значению" << endl;
        cout << "  FGET <list_name> <index> - получить элемент односвязного списка по индексу" << endl;
        cout << "  FFIND <list_name> <value> - найти в односвязном списке по значению" << endl;
        cout << "  FCOUNT <list_name> - подсчитать элементы в односвязном списке" << endl;
        cout << "  FPUSH_HEAD <list_name> <value> - добавить в начало списка" << endl;
        cout << "  FPUSH_TAIL <list_name> <value> - добавить в конец списка" << endl;
        cout << "  FPUSH_AFTER <list_name> <target_index> <value> - добавить после указанного индекса" << endl;
        cout << "  FPUSH_BEFORE <list_name> <target_index> <value> - добавить до указанного индекса" << endl;
        cout << "  FPOP_HEAD <list_name> - удалить из начала списка" << endl;
        cout << "  FPOP_TAIL <list_name> - удалить из конца списка" << endl;
        cout << "  FPOP_AFTER <list_name> <target_index> - удалить после указанного индекса" << endl;
        cout << "  FPOP_BEFORE <list_name> <target_index> - удалить до указанного индекса" << endl;

        cout << "Двусвязные списки:" << endl;
        cout << "  LPUSH <list_name> <value> [position] - добавить в двусвязный список" << endl;
        cout << "  LDEL <list_name> <value> - удалить из двусвязного списка по значению" << endl;
        cout << "  LGET <list_name> <index> - получить элемент двусвязного списка по индексу" << endl;
        cout << "  LFIND <list_name> <value> - найти в двусвязном списке по значению" << endl;
        cout << "  LCOUNT <list_name> - подсчитать элементы в двусвязном списке" << endl;
        cout << "  LPRINT_REVERSE <list_name> - вывести двусвязный список в обратном порядке" << endl;
        cout << "  LPUSH_HEAD <list_name> <value> - добавить в начало двусвязного списка" << endl;
        cout << "  LPUSH_TAIL <list_name> <value> - добавить в конец двусвязного списка" << endl;
        cout << "  LPUSH_AFTER <list_name> <target_index> <value> - добавить после указанного индекса" << endl;
        cout << "  LPUSH_BEFORE <list_name> <target_index> <value> - добавить до указанного индекса" << endl;
        cout << "  LPOP_HEAD <list_name> - удалить из начала двусвязного списка" << endl;
        cout << "  LPOP_TAIL <list_name> - удалить из конца двусвязного списка" << endl;
        cout << "  LPOP_AFTER <list_name> <target_index> - удалить после указанного индекса" << endl;
        cout << "  LPOP_BEFORE <list_name> <target_index> - удалить до указанного индекса" << endl;

        cout << "Деревья:" << endl;
        cout << "  TINSERT_BINARY <tree_name> <value> - добавить в бинарное дерево (сравнение значений)" << endl;
        cout << "  TGET <tree_name> <value> - найти в дереве" << endl;
        cout << "  TCHECK <tree_name> - проверить тип дерева (полное/строго полное)" << endl;

        cout << "Системные команды:" << endl;
        cout << "  LIST - показать все именованные структуры" << endl;
        cout << "  PRINT <type> <name> - вывести именованную структуру (типы: S,Q,M,F,L,T)" << endl;
        cout << "  SAVE_ALL - сохранить все именованные данные" << endl;
        cout << "  LOAD_ALL - загрузить все именованные данные" << endl;
        cout << "  CLEAR_ALL - очистить все именованные данные" << endl;
        cout << "  EXIT/QUIT - выход (с автосохранением)" << endl;
        cout << "  HELP - показать эту справку" << endl;
    }
}
