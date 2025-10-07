#include "FullBinaryTree.h"

// ----------------- ���������� ������ -----------------
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

    QueueTree q(100, true);
    q.enqueue(root);
    bool foundNull = false;

    while (!q.isEmpty()) {
        Node* temp = q.dequeue();

        if (!temp) {
            foundNull = true;
        }
        else {
            // ���� �� ��� ����� null-����, �� ��������� ��������� - ������ �� ������
            if (foundNull) return false;

            q.enqueue(temp->left);
            q.enqueue(temp->right);
        }
    }
    return true;
}

// �������� �� ������ ������ �������� ������ (Full/Strict Binary Tree)
bool isFullBinaryTree(Node* root) {
    if (!root) return true;

    // ���� � ���� ��� ����� - ��� ����, �� ��
    if (!root->left && !root->right) return true;

    // ���� � ���� ��� ������� - ���������� ��������� ��
    if (root->left && root->right) {
        return isFullBinaryTree(root->left) && isFullBinaryTree(root->right);
    }

    // ���� ������ ���� ������� - ������ �� ������ ������
    return false;
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
    cout << "���������� �����: ";

    // ������� �����
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

    cout << "������ ������: ";
    // ���������� ������
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

    cout << "��� ������: ";
    if (full) {
        cout << "������ ������ �������� ������" << endl;
        cout << "- ������ ���� ����� 0 ��� 2 �������" << endl;
    }
    else if (complete) {
        cout << "������ �������� ������" << endl;
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
void deleteNode(fullBinaryTree* tree, const string& value) {
    if (!tree->root) {
        cout << "������ �����!" << endl;
        return;
    }

    QueueTree q(10, true);
    q.enqueue(tree->root);

    Node* target = nullptr;
    Node* last = nullptr;
    Node* parentLast = nullptr;

    // ���� ���� ��� �������� � ��������� ����
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

    // ���� ���� �� ������
    if (!target) {
        cout << "���� � ������� '" << value << "' �� ������" << endl;
        return;
    }

    // ���� ������ ������� ������ �� �����
    if (tree->root == target && !tree->root->left && !tree->root->right) {
        delete tree->root;
        tree->root = nullptr;
        cout << "���� � ������� '" << value << "' �����" << endl;
        return;
    }

    // ���� ������� ��������� ����
    if (target == last) {
        // ������� �������� ���������� ����
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
        cout << "���� � ������� '" << value << "' �����" << endl;
        return;
    }

    // ����������� ������: �������� ������ � ������� ��������� ����
    target->data = last->data;

    // ������� �������� ���������� ����
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
        cout << "���� � ������� '" << value << "' �����" << endl;
    }
    else {
        cout << "������: �� ������� ����� �������� ����" << endl;
    }
}