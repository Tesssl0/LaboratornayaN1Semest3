#pragma once
#ifndef FULLBINARYTREE_H
#define FULLBINARYTREE_H
#include <iostream>
#include <string>

using namespace std;

// Структура узла дерева
struct Node {
    string data;
    Node* left;
    Node* right;

    Node(const string& value) : data(value), left(nullptr), right(nullptr) {}
};

// Структура бинарного дерева
struct fullBinaryTree {
    Node* root;

    fullBinaryTree() : root(nullptr) {}
};


// Основные операции с деревом
void insertBinary(fullBinaryTree* tree, const string& value);
void deleteNode(fullBinaryTree* tree, const string& value);
Node* BFS(fullBinaryTree* tree, const string& value);

// Обходы дерева
void inorder(Node* node);
void preorder(Node* node);
void postorder(Node* node);
void printBFS(fullBinaryTree* tree);

// Очистка дерева
void clearTree(Node* node);
void clearFullBinaryTree(fullBinaryTree* tree);

// Проверка типов деревьев
bool isCompleteBinaryTree(Node* root);
bool isFullBinaryTree(Node* root);
void checkTreeType(fullBinaryTree* tree);
string getBFSAsString(fullBinaryTree* tree);
string getInorderAsString(Node* node);
#endif
