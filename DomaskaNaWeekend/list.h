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

// Основные функции

bool deleteNod(ForwardList* flist, const std::string& num);
bool findNodeIndex(ForwardList* flist, const std::string& num);
void printList(const ForwardList& flist);
int countNodes(const ForwardList& flist);
linkedList* getNodeByIndex(const ForwardList& flist, int index);

void addNodeHead(ForwardList* flist, const std::string& num);
void addNodeTail(ForwardList* flist, const std::string& num);
void addNodeAfter(ForwardList* flist, linkedList* target, const std::string& num);
void addNodeBefore(ForwardList* flist, linkedList* target, const std::string& num);

void deleteNodeHead(ForwardList* flist);
void deleteNodeTail(ForwardList* flist);
void deleteNodeAfter(ForwardList* flist, linkedList* target);
void deleteNodeBefore(ForwardList* flist, linkedList* target);

bool deleteNodeIndex(ForwardList* flist, const std::string& num); 

#endif