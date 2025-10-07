#include "file_operations.h"
#include "command_interface.h" 

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

// Явные инстанциации шаблонов для очереди
template void saveQueueToFile<string>(Queue<string>& queue, const string& filename);
template void loadQueueFromFile<string>(Queue<string>& queue, const string& filename);

// Реализации шаблонных функций для очереди
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

// Сохранение именованных стеков
void saveNamedStacksToFile(const string& filename) {
    ofstream file(filename + ".named_stacks");
    if (!file.is_open()) return;

    for (int i = 0; i < namedStacksCount; i++) {
        if (namedStacks[i].used) {
            file << "STACK " << namedStacks[i].name << " ";

            Stack tempStack(100, true);
            Stack restoreStack(100, true);

            while (!namedStacks[i].stack.isEmpty()) {
                string value = namedStacks[i].stack.top();
                tempStack.push(value);
                namedStacks[i].stack.pop();
            }

            while (!tempStack.isEmpty()) {
                string value = tempStack.top();
                file << value << " ";
                restoreStack.push(value);
                tempStack.pop();
            }

            while (!restoreStack.isEmpty()) {
                namedStacks[i].stack.push(restoreStack.top());
                restoreStack.pop();
            }

            file << endl;
        }
    }
    file.close();
}

// Загрузка именованных стеков
void loadNamedStacksFromFile(const string& filename) {
    ifstream file(filename + ".named_stacks");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string type, name;
        if (iss >> type >> name && type == "STACK") {
            NamedStack* stack = findStackByName(name);
            if (!stack) {
                stack = createNewStack(name);
            }

            if (stack) {
                string value;
                vector<string> values;
                while (iss >> value) {
                    values.push_back(value);
                }

                for (int i = values.size() - 1; i >= 0; i--) {
                    stack->stack.push(values[i]);
                }
            }
        }
    }
    file.close();
}

// Сохранение именованных очередей
void saveNamedQueuesToFile(const string& filename) {
    ofstream file(filename + ".named_queues");
    if (!file.is_open()) return;

    for (int i = 0; i < namedQueuesCount; i++) {
        if (namedQueues[i].used && namedQueues[i].queue) {
            file << "QUEUE " << namedQueues[i].name << " ";

            Queue<string> tempQueue(100, true);
            int queueSize = namedQueues[i].queue->getSize();

            for (int j = 0; j < queueSize; j++) {
                string value = namedQueues[i].queue->dequeue();
                file << value << " ";
                tempQueue.enqueue(value);
            }

            for (int j = 0; j < queueSize; j++) {
                namedQueues[i].queue->enqueue(tempQueue.dequeue());
            }

            file << endl;
        }
    }
    file.close();
}

// Загрузка именованных очередей
void loadNamedQueuesFromFile(const string& filename) {
    ifstream file(filename + ".named_queues");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string type, name;
        if (iss >> type >> name && type == "QUEUE") {
            NamedQueue* queue = findQueueByName(name);
            if (!queue) {
                queue = createNewQueue(name);
            }
            if (queue && queue->queue) {
                string value;
                while (iss >> value) {
                    queue->queue->enqueue(value);
                }
            }
        }
    }
    file.close();
}

// Сохранение именованных массивов
void saveNamedArraysToFile(const string& filename) {
    ofstream file(filename + ".named_arrays");
    if (!file.is_open()) return;

    for (int i = 0; i < namedArraysCount; i++) {
        if (namedArrays[i].used) {
            file << "ARRAY " << namedArrays[i].name << " ";
            for (int j = 0; j < namedArrays[i].array.size; j++) {
                file << namedArrays[i].array.data[j] << " ";
            }
            file << endl;
        }
    }
    file.close();
}

// Загрузка именованных массивов
void loadNamedArraysFromFile(const string& filename) {
    ifstream file(filename + ".named_arrays");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string type, name;
        if (iss >> type >> name && type == "ARRAY") {
            NamedArray* array = findArrayByName(name);
            if (!array) {
                array = createNewArray(name);
            }
            if (array) {
                string value;
                while (iss >> value) {
                    add(array->array, value);
                }
            }
        }
    }
    file.close();
}

// Сохранение именованных односвязных списков
void saveNamedListsToFile(const string& filename) {
    ofstream file(filename + ".named_lists");
    if (!file.is_open()) return;

    for (int i = 0; i < namedListsCount; i++) {
        if (namedLists[i].used) {
            file << "LIST " << namedLists[i].name << " ";
            linkedList* current = namedLists[i].list.head;
            while (current != nullptr) {
                file << current->node << " ";
                current = current->next;
            }
            file << endl;
        }
    }
    file.close();
}

// Загрузка именованных односвязных списков
void loadNamedListsFromFile(const string& filename) {
    ifstream file(filename + ".named_lists");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string type, name;
        if (iss >> type >> name && type == "LIST") {
            if (namedListsCount >= MAX_NAMED_STRUCTURES) continue;

            namedLists[namedListsCount].name = name;
            namedLists[namedListsCount].used = true;
            namedLists[namedListsCount].list.head = nullptr;

            string value;
            while (iss >> value) {
                addNode(&namedLists[namedListsCount].list, nullptr, value, TAIL);
            }

            namedListsCount++;
        }
    }
    file.close();
}

// Сохранение именованных двусвязных списков
void saveNamedListsTwoToFile(const string& filename) {
    ofstream file(filename + ".named_lists_two");
    if (!file.is_open()) return;

    for (int i = 0; i < namedListsTwoCount; i++) {
        if (namedListsTwo[i].used) {
            file << "LIST_TWO " << namedListsTwo[i].name << " ";
            DoublyNode* current = namedListsTwo[i].list.head;
            while (current != nullptr) {
                file << current->node << " ";
                current = current->next;
            }
            file << endl;
        }
    }
    file.close();
}

// Загрузка именованных двусвязных списков
void loadNamedListsTwoFromFile(const string& filename) {
    ifstream file(filename + ".named_lists_two");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string type, name;
        if (iss >> type >> name && type == "LIST_TWO") {
            if (namedListsTwoCount >= MAX_NAMED_STRUCTURES) continue;

            namedListsTwo[namedListsTwoCount].name = name;
            namedListsTwo[namedListsTwoCount].used = true;
            namedListsTwo[namedListsTwoCount].list.head = nullptr;
            namedListsTwo[namedListsTwoCount].list.tail = nullptr;

            string value;
            while (iss >> value) {
                addNodeTwo(&namedListsTwo[namedListsTwoCount].list, nullptr, value, TAILTwo);
            }

            namedListsTwoCount++;
        }
    }
    file.close();
}

// Сохранение именованных деревьев
void saveNamedTreesToFile(const string& filename) {
    ofstream file(filename + ".named_trees");
    if (!file.is_open()) return;

    for (int i = 0; i < namedTreesCount; i++) {
        if (namedTrees[i].used) {
            file << "TREE " << namedTrees[i].name << " ";

            if (!namedTrees[i].tree.root) {
                file << endl;
                continue;
            }

            Queue<Node*> q(100, true);
            q.enqueue(namedTrees[i].tree.root);

            while (!q.isEmpty()) {
                Node* temp = q.dequeue();
                if (temp) {
                    file << temp->data << " ";
                    if (temp->left) q.enqueue(temp->left);
                    if (temp->right) q.enqueue(temp->right);
                }
            }

            file << endl;
        }
    }
    file.close();
}

// Загрузка именованных деревьев
void loadNamedTreesFromFile(const string& filename) {
    ifstream file(filename + ".named_trees");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string type, name;
        if (iss >> type >> name && type == "TREE") {
            if (namedTreesCount >= MAX_NAMED_STRUCTURES) continue;

            namedTrees[namedTreesCount].name = name;
            namedTrees[namedTreesCount].used = true;
            namedTrees[namedTreesCount].tree.root = nullptr;

            string value;
            while (iss >> value) {
                insert(&namedTrees[namedTreesCount].tree, value);
            }

            namedTreesCount++;
        }
    }
    file.close();
}
