#ifndef list_H
#define list_H

#include <string>

struct linkedList
{
    std::string node;
    linkedList* next;
};

struct ForwardList
{
    linkedList* head;
};

enum Position { HEAD, TAIL, AFTER, BEFORE };

void addNode(ForwardList* flist, linkedList* target, const std::string& num, Position pos);
void deleteNode(ForwardList* flist, linkedList* target, const std::string& num, Position pos);
bool deleteNodeIndex(ForwardList* flist, const std::string& num);
bool findNodeIndex(ForwardList* flist, const std::string& num);
void printList(const ForwardList& flist);
int countNodes(const ForwardList& flist);
linkedList* getNodeByIndex(const ForwardList& flist, int index);

#endif
