#include "file_operations.h"
#include "command_interface.h" 
#include "fullBinaryTree.h"
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
                // Заменяем vector на массив
                const int MAX_VALUES = 100;
                string values[MAX_VALUES];
                int valueCount = 0;

                while (iss >> value && valueCount < MAX_VALUES) {
                    values[valueCount++] = value;
                }

                for (int i = valueCount - 1; i >= 0; i--) {
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
        if (namedQueues[i].used) {
            file << "QUEUE " << namedQueues[i].name << " ";

            // Создаем временную очередь для сохранения порядка
            Queue tempQueue;
            initQueue(&tempQueue, true);

            // Перемещаем элементы во временную очередь и записываем
            while (!isEmpty(&namedQueues[i].queue)) {
                string value = dequeue(&namedQueues[i].queue);
                file << value << " ";
                enqueue(&tempQueue, value);
            }

            // Возвращаем элементы обратно
            while (!isEmpty(&tempQueue)) {
                string value = dequeue(&tempQueue);
                enqueue(&namedQueues[i].queue, value);
            }

            // Очищаем временную очередь
            clearQueue(&tempQueue);

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
            if (queue) {
                // Очищаем существующую очередь
                clearQueue(&queue->queue);

                string value;
                while (iss >> value) {
                    enqueue(&queue->queue, value);
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
            NamedArray* arr = findArrayByName(name);
            if (!arr) {
                arr = createNewArray(name);
            }
            if (arr) {
                destroy(arr->array);
                init(arr->array);

                string value;
                while (iss >> value) {
                    add(arr->array, value);
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
                addNodeTail(&namedLists[namedListsCount].list, value);
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
                addNodeTailTwo(&namedListsTwo[namedListsTwoCount].list, value);
            }

            namedListsTwoCount++;
        }
    }
    file.close();
}

// Сохранение именованных деревьев
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

            // Используем существующую функцию для обхода в ширину
            // Создаем временный файл для сохранения BFS обхода
            string tempFilename = "temp_bfs_output.txt";
            ofstream tempFile(tempFilename);
            if (!tempFile.is_open()) continue;

            // Сохраняем стандартный вывод
            streambuf* oldCoutBuffer = cout.rdbuf();
            // Перенаправляем вывод в файл
            cout.rdbuf(tempFile.rdbuf());

            // Выполняем BFS обход (функция printBFS выводит в cout)
            printBFS(&namedTrees[i].tree);

            // Восстанавливаем стандартный вывод
            cout.rdbuf(oldCoutBuffer);
            tempFile.close();

            // Читаем данные из временного файла
            ifstream tempInput(tempFilename);
            string line;
            if (getline(tempInput, line)) {
                // Пропускаем префикс "Обход в ширину: "
                size_t pos = line.find(": ");
                if (pos != string::npos) {
                    string bfsData = line.substr(pos + 2);
                    file << bfsData;
                }
            }
            tempInput.close();

            // Удаляем временный файл
            remove(tempFilename.c_str());

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