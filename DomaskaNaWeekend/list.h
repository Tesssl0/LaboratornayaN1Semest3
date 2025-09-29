#ifndef list_H
#define list_H

struct linkedList
{
    int node;
    linkedList* next;
};

struct ForwardList
{
    linkedList* head;
};

enum Position { HEAD, TAIL, AFTER, BEFORE };

void addNode(ForwardList* flist, linkedList* target, int num, Position pos);

void deleteNode(ForwardList* flist, linkedList* target, int num, Position pos);

bool deleteNodeIndex(ForwardList* flist, int num);

bool findNodeIndex(ForwardList* flist, int num);


void printList(const ForwardList& flist);

// Подсчёт количества узлов в списке
int countNodes(const ForwardList& flist);

// Получение указателя на узел по индексу
linkedList* getNodeByIndex(const ForwardList& flist, int index);

#endif
