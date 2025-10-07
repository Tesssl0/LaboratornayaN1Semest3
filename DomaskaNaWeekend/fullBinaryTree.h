#ifndef FULLBINARYTREE_H
#define FULLBINARYTREE_H

#include <iostream>
#include <string>
#include "Queue.h"
using namespace std;

// ���� ������
struct Node {
    string data;
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
void insert(fullBinaryTree* tree, const string& value);
void inorder(Node* node);
void preorder(Node* node);
void postorder(Node* node);
Node* BFS(fullBinaryTree* tree, const string& value);
void printBFS(fullBinaryTree* tree);
void deleteNode(fullBinaryTree* tree, const string& value);
void clearTree(Node* node);
void clearFullBinaryTree(fullBinaryTree* tree);
// ������� �������� �� ������ �������� ������
bool isCompleteBinaryTree(Node* root);
bool isFullBinaryTree(Node* root);
void checkTreeType(fullBinaryTree* tree);
#endif