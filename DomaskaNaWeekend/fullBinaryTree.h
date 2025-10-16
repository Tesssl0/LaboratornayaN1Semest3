#pragma once
#ifndef FULLBINARYTREE_H
#define FULLBINARYTREE_H
#include <iostream>
#include <string>

using namespace std;

// ��������� ���� ������
struct Node {
    string data;  // ����������: ���� value, ������ ���� data
    Node* left;
    Node* right;

    Node(const string& val) : data(val), left(nullptr), right(nullptr) {}  // ����������: data ������ value
};

// ��������� ��������� ������
struct fullBinaryTree {
    Node* root = nullptr;

    // ��������� ����������� �� ���������
    fullBinaryTree() : root(nullptr) {}
};

// �������� �������� � �������
void insertBST(fullBinaryTree* tree, const string& value);
Node* BFS(fullBinaryTree* tree, const string& value);

// ������ ������
void inorder(Node* node);
void preorder(Node* node);
void postorder(Node* node);
void printBFS(fullBinaryTree* tree);

// ������� ������
void clearTree(Node* node);
void clearFullBinaryTree(fullBinaryTree* tree);

// �������� ����� ��������
bool isCompleteBinaryTree(Node* root);
bool isFullBinaryTree(Node* root);
void checkTreeType(fullBinaryTree* tree);
string getBFSAsString(fullBinaryTree* tree);
string getInorderAsString(Node* node);

#endif