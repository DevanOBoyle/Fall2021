//Filename: linkedlist.h
//
//Header file for the class LinkedList that represents a linked list
//
//Devan O'Boyle, September 2021

#ifndef LIST_H
#define LIST_H

#include <string>

using namespace std;

struct Node {
    string data;
    Node *next;
    int frequency;
};

class LinkedList {
    private:
        Node *head;
        bool sorted;
    public:
        LinkedList();
        void insert(string);
        bool exists();
        Node* find_node(string);
        string find_word(int);
        void update(string);
        Node* deleteNode(string);
        void mergeSortDummy();
        void mergeSort(Node**);
        Node* sortedMerge(Node*, Node*);
        void split(Node*, Node**, Node**);
        bool return_sorted();
        void deleteList();
        void printList();
};

#endif
