//Filename: linkedlist.cpp
//
//This file contains the function implementations for the LinkedList class
//
//Devan O'Boyle, October 2021

#include "linkedlist.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

LinkedList :: LinkedList() {
    head = NULL;
    sorted = false;
}

//checks to see if the linked list exists or not
bool LinkedList :: exists() {
    if (head != NULL) {
        return true;
    }
    return false;
}
void LinkedList :: insert(string word) {
    //creates a new node with the given data from string input
    Node *insert_node = new Node;
    insert_node->data = word;
    //inserts the word at the head of the linked list
    insert_node->next = head;
    head = insert_node;
}

//given a word, return the corresponding node
Node* LinkedList :: find_node(string word) {
    Node *curr = head;
    while (curr != NULL) {
        if (curr->data == word) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

//given an index, return the corresponding word at that node
string LinkedList :: find_word(int val) {
    Node *curr = head;
    int i = 0;
    while (curr != NULL) {
        //if the index matches
        if (i == val) {
            //return the word
            return curr->data;
        }
        curr = curr->next;
        i += 1;
    }
    //otherwise return a dash to indicate no corresponding word
    return "-";
}

//increments the frequency of one of Shakespeare's words
void LinkedList :: update(string word) {
    Node *found_word = find_node(word);
    found_word->frequency += 1;
}

//deletes the node that contains one of Shakespeare's words
Node* LinkedList :: deleteNode(string word) {
    Node *curr = head;
    Node *prev = NULL;
    while (curr != NULL) {
        if (curr->data == word) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        return NULL;
    }
    if (prev == NULL) {
        head = head->next;
    }
    else {
        prev->next = curr->next;
    }
    return curr;
}

//dummy function to call the recursive merge sort function
void LinkedList :: mergeSortDummy() {
    if (head != NULL) {
        Node* input = head;
        mergeSort(&input);
        head = input;
        sorted = true;
    }
}

void LinkedList :: mergeSort(Node** start) {
    Node* s = *start;
    Node* first;
    Node* second;
    if (s == NULL || s->next == NULL) {
        return;
    }
    //split the function into two
    split(s, &first, &second);

    mergeSort(&first);
    mergeSort(&second);
    *start = sortedMerge(first, second);
}

Node* LinkedList :: sortedMerge(Node* first, Node* second) {
    Node* result = NULL;
    if (first == NULL) {
        return second;
    }
    else if (second == NULL) {
        return first;
    }
    //find which node has the greater frequency, and return it
    //then call the function again with the greater node's next
    //to continue comparing the node's until they have been merged completely
    if (first->frequency > second->frequency) {
        result = first;
        result->next = sortedMerge(first->next, second);
    }
    else if (first->frequency == second->frequency) {
        if (first->data < second->data) {
            result = first;
            result->next = sortedMerge(first->next, second);
        }
        else {
            result = second;
            result->next = sortedMerge(first, second->next);
        }
    }
    else {
        result = second;
        result->next = sortedMerge(first, second->next);
    }
    return result;
}

void LinkedList :: split(Node* start, Node** first, Node** second) {
    Node* curr;
    Node* prev;
    prev = start;
    curr = start->next;

    //iterate through
    while (curr != NULL) {
        curr = curr->next;
        if (curr != NULL) {
            prev = prev->next;
            curr = curr->next;
        }
    }
    //first becomes the start node
    *first = start;
    //second becomes the mid point node
    *second = prev->next;
    prev->next = NULL;

}

bool LinkedList :: return_sorted() {
    return sorted;
}

void LinkedList :: deleteList() {
    Node *curr = head;
    Node *temp = NULL;

    //iterate through each node and delete it
    while (curr != NULL) {
        temp = curr->next;
        delete(curr);
        curr = temp;
    }
    head = NULL;
    return;
}

//prints each word in the linked list for debugging purposes
void LinkedList :: printList() {
    Node* curr = head;
    while (curr != NULL) {
        cout << head->data << endl;
        curr = curr->next;
    }
}
