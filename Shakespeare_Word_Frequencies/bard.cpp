//Filename: bard.cpp
//
//This is the main function of the bard program that reads in an input file and prints the kth most common word of a given length.
//
//Devan O'Boyle, October 2021
#include <iostream>
#include "linkedlist.h"
#include <fstream>
#include <array>
#include <vector>
#include <sstream>
#include <cstring>

int main(int argc, char** argv) {
    ifstream input1;
    ifstream input2;
    ofstream output;

    //opens the input files
    input1.open(argv[1]);
    input2.open("shakespeare-cleaned5.txt");
    output.open(argv[2]);

    string command1;
    string command2;
    char *com, *dummy, *string_val1, *string_val2;
    int val1, val2;

    unsigned longest = 0;
    int sign_longest = 0;
    //determines the number of linked lists to use
    while (getline(input2, command1)) {
        if (command1.length() > longest) {
            longest = command1.length();
        }
    }
    input2.clear();
    input2.seekg(0, input2.beg);

    //there are no words with less than 5 letters
    longest -= 4;
    LinkedList* list_ll = new LinkedList[longest];

    //initializes all of the linked lists
    for (unsigned i = 0; i < longest; i++) {
        list_ll[i] = LinkedList();
        sign_longest += 1;
    }
    //iterate through the list of Shakespeare's words
    while (getline(input2, command1)) {
        //checks to see if the word is already is the linked list
        //if it doesn't insert the word into the linked list
        if (list_ll[command1.length() - 5].find_node(command1) == NULL) {
            list_ll[command1.length() - 5].insert(command1);
        }
        //otherwise update the frequency
        else {
            list_ll[command1.length() - 5].update(command1);
        }
    }
    //iterate through the user's input file
    while (getline(input1, command2)) {
        //tokenizes the first value and converts it to an int
        com = strdup(command2.c_str());
        string_val1 = strtok(com, " \t");
        if (string_val1 != NULL) {
            val1 = strtol(string_val1, &dummy, 10);
        }
        //checks to see if the given index has a linked list associated with it
        if (val1 > sign_longest + 4) {
            cout << "-" << endl;
            output << "-" << endl;
            continue;
        }
        if (list_ll[val1-5].exists() == true) {
            //if the linked list isn't already sorted then sort it
            if (list_ll[val1-5].return_sorted() == false) {
                list_ll[val1-5].mergeSortDummy();
            }
            //tokenize the second value and convert it to an int
            string_val2 = strtok(NULL, " \t");
            if (string_val2 != NULL) {
                val2 = strtol(string_val2, &dummy, 10);
            }
            //print the word from the given index
            cout << list_ll[val1-5].find_word(val2) << endl;
            output << list_ll[val1-5].find_word(val2) << endl;
        }
        else {
            cout << "-" << endl;
            output << "-" << endl;
        }
    }
    //deletes all of the linked lists
    for (unsigned i = 0; i < longest; i++) {
        list_ll[i].deleteList();
    }

    //closes the inputs and output files
    input1.close();
    input2.close();
    output.close();
}
