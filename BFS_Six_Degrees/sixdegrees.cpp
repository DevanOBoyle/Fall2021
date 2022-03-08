//Filename: sixdegrees.cpp
//
//This file is the main executable of the six degrees function finds the shortest path between two actors through
//other actors that they starred in the same movie with
//
//Devan O'Boyle, Nov 2021

#include <iostream>
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <unordered_map>
#include <utility>
#include <queue>

using namespace std;

//runs breadth first search to find the shortest path between two actors
string shortest_path(unordered_map<string, vector<pair<string, string>>> g, string s1, string s2) {
    queue<pair<string, string>> Q;
    Q.push(make_pair(s1, ""));

    unordered_map<string, pair<string, string>> preds;
    unordered_map<string, bool> visited;

    string shortest = "";

    while (!Q.empty()) {
        pair<string, string> top = Q.front();
        pair<string, string> previous = top;
        Q.pop();
        if (top.first == s2) {
            pair<string, string> current = top;
            while (current.first != s1) {
                shortest = " -(" + current.second + ")- " + current.first + shortest;
                previous = current;
                current = preds[current.first];
            }
            shortest = current.first + shortest;
            return shortest;
        }
        for (unsigned i = 0; i < g[top.first].size(); i++) {
            if (visited.find(g[top.first][i].first) == visited.end()) {
                visited[g[top.first][i].first] = true;
                preds[g[top.first][i].first] = top;
                Q.push(g[top.first][i]);
            }
        }
    }
    return "Not present";
}

int main(int argc, char** argv) {
    if (argc < 3) {
        throw std :: invalid_argument("Usage: ./sixdegrees <INPUT FILE> <OUTPUT FILE>");
    }

    ifstream input1;
    ifstream input2;
    ofstream output;

    input1.open(argv[1]);
    input2.open("cleaned_movielist.txt");
    output.open(argv[2]);

    string command1;
    string command2;
    char *com1, *com2, *movie, *string_val;
    string string1, string2;

    unordered_map<string, vector<pair<string, string>>> graph;

    while (getline(input2, command1)) {
        com1 = strdup(command1.c_str());
        movie = strtok(com1, " \t");
        vector<string> actors;
        while ((string_val = strtok(NULL, " \t")) != NULL) {
            actors.push_back(string_val);
        }
        for (unsigned i = 0; i < actors.size(); i++) {
            for (unsigned j = 0; j < actors.size(); j++) {
                if (actors[i] != actors[j]) {
                    graph[actors[i]].push_back(make_pair(actors[j], movie));
                }
            }
        }
    }
    while (getline(input1, command2)) {
        com2 = strdup(command2.c_str());
        string1 = strtok(com2, " \t");
        string2 = strtok(NULL, " \t");
        if (graph.find(string1) == graph.end() || graph.find(string2) == graph.end()) {
            cout << "Not present" << endl;
            output << "Not present" << endl;
        }
        else if (string1 == string2) {
            cout << string1 << endl;
            output << string1 << endl;
        }
        else {
            string s = shortest_path(graph, string1, string2);
            cout << s << endl;
            output << s << endl;
        }
    }
    input1.close();
    input2.close();
    output.close();
}
