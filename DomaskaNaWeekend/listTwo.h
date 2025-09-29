#ifndef listTwo_H
#define listTwo_H

struct DoublyNode {
    int node;
    DoublyNode* next;
    DoublyNode* prev;  // ����� ��������� �� ���������� ����
};

struct ForwardListTwo {
    DoublyNode* head;
    DoublyNode* tail; // ��� ������� ������� � �����
};

enum PositionTwo {HEADTwo, TAILTwo, AFTERTwo, BEFORETwo};

void addNodeTwo(ForwardListTwo* flist, DoublyNode* target, int num, PositionTwo pos);

void deleteNodeTwo(ForwardListTwo* flist, DoublyNode* target, int num, PositionTwo pos);

bool deleteNodeIndexTwo(ForwardListTwo* flist, int num);

bool findNodeIndexTwo(ForwardListTwo* flist, int num);

void printListTwo(const ForwardListTwo& flist);

int countNodesTwo(const ForwardListTwo& flist);

DoublyNode* getNodeByIndexTwo(ForwardListTwo& flist, int index);

#endif