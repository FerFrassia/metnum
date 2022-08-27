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

void Matrix::addLink(Matrix* matrix, string originalString) {
    list<string> linkList = split(originalString, ' ');
    int referencingPage = stoi(linkList.front());
    int referencedPage = stoi(linkList.back());
    matrix->graph[referencingPage].push_back(referencedPage);
}

void Matrix::print(Matrix* matrix) {
    for (unsigned long i = 0; i < matrix->graph.size(); ++i) {
        string page = "[" + to_string(i) + "]: ";
        list<int>::iterator it;
        for (it = matrix->graph[i].begin(); it != matrix->graph[i].end(); ++it) {
            int linkedPage = *it;
            page = page + "[" + to_string(linkedPage) + "] -> ";
        }
        cout << page + "\n" << endl;
    }
}

int Matrix::size() {
    return graph.size();
}

list<int> Matrix::get(Matrix* matrix, int column) {
    return matrix->graph[column];
}

Matrix::Matrix(string file) {
    /*
    generateW
    generateD
    multiply(W, D)
    generateI
    I - p w d | 1
*/
}

Matrix::Matrix() {

}

Matrix* Matrix::generateW(string file) {
    string line;
    ifstream myfile (file);
    Matrix *result = new Matrix();
    if (myfile.is_open()) {
        getline(myfile, line); //number of pages
        list<int> emptyList;
        vector<list<int>> vect(stoi(line)+1, emptyList);

        getline(myfile, line); //number of links
        while(getline(myfile, line)) {
            addLink(line); //add each link

        }
        myfile.close();
    } else {
        cout << "unable to open file";
    }
    return result;
}

vector<double> Matrix::generateD(Matrix w) {
    vector<double> res(w.size());
    for (int i = 0; i < w.size(); i++) {
        int c_j = w.get(w, i).size();
        res[i] = c_j == 0 ? 0 : 1/c_j;
    }
    return res;
}

vector<vector<double>> Matrix::multiply(Matrix w, vector<double> d) {
    int matrix_size = w.size();
    vector<vector<double>> result(matrix_size);
    for (int i = 0; i < w.size(); i++) {
        list<int> column_i = w.get(i);
        list<int>::iterator it = column_i.begin();
        for (int j = 0; j < matrix_size; j++) {
            if (j + 1 < *it) {
                result[i][j] = 0;
            } else {
                result[i][j] = d[i];
                it++;
            }
        }
    }
    return result;
}



