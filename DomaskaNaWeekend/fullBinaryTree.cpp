#include "FullBinaryTree.h"

// ----------------- Реализация дерева -----------------
void insert(fullBinaryTree* tree, int value) {
    Node* newNode = new Node{ value, nullptr, nullptr };
    if (!tree->root) {
        tree->root = newNode;
        return;
    }
    QueueTree q(10, true); // ТИХИЙ режим для дерева
    q.enqueue(tree->root);
    while (!q.isEmpty()) {
        Node* temp = q.dequeue();
        if (!temp->left) { temp->left = newNode; return; }
        else q.enqueue(temp->left);
        if (!temp->right) { temp->right = newNode; return; }
        else q.enqueue(temp->right);
    }
}

void inorder(Node* node) {
    if (!node) return;
    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}

void preorder(Node* node) {
    if (!node) return;
    cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
}

void postorder(Node* node) {
    if (!node) return;
    postorder(node->left);
    postorder(node->right);
    cout << node->data << " ";
}

Node* BFS(fullBinaryTree* tree, int value) {
    if (!tree->root) return nullptr;
    QueueTree q(10, true); // ТИХИЙ режим для дерева
    q.enqueue(tree->root);
    while (!q.isEmpty()) {
        Node* temp = q.dequeue();
        if (temp->data == value) return temp;
        if (temp->left) q.enqueue(temp->left);
        if (temp->right) q.enqueue(temp->right);
    }
    return nullptr;
}

void printBFS(fullBinaryTree* tree) {
    if (!tree->root) return;
    QueueTree q(10, true); // ТИХИЙ режим для дерева
    q.enqueue(tree->root);
    cout << "Обход в ширину: ";
    while (!q.isEmpty()) {
        Node* temp = q.dequeue();
        cout << temp->data << " ";
        if (temp->left) q.enqueue(temp->left);
        if (temp->right) q.enqueue(temp->right);
    }
    cout << endl;
}

void deleteNode(fullBinaryTree* tree, int value) {
    if (!tree->root) return;
    QueueTree q(10, true); // ТИХИЙ режим для дерева
    q.enqueue(tree->root);

    Node* target = nullptr;
    Node* last = nullptr;
    Node* parentLast = nullptr;

    while (!q.isEmpty()) {
        Node* temp = q.dequeue();
        if (temp->data == value) target = temp;
        if (temp->left) { parentLast = temp; q.enqueue(temp->left); last = temp->left; }
        if (temp->right) { parentLast = temp; q.enqueue(temp->right); last = temp->right; }
    }

    if (!target) { cout << "Узел с данными " << value << " не найден" << endl; return; }

    target->data = last->data;
    if (parentLast->right == last) parentLast->right = nullptr;
    else if (parentLast->left == last) parentLast->left = nullptr;

    delete last;
    cout << "Узел с данными " << value << " удалён" << endl;
}