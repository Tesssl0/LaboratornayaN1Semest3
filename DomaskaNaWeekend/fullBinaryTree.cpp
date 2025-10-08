#include "fullBinaryTree.h"
#include <iostream>
#include <string>

using namespace std;

struct QueueNode {
    Node* treeNode;
    QueueNode* next;

    QueueNode(Node* node) : treeNode(node), next(nullptr) {}
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

// Вставка элемента в дерево (уровень за уровнем)
void insert(fullBinaryTree* tree, const string& value) {
    Node* newNode = new Node(value);

    if (!tree->root) {
        tree->root = newNode;
        return;
    }

    SimpleQueue q;
    q.enqueue(tree->root);

    while (!q.isEmpty()) {
        Node* temp = q.dequeue();

        if (!temp->left) {
            temp->left = newNode;
            return;
        }
        else {
            q.enqueue(temp->left);
        }

        if (!temp->right) {
            temp->right = newNode;
            return;
        }
        else {
            q.enqueue(temp->right);
        }
    }
}

// Рекурсивная очистка дерева
void clearTree(Node* node) {
    if (node == nullptr) return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

// Очистка всего дерева
void clearFullBinaryTree(fullBinaryTree* tree) {
    clearTree(tree->root);
    tree->root = nullptr;
}

// Симметричный обход (левый-корень-правый)
void inorder(Node* node) {
    if (!node) return;
    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}

// Прямой обход (корень-левый-правый)
void preorder(Node* node) {
    if (!node) return;
    cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
}

// Обратный обход (левый-правый-корень)
void postorder(Node* node) {
    if (!node) return;
    postorder(node->left);
    postorder(node->right);
    cout << node->data << " ";
}

// Поиск в ширину (BFS)
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

// Вывод дерева в ширину
void printBFS(fullBinaryTree* tree) {
    if (!tree->root) {
        cout << "Дерево пустое" << endl;
        return;
    }

    SimpleQueue q;
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

// Проверка на полное бинарное дерево (Complete Binary Tree)
bool isCompleteBinaryTree(Node* root) {
    if (!root) return true;

    SimpleQueue q;
    q.enqueue(root);
    bool foundNull = false;

    while (!q.isEmpty()) {
        Node* temp = q.dequeue();

        if (!temp) {
            foundNull = true;
        }
        else {
            // Если мы уже нашли null-узел, но встречаем ненулевой - дерево не полное
            if (foundNull) return false;

            q.enqueue(temp->left);
            q.enqueue(temp->right);
        }
    }
    return true;
}

// Проверка на строго полное бинарное дерево (Full/Strict Binary Tree)
bool isFullBinaryTree(Node* root) {
    if (!root) return true;

    // Если у узла нет детей - это лист, всё ок
    if (!root->left && !root->right) return true;

    // Если у узла оба ребенка - рекурсивно проверяем их
    if (root->left && root->right) {
        return isFullBinaryTree(root->left) && isFullBinaryTree(root->right);
    }

    // Если только один ребенок - дерево не строго полное
    return false;
}

// Функция для проверки и вывода типа дерева
void checkTreeType(fullBinaryTree* tree) {
    if (!tree->root) {
        cout << "Дерево пустое" << endl;
        return;
    }

    bool complete = isCompleteBinaryTree(tree->root);
    bool full = isFullBinaryTree(tree->root);

    cout << "=== АНАЛИЗ ДЕРЕВА ===" << endl;

    // Подсчет узлов
    int count = 0;
    SimpleQueue q;
    if (tree->root) q.enqueue(tree->root);
    while (!q.isEmpty()) {
        Node* temp = q.dequeue();
        count++;
        if (temp->left) q.enqueue(temp->left);
        if (temp->right) q.enqueue(temp->right);
    }
    cout << "Количество узлов: " << count << endl;

    // Вычисление высоты
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
    cout << "Высота дерева: " << height << endl;

    cout << "Тип дерева: ";
    if (full) {
        cout << "СТРОГО ПОЛНОЕ БИНАРНОЕ ДЕРЕВО (Full/Strict Binary Tree)" << endl;
        cout << "- Каждый узел имеет 0 или 2 потомка" << endl;
    }
    else if (complete) {
        cout << "ПОЛНОЕ БИНАРНОЕ ДЕРЕВО (Complete Binary Tree)" << endl;
        cout << "- Все уровни полностью заполнены, кроме последнего" << endl;
        cout << "- Последний уровень заполнен слева направо" << endl;
    }
    else {
        cout << "ОБЫЧНОЕ БИНАРНОЕ ДЕРЕВО" << endl;
        cout << "- Не удовлетворяет критериям полного бинарного дерева" << endl;
    }

    // Дополнительная информация
    cout << "Максимальное количество узлов для высоты " << height << ": " << ((1 << height) - 1) << endl;
    cout << "Фактическое количество узлов: " << count << endl;

    if (complete && count == ((1 << height) - 1)) {
        cout << "Дерево является ИДЕАЛЬНЫМ бинарным деревом!" << endl;
    }
}

// Удаление узла из дерева
void deleteNode(fullBinaryTree* tree, const string& value) {
    if (!tree->root) {
        cout << "Дерево пусто!" << endl;
        return;
    }

    // Если удаляем корень и он единственный узел
    if (tree->root->data == value && !tree->root->left && !tree->root->right) {
        delete tree->root;
        tree->root = nullptr;
        cout << "Узел '" << value << "' удалён" << endl;
        return;
    }

    SimpleQueue q;
    q.enqueue(tree->root);

    Node* target = nullptr;
    Node* last = nullptr;
    Node* parentOfLast = nullptr;

    // Находим узел для удаления и последний узел
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
        cout << "Узел '" << value << "' не найден" << endl;
        return;
    }

    // Заменяем данные целевого узла данными последнего узла
    target->data = last->data;

    // Удаляем последний узел
    if (parentOfLast->left == last) {
        parentOfLast->left = nullptr;
    }
    else {
        parentOfLast->right = nullptr;
    }

    delete last;
    cout << "Узел '" << value << "' удалён" << endl;
}