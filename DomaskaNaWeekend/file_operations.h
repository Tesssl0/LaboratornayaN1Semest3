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

// ������� ������� ��� ������ � �������
void saveToFile(const string& filename, const string& data);
string readFromFile(const string& filename);

// ������
void saveArrayToFile(const Array& arr, const string& filename);
void loadArrayFromFile(Array& arr, const string& filename);

// ����������� ������
void saveForwardListToFile(const ForwardList& flist, const string& filename);
void loadForwardListFromFile(ForwardList& flist, const string& filename);

// ���������� ������
void saveForwardListTwoToFile(const ForwardListTwo& flist, const string& filename);
void loadForwardListTwoFromFile(ForwardListTwo& flist, const string& filename);

// �������
template<typename T>
void saveQueueToFile(Queue<T>& queue, const string& filename);

template<typename T>
void loadQueueFromFile(Queue<T>& queue, const string& filename);

// ����
void saveStackToFile(Stack& stack, const string& filename);
void loadStackFromFile(Stack& stack, const string& filename);

// ������
void saveTreeToFile(fullBinaryTree* tree, const string& filename);
void loadTreeFromFile(fullBinaryTree* tree, const string& filename);

// ������� ��� ������ � ������������ �����������
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