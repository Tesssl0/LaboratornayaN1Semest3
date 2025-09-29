#ifndef FULLBINARYTREE_H
#define FULLBINARYTREE_H

#include <iostream>
#include "Queue.h"
using namespace std;

// Узел дерева
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Полное бинарное дерево
struct fullBinaryTree {
    Node* root;
    fullBinaryTree() { root = nullptr; }
};

// Используем шаблонную очередь для узлов дерева в ТИХОМ режиме
typedef Queue<Node*> QueueTree;

// Функции работы с деревом
void insert(fullBinaryTree* tree, int value);
void inorder(Node* node);
void preorder(Node* node);
void postorder(Node* node);
Node* BFS(fullBinaryTree* tree, int value);
void printBFS(fullBinaryTree* tree);
void deleteNode(fullBinaryTree* tree, int value);

#endif