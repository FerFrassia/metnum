#include "Matrix.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

list<string> split(string originalString, char delim) {
    list<string> output;
    string current;
    stringstream stream(originalString);

    while (getline(stream, current, delim)) {
        output.push_back(current);
    }

    return output;
}

void Matrix::addLink(string originalString) {
    list<string> linkList = split(originalString, ' ');
    int referencingPage = stoi(linkList.front());
    int referencedPage = stoi(linkList.back());
    graph[referencingPage].push_back(referencedPage);
}

void Matrix::print() {
    for (unsigned long i = 0; i < graph.size(); ++i) {
        string page = "[" + to_string(i) + "]: ";
        list<int>::iterator it;
        for (it = graph[i].begin(); it != graph[i].end(); ++it) {
            int linkedPage = *it;
            page = page + "[" + to_string(linkedPage) + "] -> ";
        }
        cout << page + "\n" << endl;
    }
}

Matrix::Matrix(string file) {
    string line;
    ifstream myfile (file);
    if (myfile.is_open()) {
        getline(myfile, line); //number of pages
        list<int> emptyList;
        vector<list<int>> vect(stoi(line)+1, emptyList);
        graph = vect;
        
        getline(myfile, line); //number of links
        while(getline(myfile, line)) {
            addLink(line); //add each link
        }
        myfile.close();
    } else {
        cout << "unable to open file";
    }
}




