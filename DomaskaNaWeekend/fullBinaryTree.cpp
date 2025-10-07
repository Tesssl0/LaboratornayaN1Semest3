#include "FullBinaryTree.h"

// ----------------- Реализация дерева -----------------
void insert(fullBinaryTree* tree, const string& value) {
    Node* newNode = new Node{ value, nullptr, nullptr };
    if (!tree->root) {
        tree->root = newNode;
        return;
    }
    QueueTree q(10, true);
    q.enqueue(tree->root);
    while (!q.isEmpty()) {
        Node* temp = q.dequeue();
        if (!temp->left) { temp->left = newNode; return; }
        else q.enqueue(temp->left);
        if (!temp->right) { temp->right = newNode; return; }
        else q.enqueue(temp->right);
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

Node* BFS(fullBinaryTree* tree, const string& value) {
    if (!tree->root) return nullptr;
    QueueTree q(10, true);
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
    QueueTree q(10, true);
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

    QueueTree q(100, true);
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
    cout << "Количество узлов: ";

    // Подсчет узлов
    int count = 0;
    QueueTree q(100, true);
    if (tree->root) q.enqueue(tree->root);
    while (!q.isEmpty()) {
        Node* temp = q.dequeue();
        count++;
        if (temp->left) q.enqueue(temp->left);
        if (temp->right) q.enqueue(temp->right);
    }
    cout << count << endl;

    cout << "Высота дерева: ";
    // Вычисление высоты
    QueueTree q2(100, true);
    int height = 0;
    if (tree->root) {
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
    cout << height << endl;

    cout << "Тип дерева: ";
    if (full) {
        cout << "СТРОГО ПОЛНОЕ БИНАРНОЕ ДЕРЕВО" << endl;
        cout << "- Каждый узел имеет 0 или 2 потомка" << endl;
    }
    else if (complete) {
        cout << "ПОЛНОЕ БИНАРНОЕ ДЕРЕВО" << endl;
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
void deleteNode(fullBinaryTree* tree, const string& value) {
    if (!tree->root) {
        cout << "Дерево пусто!" << endl;
        return;
    }

    QueueTree q(10, true);
    q.enqueue(tree->root);

    Node* target = nullptr;
    Node* last = nullptr;
    Node* parentLast = nullptr;

    // Ищем узел для удаления и последний узел
    while (!q.isEmpty()) {
        Node* temp = q.dequeue();

        if (temp->data == value) {
            target = temp;
        }

        if (temp->left) {
            parentLast = temp;
            q.enqueue(temp->left);
            last = temp->left;
        }
        if (temp->right) {
            parentLast = temp;
            q.enqueue(temp->right);
            last = temp->right;
        }
    }

    // Если узел не найден
    if (!target) {
        cout << "Узел с данными '" << value << "' не найден" << endl;
        return;
    }

    // Если дерево состоит только из корня
    if (tree->root == target && !tree->root->left && !tree->root->right) {
        delete tree->root;
        tree->root = nullptr;
        cout << "Узел с данными '" << value << "' удалён" << endl;
        return;
    }

    // Если удаляем последний узел
    if (target == last) {
        // Находим родителя последнего узла
        QueueTree q2(10, true);
        q2.enqueue(tree->root);
        Node* parent = nullptr;

        while (!q2.isEmpty()) {
            Node* temp = q2.dequeue();
            if (temp->left == last || temp->right == last) {
                parent = temp;
                break;
            }
            if (temp->left) q2.enqueue(temp->left);
            if (temp->right) q2.enqueue(temp->right);
        }

        if (parent) {
            if (parent->left == last) parent->left = nullptr;
            else if (parent->right == last) parent->right = nullptr;
        }
        delete last;
        cout << "Узел с данными '" << value << "' удалён" << endl;
        return;
    }

    // Стандартный случай: заменяем данные и удаляем последний узел
    target->data = last->data;

    // Находим родителя последнего узла
    QueueTree q3(10, true);
    q3.enqueue(tree->root);
    Node* parentOfLast = nullptr;

    while (!q3.isEmpty()) {
        Node* temp = q3.dequeue();
        if (temp->left == last || temp->right == last) {
            parentOfLast = temp;
            break;
        }
        if (temp->left) q3.enqueue(temp->left);
        if (temp->right) q3.enqueue(temp->right);
    }

    if (parentOfLast) {
        if (parentOfLast->left == last) {
            parentOfLast->left = nullptr;
        }
        else if (parentOfLast->right == last) {
            parentOfLast->right = nullptr;
        }
        delete last;
        cout << "Узел с данными '" << value << "' удалён" << endl;
    }
    else {
        cout << "Ошибка: не удалось найти родителя узла" << endl;
    }
}