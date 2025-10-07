#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <fstream>
#include <string>
#include <sstream>
#include "array.h"
#include "list.h"
#include "listTwo.h"
#include "queue.h"
#include "stack.h"
#include "fullBinaryTree.h"

using namespace std;

// Базовые функции для работы с файлами
void saveToFile(const string& filename, const string& data);
string readFromFile(const string& filename);

// Функции для работы с именованными структурами
void saveNamedStacksToFile(const string& filename);
void loadNamedStacksFromFile(const string& filename);

void saveNamedQueuesToFile(const string& filename);
void loadNamedQueuesFromFile(const string& filename);

void saveNamedArraysToFile(const string& filename);
void loadNamedArraysFromFile(const string& filename);

void saveNamedListsToFile(const string& filename);
void loadNamedListsFromFile(const string& filename);

void saveNamedListsTwoToFile(const string& filename);
void loadNamedListsTwoFromFile(const string& filename);

void saveNamedTreesToFile(const string& filename);
void loadNamedTreesFromFile(const string& filename);

#endif
