#ifndef FULLBINARYTREE_H
#define FULLBINARYTREE_H

#include <iostream>
#include "Queue.h"
using namespace std;

// ���� ������
struct Node {
    int data;
    Node* left;
    Node* right;
};

// ������ �������� ������
struct fullBinaryTree {
    Node* root;
    fullBinaryTree() { root = nullptr; }
};

// ���������� ��������� ������� ��� ����� ������ � ����� ������
typedef Queue<Node*> QueueTree;

// ������� ������ � �������
void insert(fullBinaryTree* tree, int value);
void inorder(Node* node);
void preorder(Node* node);
void postorder(Node* node);
Node* BFS(fullBinaryTree* tree, int value);
void printBFS(fullBinaryTree* tree);
void deleteNode(fullBinaryTree* tree, int value);

#endif