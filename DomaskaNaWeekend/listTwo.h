#ifndef listTwo_H
#define listTwo_H

#include <string>

struct DoublyNode {
    std::string node;
    DoublyNode* next;
    DoublyNode* prev;
};

struct ForwardListTwo {
    DoublyNode* head;
    DoublyNode* tail;
};

enum PositionTwo { HEADTwo, TAILTwo, AFTERTwo, BEFORETwo };

void addNodeTwo(ForwardListTwo* flist, DoublyNode* target, const std::string& num, PositionTwo pos);
void deleteNodeTwo(ForwardListTwo* flist, DoublyNode* target, const std::string& num, PositionTwo pos);
bool deleteNodeIndexTwo(ForwardListTwo* flist, const std::string& num);
bool findNodeIndexTwo(ForwardListTwo* flist, const std::string& num);
void printListTwo(const ForwardListTwo& flist);
int countNodesTwo(const ForwardListTwo& flist);
DoublyNode* getNodeByIndexTwo(ForwardListTwo& flist, int index);

#endif