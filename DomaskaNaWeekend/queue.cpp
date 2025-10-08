#include "queue.h"

// Инициализация очереди
void initQueue(Queue* q, bool silentMode) {
    q->frontPtr = nullptr;
    q->rearPtr = nullptr;
    q->size = 0;
    q->silent = silentMode;
}

// Добавление элемента в очередь
void enqueue(Queue* q, const string& value) {
    QueueNode* newNode = new QueueNode;
    newNode->data = value;
    newNode->next = nullptr;

    if (isEmpty(q)) {
        // Очередь пуста - новый элемент становится и первым и последним
        q->frontPtr = newNode;
        q->rearPtr = newNode;
    }
    else {
        // Добавляем в конец очереди
        q->rearPtr->next = newNode;
        q->rearPtr = newNode;
    }

    q->size++;

    if (!q->silent) {
        cout << "Добавлен элемент: " << value << endl;
    }
}

// Удаление элемента из очереди
string dequeue(Queue* q) {
    if (isEmpty(q)) {
        if (!q->silent) {
            cout << "Очередь пуста!" << endl;
        }
        return "";
    }

    // Сохраняем данные первого элемента
    string value = q->frontPtr->data;

    // Удаляем первый элемент
    QueueNode* temp = q->frontPtr;
    q->frontPtr = q->frontPtr->next;

    // Если очередь стала пустой, обновляем rearPtr
    if (q->frontPtr == nullptr) {
        q->rearPtr = nullptr;
    }

    delete temp;
    q->size--;

    if (!q->silent) {
        cout << "Извлечен элемент: " << value << endl;
    }

    return value;
}

// Чтение первого элемента (без удаления)
string front(Queue* q) {
    if (isEmpty(q)) {
        if (!q->silent) {
            cout << "Очередь пуста!" << endl;
        }
        return "";
    }

    return q->frontPtr->data;
}

// Проверка на пустоту
bool isEmpty(Queue* q) {
    return q->frontPtr == nullptr;
}

// Получение размера очереди
int getSize(Queue* q) {
    return q->size;
}

// Вывод очереди
void printQueue(Queue* q) {
    if (isEmpty(q)) {
        cout << "Очередь пуста" << endl;
        return;
    }

    cout << "Очередь (первый -> последний): ";
    QueueNode* current = q->frontPtr;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Установка тихого режима
void setSilent(Queue* q, bool mode) {
    q->silent = mode;
}

// Очистка очереди
void clearQueue(Queue* q) {
    while (!isEmpty(q)) {
        dequeue(q);
    }
}