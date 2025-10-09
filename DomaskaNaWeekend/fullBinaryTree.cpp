#include "fullBinaryTree.h"
#include <iostream>
#include <string>

using namespace std;

struct QueueNode {
    Node* treeNode;      // ��������� �� ���� ������
    QueueNode* next; // ��������� �� ��������� ���� � �������

    QueueNode(Node* node) : treeNode(node), next(nullptr) {}    // �����������
};

struct SimpleQueue {
    QueueNode* front; 
    QueueNode* rear;
    int size;

    SimpleQueue() : front(nullptr), rear(nullptr), size(0) {}

    ~SimpleQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(Node* node) {
        QueueNode* newNode = new QueueNode(node);
        if (rear == nullptr) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    Node* dequeue() {
        if (front == nullptr) return nullptr;

        QueueNode* temp = front;
        Node* node = temp->treeNode;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
        size--;
        return node;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    int getSize() {
        return size;
    }
};

// ������� �������� � ������ (������� �� �������)
void insertBinary(fullBinaryTree* tree, const string& value) {
    Node* newNode = new Node(value);

    if (!tree->root) {
        tree->root = newNode;
        return;
    }

    // ���� ����� ��� �������, ��������� �������� ��� �����
    Node* current = tree->root;
    Node* parent = nullptr;

    while (current != nullptr) {
        parent = current;

        // ����������� ������ � ����� ��� ���������
        int valueNum = stoi(value);
        int currentNum = stoi(current->data);

        if (valueNum < currentNum) {
            current = current->left;
        }
        else if (valueNum > currentNum) {
            current = current->right;
        }
        else {
            // ���� �������� ��� ����������, �� ��������� ��������
            delete newNode;
            return;
        }
    }

    // ��������� ����� ����
    int valueNum = stoi(value);
    int parentNum = stoi(parent->data);

    if (valueNum < parentNum) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }
}
string getBFSAsString(fullBinaryTree* tree) {
    string result;
    if (!tree->root) return result;

    SimpleQueue q;
    q.enqueue(tree->root);

    while (!q.isEmpty()) {
        Node* temp = q.dequeue();
        result += temp->data + " ";

        if (temp->left) q.enqueue(temp->left);
        if (temp->right) q.enqueue(temp->right);
    }

    if (!result.empty()) {
        result.pop_back(); // ������� ��������� ������
    }
    return result;
}


// ����������� ������� ������
void clearTree(Node* node) {
    if (node == nullptr) return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

// ������� ����� ������
void clearFullBinaryTree(fullBinaryTree* tree) {
    clearTree(tree->root);
    tree->root = nullptr;
}

// ������������ ����� (�����-������-������)
void inorder(Node* node) {
    if (!node) return;
    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}

// ������ ����� (������-�����-������)
void preorder(Node* node) {
    if (!node) return;
    cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
}

// �������� ����� (�����-������-������)
void postorder(Node* node) {
    if (!node) return;
    postorder(node->left);
    postorder(node->right);
    cout << node->data << " ";
}

// ����� � ������ (BFS)
Node* BFS(fullBinaryTree* tree, const string& value) {
    if (!tree->root) return nullptr;

    SimpleQueue q;
    q.enqueue(tree->root);

    while (!q.isEmpty()) {
        Node* temp = q.dequeue();
        if (temp->data == value) return temp;

        if (temp->left) q.enqueue(temp->left);
        if (temp->right) q.enqueue(temp->right);
    }

    return nullptr;
}

// ����� ������ � ������
void printBFS(fullBinaryTree* tree) {
    if (!tree->root) {
        cout << "������ ������" << endl;
        return;
    }

    SimpleQueue q;
    q.enqueue(tree->root);

    cout << "����� � ������: ";
    while (!q.isEmpty()) {
        Node* temp = q.dequeue();
        cout << temp->data << " ";

        if (temp->left) q.enqueue(temp->left);
        if (temp->right) q.enqueue(temp->right);
    }
    cout << endl;
}

// �������� �� ������ �������� ������ (Complete Binary Tree)
bool isCompleteBinaryTree(Node* root) {
    if (!root) return true;

    SimpleQueue q;
    q.enqueue(root);
    bool foundNull = false;

    while (!q.isEmpty()) {
        Node* temp = q.dequeue();

        // ��������� ������ �������
        if (temp->left) {
            if (foundNull) return false;  // ����� ���� ����� null
            q.enqueue(temp->left);
        }
        else {
            foundNull = true;
        }

        // ��������� ������� �������
        if (temp->right) {
            if (foundNull) return false;  // ����� ���� ����� null
            q.enqueue(temp->right);
        }
        else {
            foundNull = true;
        }
    }
    return true;
}
// �������� �� ������ ������ �������� ������ (Full/Strict Binary Tree)
bool isFullBinaryTree(Node* root) {
    if (!root) return true;

    // ���� � ���� ��� ����� - ��� ����
    if (!root->left && !root->right) return true;

    // ���� � ���� ��� ������� - ��������� ����������
    if (root->left && root->right) {
        return isFullBinaryTree(root->left) && isFullBinaryTree(root->right);
    }

    // ���� ������ ���� ������� - �� ������ ������
    return false;
}
// ����������� ������� ��� ��������� inorder � ���� ������
void getInorderHelper(Node* node, string& result) {
    if (!node) return;
    getInorderHelper(node->left, result);
    result += node->data + " ";
    getInorderHelper(node->right, result);
}

string getInorderAsString(Node* node) {
    string result;
    getInorderHelper(node, result);
    if (!result.empty()) {
        result.pop_back(); // ������� ��������� ������
    }
    return result;
}
// ������� ��� �������� � ������ ���� ������
void checkTreeType(fullBinaryTree* tree) {
    if (!tree->root) {
        cout << "������ ������" << endl;
        return;
    }

    bool complete = isCompleteBinaryTree(tree->root);
    bool full = isFullBinaryTree(tree->root);

    cout << "=== ������ ������ ===" << endl;

    // ������� �����
    int count = 0;
    SimpleQueue q;
    if (tree->root) q.enqueue(tree->root);
    while (!q.isEmpty()) {
        Node* temp = q.dequeue();
        count++;
        if (temp->left) q.enqueue(temp->left);
        if (temp->right) q.enqueue(temp->right);
    }
    cout << "���������� �����: " << count << endl;

    // ���������� ������
    int height = 0;
    if (tree->root) {
        SimpleQueue q2;
        q2.enqueue(tree->root);

        while (!q2.isEmpty()) {
            int levelSize = q2.getSize();
            for (int i = 0; i < levelSize; i++) {
                Node* temp = q2.dequeue();
                if (temp->left) q2.enqueue(temp->left);
                if (temp->right) q2.enqueue(temp->right);
            }
            height++;
        }
    }
    cout << "������ ������: " << height << endl;

    cout << "��� ������: ";
    if (full) { 
        cout << "������ ������ �������� ������ (Full/Strict Binary Tree)" << endl;
        cout << "- ������ ���� ����� 0 ��� 2 �������" << endl;
    }
    else if (complete) {
        cout << "�� ������ �������� ������ (Complete Binary Tree)" << endl;
        cout << "- ��� ������ ��������� ���������, ����� ����������" << endl;
        cout << "- ��������� ������� �������� ����� �������" << endl;
    }
    else {
        cout << "������� �������� ������" << endl;
        cout << "- �� ������������� ��������� ������� ��������� ������" << endl;
    }

    // �������������� ����������
    cout << "������������ ���������� ����� ��� ������ " << height << ": " << ((1 << height) - 1) << endl;
    cout << "����������� ���������� �����: " << count << endl;

    if (complete && count == ((1 << height) - 1)) {
        cout << "������ �������� ��������� �������� �������!" << endl;
    }
}

// �������� ���� �� ������
void deleteNode(fullBinaryTree* tree, const string& value) {
    if (!tree->root) {
        cout << "������ �����!" << endl;
        return;
    }

    // ���� ������� ������ � �� ������������ ����
    if (tree->root->data == value && !tree->root->left && !tree->root->right) {
        delete tree->root;
        tree->root = nullptr;
        cout << "���� '" << value << "' �����" << endl;
        return;
    }

    SimpleQueue q;
    q.enqueue(tree->root);

    Node* target = nullptr;
    Node* last = nullptr;
    Node* parentOfLast = nullptr;

    // ������� ���� ��� �������� � ��������� ����
    while (!q.isEmpty()) {
        Node* temp = q.dequeue();

        if (temp->data == value) {
            target = temp;
        }

        if (temp->left) {
            parentOfLast = temp;
            last = temp->left;
            q.enqueue(temp->left);
        }
        if (temp->right) {
            parentOfLast = temp;
            last = temp->right;
            q.enqueue(temp->right);
        }
    }

    if (!target) {
        cout << "���� '" << value << "' �� ������" << endl;
        return;
    }

    // �������� ������ �������� ���� ������� ���������� ����
    target->data = last->data;

    // ������� ��������� ����
    if (parentOfLast->left == last) {
        parentOfLast->left = nullptr;
    }
    else {
        parentOfLast->right = nullptr;
    }

    delete last;
    cout << "���� '" << value << "' �����" << endl;
}


/*

./dbms --file file.data --query "CLEAR_ALL"
./dbms --file file.data --query "TINSERT_BINARY W 4"
./dbms --file file.data --query "TINSERT_BINARY W 2"
./dbms --file file.data --query "TINSERT_BINARY W 6"
./dbms --file file.data --query "TINSERT_BINARY W 1"
./dbms --file file.data --query "TINSERT_BINARY W 3"
./dbms --file file.data --query "TINSERT_BINARY W 5"
./dbms --file file.data --query "TINSERT_BINARY W 7"
./dbms --file file.data --query "TCHECK W"
./dbms --file file.data --query "PRINT T W"

*/