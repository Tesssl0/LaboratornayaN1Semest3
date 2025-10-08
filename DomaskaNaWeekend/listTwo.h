#ifndef listTwo_H
#define listTwo_H

#include <string>
using namespace std;

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

// Основные функции
void addNodeTwo(ForwardListTwo* flist, DoublyNode* target, const std::string& num, PositionTwo pos);
void deleteNodeTwo(ForwardListTwo* flist, DoublyNode* target, const std::string& num, PositionTwo pos);
bool deleteNodTwo(ForwardListTwo* flist, const std::string& num);
bool findNodeIndexTwo(ForwardListTwo* flist, const std::string& num);
void printListTwo(const ForwardListTwo& flist);
int countNodesTwo(const ForwardListTwo& flist);
DoublyNode* getNodeByIndexTwo(ForwardListTwo& flist, int index);

// Новые функции без switch case
void addNodeHeadTwo(ForwardListTwo* flist, const std::string& num);
void addNodeTailTwo(ForwardListTwo* flist, const std::string& num);
void addNodeAfterTwo(ForwardListTwo* flist, DoublyNode* target, const std::string& num);
void addNodeBeforeTwo(ForwardListTwo* flist, DoublyNode* target, const std::string& num);

void deleteNodeHeadTwo(ForwardListTwo* flist);
void deleteNodeTailTwo(ForwardListTwo* flist);
void deleteNodeAfterTwo(ForwardListTwo* flist, DoublyNode* target);
void deleteNodeBeforeTwo(ForwardListTwo* flist, DoublyNode* target);

bool deleteNodeIndexTwo(ForwardListTwo* flist, const string& num);

#endif