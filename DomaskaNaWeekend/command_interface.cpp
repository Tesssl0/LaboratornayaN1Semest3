#include "command_interface.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// ����������� ���������
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
        LOAD_ALL_FROM("named_data");  // ���������� ����� �������
        firstLoad = false;
    }
}

// ��������������� ������� ��� ������ � ������������ �����������
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
        cout << "���� " << name << " ��� ����������!" << endl;
        return existing;
    }

    if (namedStacksCount >= MAX_NAMED_STRUCTURES) {
        cout << "��������� ����� ����������� ������!" << endl;
        return nullptr;
    }

    namedStacks[namedStacksCount].name = name;
    namedStacks[namedStacksCount].used = true;
    namedStacks[namedStacksCount].stack.arr = new string[100];
    namedStacks[namedStacksCount].stack.capacity = 100;
    namedStacks[namedStacksCount].stack.topIndex = -1;
    namedStacks[namedStacksCount].stack.silent = true;

    // �������������� ������
    for (int i = 0; i < 100; i++) {
        namedStacks[namedStacksCount].stack.arr[i] = "";
    }

    return &namedStacks[namedStacksCount++];
}

NamedQueue* createNewQueue(const string& name) {
    NamedQueue* existing = findQueueByName(name);
    if (existing) {
        cout << "������� " << name << " ��� ����������!" << endl;
        return existing;
    }

    if (namedQueuesCount >= MAX_NAMED_STRUCTURES) {
        cout << "��������� ����� ����������� ��������!" << endl;
        return nullptr;
    }

    // ���� ������� ����� ������� ����� new
    namedQueues[namedQueuesCount].name = name;
    namedQueues[namedQueuesCount].queue = new Queue<string>(100, true);
    namedQueues[namedQueuesCount].used = true;

    cout << "������� ����� �������: " << name << endl;
    return &namedQueues[namedQueuesCount++];
}

NamedArray* createNewArray(const string& name) {
    NamedArray* existing = findArrayByName(name);
    if (existing) {
        cout << "������ " << name << " ��� ����������!" << endl;
        return existing;
    }

    if (namedArraysCount >= MAX_NAMED_STRUCTURES) {
        cout << "��������� ����� ����������� ��������!" << endl;
        return nullptr;
    }

    namedArrays[namedArraysCount].name = name;
    namedArrays[namedArraysCount].used = true;
    init(namedArrays[namedArraysCount].array);

    cout << "������ ����� ������: " << name << endl;
    return &namedArrays[namedArraysCount++];
}

NamedList* createNewList(const string& name) {
    NamedList* existing = findListByName(name);
    if (existing) {
        cout << "����������� ������ " << name << " ��� ����������!" << endl;
        return existing;
    }

    if (namedListsCount >= MAX_NAMED_STRUCTURES) {
        cout << "��������� ����� ����������� ����������� �������!" << endl;
        return nullptr;
    }

    namedLists[namedListsCount].name = name;
    namedLists[namedListsCount].used = true;
    namedLists[namedListsCount].list.head = nullptr;

    cout << "������ ����� ����������� ������: " << name << endl;
    return &namedLists[namedListsCount++];
}

NamedListTwo* createNewListTwo(const string& name) {
    NamedListTwo* existing = findListTwoByName(name);
    if (existing) {
        cout << "���������� ������ " << name << " ��� ����������!" << endl;
        return existing;
    }

    if (namedListsTwoCount >= MAX_NAMED_STRUCTURES) {
        cout << "��������� ����� ����������� ���������� �������!" << endl;
        return nullptr;
    }

    namedListsTwo[namedListsTwoCount].name = name;
    namedListsTwo[namedListsTwoCount].used = true;
    namedListsTwo[namedListsTwoCount].list.head = nullptr;
    namedListsTwo[namedListsTwoCount].list.tail = nullptr;

    cout << "������ ����� ���������� ������: " << name << endl;
    return &namedListsTwo[namedListsTwoCount++];
}

NamedTree* createNewTree(const string& name) {
    NamedTree* existing = findTreeByName(name);
    if (existing) {
        cout << "������ " << name << " ��� ����������!" << endl;
        return existing;
    }

    if (namedTreesCount >= MAX_NAMED_STRUCTURES) {
        cout << "��������� ����� ����������� ��������!" << endl;
        return nullptr;
    }

    namedTrees[namedTreesCount].name = name;
    namedTrees[namedTreesCount].used = true;
    namedTrees[namedTreesCount].tree.root = nullptr;

    cout << "������� ����� ������: " << name << endl;
    return &namedTrees[namedTreesCount++];
}

// ������� ��� ������ � ������������ �������
void NAMED_SPUSH(const string& stackName, const string& value) {
    NamedStack* stack = findStackByName(stackName);
    if (!stack) {
        stack = createNewStack(stackName);
        if (!stack) return;
    }
    stack->stack.push(value);
    cout << "�������� ������� " << value << " � ���� " << stackName << endl;
}

void NAMED_SPOP(const string& stackName) {
    NamedStack* stack = findStackByName(stackName);
    if (stack && !stack->stack.isEmpty()) {
        string value = stack->stack.top();
        stack->stack.pop();
        cout << "�������� ������� " << value << " �� ����� " << stackName << endl;
    }
    else {
        cout << "���� " << stackName << " �� ������ ��� ����" << endl;
    }
}

void NAMED_SGET(const string& stackName) {
    NamedStack* stack = findStackByName(stackName);
    if (stack && !stack->stack.isEmpty()) {
        string value = stack->stack.top();
        cout << "������� ������� ����� " << stackName << ": " << value << endl;
    }
    else {
        cout << "���� " << stackName << " �� ������ ��� ����" << endl;
    }
}

void NAMED_PRINT_STACK(const string& stackName) {
    NamedStack* stack = findStackByName(stackName);
    if (!stack) {
        cout << "���� " << stackName << " �� ������" << endl;
        return;
    }

    if (stack->stack.isEmpty()) {
        cout << "���� " << stackName << ": ����" << endl;
    }
    else {
        Stack tempStack(100, true);
        Stack restoreStack(100, true);

        cout << "���� " << stackName << ": (������ -> �������): ";

        while (!stack->stack.isEmpty()) {
            string value = stack->stack.top();
            cout << value << " ";
            tempStack.push(value);
            stack->stack.pop();
        }

        cout << endl;

        while (!tempStack.isEmpty()) {
            stack->stack.push(tempStack.top());
            tempStack.pop();
        }
    }
}

void NAMED_QPUSH(const string& queueName, const string& value) {
    NamedQueue* queue = findQueueByName(queueName);
    if (!queue) {
        queue = createNewQueue(queueName);
        if (!queue) return;
    }
    queue->queue->enqueue(value);  // ���������� -> ��� ���������
    cout << "�������� ������� " << value << " � ������� " << queueName << endl;
}

void NAMED_QPOP(const string& queueName) {
    NamedQueue* queue = findQueueByName(queueName);
    if (queue && !queue->queue->isEmpty()) {
        string value = queue->queue->dequeue();
        cout << "�������� ������� " << value << " �� ������� " << queueName << endl;
    }
    else {
        cout << "������� " << queueName << " �� ������� ��� �����" << endl;
    }
}

void NAMED_QGET(const string& queueName) {
    NamedQueue* queue = findQueueByName(queueName);
    if (queue && !queue->queue->isEmpty()) {
        string value = queue->queue->front();
        cout << "������ ������� ������� " << queueName << ": " << value << endl;
    }
    else {
        cout << "������� " << queueName << " �� ������� ��� �����" << endl;
    }
}
// === ����� ������� ��� �������� ===

void NAMED_MADDAT(const string& arrayName, int index, const string& value) {
    NamedArray* array = findArrayByName(arrayName);
    if (array) {
        if (index >= 0 && index <= array->array.size) {
            addAt(array->array, index, value);
            cout << "�������� ������� " << value << " � ������ " << arrayName << " �� ������� " << index << endl;
        }
        else {
            cout << "�������� ������" << endl;
        }
    }
    else {
        cout << "������ " << arrayName << " �� ������" << endl;
    }
}

void NAMED_MSET(const string& arrayName, int index, const string& value) {
    NamedArray* array = findArrayByName(arrayName);
    if (array) {
        if (index >= 0 && index < array->array.size) {
            set(array->array, index, value);
            cout << "������� ������� �� ������� " << index << " �� �������� " << value << " � ������� " << arrayName << endl;
        }
        else {
            cout << "�������� ������" << endl;
        }
    }
    else {
        cout << "������ " << arrayName << " �� ������" << endl;
    }
}

void NAMED_MLENGTH(const string& arrayName) {
    NamedArray* array = findArrayByName(arrayName);
    if (array) {
        int len = length(array->array);
        cout << "����� ������� " << arrayName << ": " << len << " ���������" << endl;
    }
    else {
        cout << "������ " << arrayName << " �� ������" << endl;
    }
}

void NAMED_MFIND(const string& arrayName, const string& value) {
    NamedArray* array = findArrayByName(arrayName);
    if (array) {
        int index = findInArray(array->array, value);
        if (index != -1) {
            cout << "������� " << value << " ������ � ������� " << arrayName << " �� ������� " << index << endl;
        }
        else {
            cout << "������� " << value << " �� ������ � ������� " << arrayName << endl;
        }
    }
    else {
        cout << "������ " << arrayName << " �� ������" << endl;
    }
}

void NAMED_MCREATE(const string& arrayName) {
    NamedArray* array = findArrayByName(arrayName);
    if (!array) {
        array = createNewArray(arrayName);
        if (array) {
            cout << "������ " << arrayName << " ������" << endl;
        }
    }
    else {
        cout << "������ " << arrayName << " ��� ����������" << endl;
    }
}

void NAMED_PRINT_QUEUE(const string& queueName) {
    NamedQueue* queue = findQueueByName(queueName);
    if (!queue) {
        cout << "������� " << queueName << " �� �������" << endl;
        return;
    }

    if (queue->queue->isEmpty()) {
        cout << "������� " << queueName << ": �����" << endl;
    }
    else {
        Queue<string> tempQueue(100, true);

        cout << "������� " << queueName << ": (������ -> ���������): ";

        while (!queue->queue->isEmpty()) {
            string value = queue->queue->dequeue();
            cout << value << " ";
            tempQueue.enqueue(value);
        }

        cout << endl;

        while (!tempQueue.isEmpty()) {
            queue->queue->enqueue(tempQueue.dequeue());
        }
    }
}
// === ����� ������� ��� ����������� ������� ===

void NAMED_FFIND(const string& listName, const string& value) {
    NamedList* list = findListByName(listName);
    if (list) {
        if (findNodeIndex(&list->list, value)) {
            cout << "������� " << value << " ������ � ������ " << listName << endl;
        }
        else {
            cout << "������� " << value << " �� ������ � ������ " << listName << endl;
        }
    }
    else {
        cout << "������ " << listName << " �� ������" << endl;
    }
}

void NAMED_FCOUNT(const string& listName) {
    NamedList* list = findListByName(listName);
    if (list) {
        int count = countNodes(list->list);
        cout << "���������� ��������� � ������ " << listName << ": " << count << endl;
    }
    else {
        cout << "������ " << listName << " �� ������" << endl;
    }
}

// === ����� ������� ��� ���������� ������� ===

void NAMED_LFIND(const string& listName, const string& value) {
    NamedListTwo* list = findListTwoByName(listName);
    if (list) {
        if (findNodeIndexTwo(&list->list, value)) {
            cout << "������� " << value << " ������ � ������ " << listName << endl;
        }
        else {
            cout << "������� " << value << " �� ������ � ������ " << listName << endl;
        }
    }
    else {
        cout << "������ " << listName << " �� ������" << endl;
    }
}

void NAMED_LCOUNT(const string& listName) {
    NamedListTwo* list = findListTwoByName(listName);
    if (list) {
        int count = countNodesTwo(list->list);
        cout << "���������� ��������� � ������ " << listName << ": " << count << endl;
    }
    else {
        cout << "������ " << listName << " �� ������" << endl;
    }
}

void NAMED_PRINT_LIST_TWO_REVERSE(const string& listName) {
    NamedListTwo* list = findListTwoByName(listName);
    if (!list) {
        cout << "���������� ������ " << listName << " �� ������" << endl;
        return;
    }

    cout << "���������� ������ " << listName << " (�������� �������): ";
    DoublyNode* current = list->list.tail;
    while (current != nullptr) {
        cout << current->node << " ";
        current = current->prev;
    }
    cout << endl;
}

// === ��������� ������� ===

void LIST_STRUCTURES() {
    cout << "=== ����������� ��������� ===" << endl;

    cout << "����� (" << namedStacksCount << "): ";
    for (int i = 0; i < namedStacksCount; i++) {
        if (namedStacks[i].used) cout << namedStacks[i].name << " ";
    }
    cout << endl;

    cout << "������� (" << namedQueuesCount << "): ";
    for (int i = 0; i < namedQueuesCount; i++) {
        if (namedQueues[i].used) cout << namedQueues[i].name << " ";
    }
    cout << endl;

    cout << "������� (" << namedArraysCount << "): ";
    for (int i = 0; i < namedArraysCount; i++) {
        if (namedArrays[i].used) cout << namedArrays[i].name << " ";
    }
    cout << endl;

    cout << "����������� ������ (" << namedListsCount << "): ";
    for (int i = 0; i < namedListsCount; i++) {
        if (namedLists[i].used) cout << namedLists[i].name << " ";
    }
    cout << endl;

    cout << "���������� ������ (" << namedListsTwoCount << "): ";
    for (int i = 0; i < namedListsTwoCount; i++) {
        if (namedListsTwo[i].used) cout << namedListsTwo[i].name << " ";
    }
    cout << endl;

    cout << "������� (" << namedTreesCount << "): ";
    for (int i = 0; i < namedTreesCount; i++) {
        if (namedTrees[i].used) cout << namedTrees[i].name << " ";
    }
    cout << endl;
}
// ������� ��� ������ � ������������ ���������
void NAMED_MPUSH(const string& arrayName, const string& value) {
    NamedArray* array = findArrayByName(arrayName);
    if (!array) {
        array = createNewArray(arrayName);
        if (!array) return;
    }
    add(array->array, value);
    cout << "�������� ������� " << value << " � ������ " << arrayName << endl;
}

void NAMED_MDEL(const string& arrayName, int index) {
    NamedArray* array = findArrayByName(arrayName);
    if (array) {
        if (index >= 0 && index < array->array.size) {
            string value = get(array->array, index);
            remove(array->array, index);
            cout << "������ ������� " << value << " �� ������� " << arrayName << " �� ������� " << index << endl;
        }
        else {
            cout << "�������� ������" << endl;
        }
    }
    else {
        cout << "������ " << arrayName << " �� ������" << endl;
    }
}

void NAMED_MGET(const string& arrayName, int index) {
    NamedArray* array = findArrayByName(arrayName);
    if (array) {
        if (index >= 0 && index < array->array.size) {
            string value = get(array->array, index);
            cout << "������� �� ������� " << index << " � ������� " << arrayName << ": " << value << endl;
        }
        else {
            cout << "�������� ������" << endl;
        }
    }
    else {
        cout << "������ " << arrayName << " �� ������" << endl;
    }
}

void NAMED_PRINT_ARRAY(const string& arrayName) {
    NamedArray* array = findArrayByName(arrayName);
    if (!array) {
        cout << "������ " << arrayName << " �� ������" << endl;
        return;
    }

    cout << "������ " << arrayName << ": ";
    print(array->array);
}

// ������� ��� ������ � ������������ ������������ ��������
void NAMED_FPUSH(const string& listName, const string& value, int position) {
    NamedList* list = findListByName(listName);
    if (!list) {
        list = createNewList(listName);
        if (!list) return;
    }

    if (position == -1) {
        addNode(&list->list, nullptr, value, TAIL);
    }
    else {
        linkedList* target = getNodeByIndex(list->list, position);
        if (target) {
            addNode(&list->list, target, value, AFTER);
        }
        else {
            cout << "�������� �������" << endl;
            return;
        }
    }
    cout << "�������� ������� " << value << " � ����������� ������ " << listName << endl;
}

void NAMED_FDEL(const string& listName, const string& value) {
    NamedList* list = findListByName(listName);
    if (list && deleteNodeIndex(&list->list, value)) {
        cout << "������ ������� " << value << " �� ������������ ������ " << listName << endl;
    }
    else {
        cout << "������� �� ������ ��� ������ �� ����������" << endl;
    }
}

void NAMED_FGET(const string& listName, int index) {
    NamedList* list = findListByName(listName);
    if (list) {
        linkedList* node = getNodeByIndex(list->list, index);
        if (node) {
            cout << "������� �� ������� " << index << " � ������ " << listName << ": " << node->node << endl;
        }
        else {
            cout << "�������� ������" << endl;
        }
    }
    else {
        cout << "������ " << listName << " �� ������" << endl;
    }
}

void NAMED_PRINT_LIST(const string& listName) {
    NamedList* list = findListByName(listName);
    if (!list) {
        cout << "����������� ������ " << listName << " �� ������" << endl;
        return;
    }
    cout << "����������� ������ " << listName << ": ";
    printList(list->list);
}

// ������� ��� ������ � ������������ ����������� ��������
void NAMED_LPUSH(const string& listName, const string& value, int position) {
    NamedListTwo* list = findListTwoByName(listName);
    if (!list) {
        list = createNewListTwo(listName);
        if (!list) return;
    }

    if (position == -1) {
        addNodeTwo(&list->list, nullptr, value, TAILTwo);
    }
    else {
        DoublyNode* target = getNodeByIndexTwo(list->list, position);
        if (target) {
            addNodeTwo(&list->list, target, value, AFTERTwo);
        }
        else {
            cout << "�������� �������" << endl;
            return;
        }
    }
    cout << "�������� ������� " << value << " � ���������� ������ " << listName << endl;
}

void NAMED_LDEL(const string& listName, const string& value) {
    NamedListTwo* list = findListTwoByName(listName);
    if (list && deleteNodeIndexTwo(&list->list, value)) {
        cout << "������ ������� " << value << " �� ����������� ������ " << listName << endl;
    }
    else {
        cout << "������� �� ������ ��� ������ �� ����������" << endl;
    }
}

void NAMED_LGET(const string& listName, int index) {
    NamedListTwo* list = findListTwoByName(listName);
    if (list) {
        DoublyNode* node = getNodeByIndexTwo(list->list, index);
        if (node) {
            cout << "������� �� ������� " << index << " � ������ " << listName << ": " << node->node << endl;
        }
        else {
            cout << "�������� ������" << endl;
        }
    }
    else {
        cout << "������ " << listName << " �� ������" << endl;
    }
}

void NAMED_PRINT_LIST_TWO(const string& listName) {
    NamedListTwo* list = findListTwoByName(listName);
    if (!list) {
        cout << "���������� ������ " << listName << " �� ������" << endl;
        return;
    }
    cout << "���������� ������ " << listName << ": ";
    printListTwo(list->list);
}

// ������� ��� ������ � ������������ ���������
void NAMED_TINSERT(const string& treeName, const string& value) {
    NamedTree* tree = findTreeByName(treeName);
    if (!tree) {
        tree = createNewTree(treeName);
        if (!tree) return;
    }
    insert(&tree->tree, value);
    cout << "�������� ������� " << value << " � ������ " << treeName << endl;
}

void NAMED_TDEL(const string& treeName, const string& value) {
    NamedTree* tree = findTreeByName(treeName);
    if (tree) {
        try {
            if (value.empty()) {
                cout << "������: ������ ������ ��� ��������" << endl;
                return;
            }
            deleteNode(&tree->tree, value);
            cout << "������ ������� " << value << " �� ������ " << treeName << endl;
        }
        catch (const exception& e) {
            cout << "������ ��� �������� �� ������: " << e.what() << endl;
        }
    }
    else {
        cout << "������ " << treeName << " �� �������" << endl;
    }
}

void NAMED_TGET(const string& treeName, const string& value) {
    NamedTree* tree = findTreeByName(treeName);
    if (tree) {
        Node* node = BFS(&tree->tree, value);
        if (node) {
            cout << "������ ������� " << value << " � ������ " << treeName << endl;
        }
        else {
            cout << "������� " << value << " �� ������ � ������ " << treeName << endl;
        }
    }
    else {
        cout << "������ " << treeName << " �� �������" << endl;
    }
}

void NAMED_PRINT_TREE(const string& treeName) {
    NamedTree* tree = findTreeByName(treeName);
    if (!tree) {
        cout << "������ " << treeName << " �� �������" << endl;
        return;
    }

    cout << "=== ������ " << treeName << " ===" << endl;
    if (!tree->tree.root) {
        cout << "������ ������" << endl;
        return;
    }

    cout << "Inorder (������������): ";
    inorder(tree->tree.root);
    cout << endl;
    cout << "Preorder (������): ";
    preorder(tree->tree.root);
    cout << endl;
    cout << "Postorder (��������): ";
    postorder(tree->tree.root);
    cout << endl;

    cout << "BFS (����� � ������): ";
    Queue<Node*> q(100, true);
    q.enqueue(tree->tree.root);
    while (!q.isEmpty()) {
        Node* temp = q.dequeue();
        cout << temp->data << " ";
        if (temp->left) q.enqueue(temp->left);
        if (temp->right) q.enqueue(temp->right);
    }
    cout << endl;
}

// ������������� ������� PRINT
void PRINT(const string& structure) {
    cout << "����������� PRINT <���> <���> ��� ����������� ��������" << endl;
    cout << "����: S (����), Q (�������), M (������), F (����������� ������), L (���������� ������), T (������)" << endl;
}

// ��������� �������
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

    // ������ ��������� ��� ������ - ������� �������� ���� ������� ���������
    loadNamedStacksFromFile(filename);
    loadNamedQueuesFromFile(filename);
    loadNamedArraysFromFile(filename);
    loadNamedListsFromFile(filename);
    loadNamedListsTwoFromFile(filename);
    loadNamedTreesFromFile(filename);


}


// ��������� ��������� ������
void processCommand(const string& command) {
    istringstream iss(command);
    string cmd;
    iss >> cmd;

    // ����������� ���������
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
                cout << "�������� ������ �������: SPUSH <stack_name> <value>" << endl;
            }
        }
        else {
            cout << "�������� ������ �������: SPUSH <stack_name> <value>" << endl;
        }
    }
    else if (cmd == "SPOP") {
        string stackName;
        if (iss >> stackName) {
            NAMED_SPOP(stackName);
        }
        else {
            cout << "�������� ������ �������: SPOP <stack_name>" << endl;
        }
    }
    else if (cmd == "SGET") {
        string stackName;
        if (iss >> stackName) {
            NAMED_SGET(stackName);
        }
        else {
            cout << "�������� ������ �������: SGET <stack_name>" << endl;
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
                cout << "�������� ������ �������: QPUSH <queue_name> <value>" << endl;
            }
        }
        else {
            cout << "�������� ������ �������: QPUSH <queue_name> <value>" << endl;
        }
    }
    else if (cmd == "QPOP") {
        string queueName;
        if (iss >> queueName) {
            NAMED_QPOP(queueName);
        }
        else {
            cout << "�������� ������ �������: QPOP <queue_name>" << endl;
        }
    }
    else if (cmd == "QGET") {
        string queueName;
        if (iss >> queueName) {
            NAMED_QGET(queueName);
        }
        else {
            cout << "�������� ������ �������: QGET <queue_name>" << endl;
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
                cout << "�������� ������ �������: MPUSH <array_name> <value>" << endl;
            }
        }
        else {
            cout << "�������� ������ �������: MPUSH <array_name> <value>" << endl;
        }
    }
    else if (cmd == "MDEL") {
        string arrayName;
        int index;
        if (iss >> arrayName >> index) {
            NAMED_MDEL(arrayName, index);
        }
        else {
            cout << "�������� ������ �������: MDEL <array_name> <index>" << endl;
        }
    }
    else if (cmd == "MGET") {
        string arrayName;
        int index;
        if (iss >> arrayName >> index) {
            NAMED_MGET(arrayName, index);
        }
        else {
            cout << "�������� ������ �������: MGET <array_name> <index>" << endl;
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
            cout << "�������� ������ �������: FPUSH <list_name> <value> [position]" << endl;
        }
    }
    else if (cmd == "FDEL") {
        string listName, value;
        if (iss >> listName >> value) {
            NAMED_FDEL(listName, value);
        }
        else {
            cout << "�������� ������ �������: FDEL <list_name> <value>" << endl;
        }
    }
    else if (cmd == "FGET") {
        string listName;
        int index;
        if (iss >> listName >> index) {
            NAMED_FGET(listName, index);
        }
        else {
            cout << "�������� ������ �������: FGET <list_name> <index>" << endl;
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
            cout << "�������� ������ �������: LPUSH <list_name> <value> [position]" << endl;
        }
    }
    else if (cmd == "LDEL") {
        string listName, value;
        if (iss >> listName >> value) {
            NAMED_LDEL(listName, value);
        }
        else {
            cout << "�������� ������ �������: LDEL <list_name> <value>" << endl;
        }
    }
    else if (cmd == "LGET") {
        string listName;
        int index;
        if (iss >> listName >> index) {
            NAMED_LGET(listName, index);
        }
        else {
            cout << "�������� ������ �������: LGET <list_name> <index>" << endl;
        }
    }
    else if (cmd == "TINSERT") {
        string treeName, value;
        if (iss >> treeName >> value) {
            NAMED_TINSERT(treeName, value);
        }
        else {
            cout << "�������� ������ �������: TINSERT <tree_name> <value>" << endl;
        }
    }
    else if (cmd == "TDEL") {
        string treeName, value;
        if (iss >> treeName >> value) {
            NAMED_TDEL(treeName, value);
        }
        else {
            cout << "�������� ������ �������: TDEL <tree_name> <value>" << endl;
        }
    }
    else if (cmd == "TGET") {
        string treeName, value;
        if (iss >> treeName >> value) {
            NAMED_TGET(treeName, value);
        }
        else {
            cout << "�������� ������ �������: TGET <tree_name> <value>" << endl;
        }
    }
    // � ������� processCommand ��������:
    else if (cmd == "FFIND") {
        string listName, value;
        if (iss >> listName >> value) {
            NAMED_FFIND(listName, value);
        }
        else {
            cout << "�������� ������ �������: FFIND <list_name> <value>" << endl;
        }
        }
    else if (cmd == "FCOUNT") {
            string listName;
            if (iss >> listName) {
                NAMED_FCOUNT(listName);
            }
            else {
                cout << "�������� ������ �������: FCOUNT <list_name>" << endl;
            }
            }
    else if (cmd == "LFIND") {
                string listName, value;
                if (iss >> listName >> value) {
                    NAMED_LFIND(listName, value);
                }
                else {
                    cout << "�������� ������ �������: LFIND <list_name> <value>" << endl;
                }
                }
    else if (cmd == "LCOUNT") {
                    string listName;
                    if (iss >> listName) {
                        NAMED_LCOUNT(listName);
                    }
                    else {
                        cout << "�������� ������ �������: LCOUNT <list_name>" << endl;
                    }
                    }
    else if (cmd == "LPRINT_REVERSE") {
                        string listName;
                        if (iss >> listName) {
                            NAMED_PRINT_LIST_TWO_REVERSE(listName);
                        }
                        else {
                            cout << "�������� ������ �������: LPRINT_REVERSE <list_name>" << endl;
                        }
                        }
    else if (cmd == "LIST") {
                            LIST_STRUCTURES();
                            }
                            // � ������� processCommand ��������:
    else if (cmd == "MADDAT") {
        string arrayName, value;
        int index;
        if (iss >> arrayName >> index >> value) {
            NAMED_MADDAT(arrayName, index, value);
        }
        else {
            cout << "�������� ������ �������: MADDAT <array_name> <index> <value>" << endl;
        }
        }
    else if (cmd == "MSET") {
            string arrayName, value;
            int index;
            if (iss >> arrayName >> index >> value) {
                NAMED_MSET(arrayName, index, value);
            }
            else {
                cout << "�������� ������ �������: MSET <array_name> <index> <value>" << endl;
            }
            }
    else if (cmd == "MLENGTH") {
                string arrayName;
                if (iss >> arrayName) {
                    NAMED_MLENGTH(arrayName);
                }
                else {
                    cout << "�������� ������ �������: MLENGTH <array_name>" << endl;
                }
                }
    else if (cmd == "MFIND") {
                    string arrayName, value;
                    if (iss >> arrayName >> value) {
                        NAMED_MFIND(arrayName, value);
                    }
                    else {
                        cout << "�������� ������ �������: MFIND <array_name> <value>" << endl;
                    }
                    }
    else if (cmd == "MCREATE") {
                        string arrayName;
                        if (iss >> arrayName) {
                            NAMED_MCREATE(arrayName);
                        }
                        else {
                            cout << "�������� ������ �������: MCREATE <array_name>" << endl;
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
                    cout << "����������� ��� ���������: " << type << endl;
                }
            }
            else {
                PRINT(type);
            }
        }
        else {
            cout << "�������� ������ �������: PRINT <type> [name]" << endl;
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
        cout << "��������� ������� (������ ����������� ���������):" << endl;
        cout << "����������� ���������:" << endl;
        cout << "  SPUSH <stack_name> <value> - �������� � ����������� ����" << endl;
        cout << "  SPOP <stack_name> - ������� �� ������������ �����" << endl;
        cout << "  SGET <stack_name> - ���������� ������� ������� ������������ �����" << endl;
        cout << "  QPUSH <queue_name> <value> - �������� � ����������� �������" << endl;
        cout << "  QPOP <queue_name> - ������� �� ����������� �������" << endl;
        cout << "  QGET <queue_name> - ���������� ������ ������� ����������� �������" << endl;
        cout << "  MPUSH <array_name> <value> - �������� � ����������� ������" << endl;
        cout << "  MDEL <array_name> <index> - ������� �� ������������ ������� �� �������" << endl;
        cout << "  MGET <array_name> <index> - �������� ������� ������������ ������� �� �������" << endl;
        cout << "  MADDAT <array_name> <index> <value> - �������� � ������ �� �������" << endl;
        cout << "  MSET <array_name> <index> <value> - �������� ������� � ������� �� �������" << endl;
        cout << "  MLENGTH <array_name> - �������� ����� �������" << endl;
        cout << "  MFIND <array_name> <value> - ����� ������� � ������� �� ��������" << endl;
        cout << "  MCREATE <array_name> - ������� ����� ������" << endl;
        cout << "  FPUSH <list_name> <value> [position] - �������� � ����������� ������" << endl;
        cout << "  FDEL <list_name> <value> - ������� �� ������������ ������ �� ��������" << endl;
        cout << "  FGET <list_name> <index> - �������� ������� ������������ ������ �� �������" << endl;
        cout << "  FFIND <list_name> <value> - ����� � ����������� ������ �� ��������" << endl;
        cout << "  FCOUNT <list_name> - ���������� �������� � ����������� ������" << endl;
        cout << "  LPUSH <list_name> <value> [position] - �������� � ���������� ������" << endl;
        cout << "  LDEL <list_name> <value> - ������� �� ����������� ������ �� ��������" << endl;
        cout << "  LGET <list_name> <index> - �������� ������� ����������� ������ �� �������" << endl;
        cout << "  LFIND <list_name> <value> - ����� � ���������� ������ �� ��������" << endl;
        cout << "  LCOUNT <list_name> - ���������� �������� � ���������� ������" << endl;
        cout << "  LPRINT_REVERSE <list_name> - ������� ���������� ������ � �������� �������" << endl;
        cout << "  TINSERT <tree_name> <value> - �������� � ������" << endl;
        cout << "  TDEL <tree_name> <value> - ������� �� ������" << endl;
        cout << "  TGET <tree_name> <value> - ����� � ������" << endl;
        cout << "  LIST - �������� ��� ����������� ���������" << endl;
        cout << "  PRINT <type> <name> - ������� ����������� ��������� (����: S,Q,M,F,L,T)" << endl;
        cout << "��������� �������:" << endl;
        cout << "  SAVE_ALL - ��������� ��� ����������� ������" << endl;
        cout << "  LOAD_ALL - ��������� ��� ����������� ������" << endl;
        cout << "  CLEAR_ALL - �������� ��� ����������� ������" << endl;
        cout << "  EXIT/QUIT - ����� (� ���������������)" << endl;
        cout << "  HELP - �������� ��� �������" << endl;
    }
    else {
        cout << "����������� �������. ������� HELP ��� ������ ������." << endl;
    }
}