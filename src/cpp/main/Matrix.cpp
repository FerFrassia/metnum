#include "Matrix.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

namespace MatrixBuilder {

    list<string> split(string originalString, char delim) {
        list<string> output;
        string current;
        stringstream stream(originalString);

        while (getline(stream, current, delim)) {
            output.push_back(current);
        }

        return output;
    }

    void addLink(InputMatrix &W, string originalString) {
        list<string> linkList = split(originalString, ' ');
        int referencingPage = stoi(linkList.front());
        int referencedPage = stoi(linkList.back());
        W.graph[referencedPage - 1][referencingPage - 1] = 1;
        W.grade[referencingPage - 1] = W.grade[referencingPage - 1] + 1;
    }

    /*
     * Usamos un map<int, map<int, double>> para ordenar. Podemos probar otra estructura despues
     */
    extern InputMatrix buildW(string file) {
        string line;
        ifstream myfile (file);
        InputMatrix result;
        if (myfile.is_open()) {
            getline(myfile, line); //number of pages
            int numberOfPages = stoi(line);
            vector<int> grades(numberOfPages);
            result.grade = grades;

            getline(myfile, line); //number of links
            while(getline(myfile, line)) {
                addLink(result, line); //add each link
            }
            myfile.close();
        } else {
            cout << "unable to open file";
        }
        return result;
    }

    void printMatrixValues(coordinateList &graph) {
        cout << "Graph size: " << graph.size() << endl;
        for (unsigned long i = 0; i < graph.size(); ++i) {
            string page = "[" + to_string(i) + "]: ";
            map<int, double> m = graph[i];
            for (map<int, double>::iterator iter = m.begin(); iter != m.end(); ++iter) {
                page += + "[(" + to_string(iter->first) + ", " + to_string(iter->second) + ")] -> ";
            }
            cout << page + "\n" << endl;
        }
    }

    void printGrades(vector<int> &matrixGrades) {
        string grades = "Grades: [";
        for (unsigned long j = 0; j < matrixGrades.size(); j++) {
            grades += to_string(matrixGrades[j]);
            if (j < matrixGrades.size() - 1) {
                grades += ", ";
            }
        }
        grades += "]";
        cout << grades << endl;
    }

    extern void printInputMatrix(InputMatrix &input) {
        printMatrixValues(input.graph);
        printGrades(input.grade);
    }

    CSR buildD(InputMatrix &W) {

    }

    CSR convertInputMatrixToCsr(InputMatrix W) {
        coordinateList graph = W.graph;
        int m = graph.size();
        CSR result;
//        vi A;
//        vi IA = { 0 }; // IA matrix has N+1 rows
//        vi JA;
        int NNZ, i = 0;


        for (i = 0; i < m; i++) {
            int n = graph[i].size();
            list<int>::iterator it;
            int j = 0;
//            for (it = W[i].begin(); it != W[i].end(); ++it) {
//                int rowInJColumn = *it;
////                if (W[i][j] != 0) {
//                    result.A.push_back(rowInJColumn);
//                    result.JA.push_back(j);
//
//                    // Count Number of Non Zero
//                    // Elements in row i
//                    j++;
//                    NNZ++;
////                }
//            }
            result.IA.push_back(NNZ);
        }

//        printMatrix(M);
//        printAVector(result.A, (char*)"A = ");
//        printVector(result.JA, (char*)"JA = ");
//        printVector(result.IA, (char*)"IA = ");
    }

    void printAVector(vector<double>& V, char* msg)
    {

        cout << msg << "[ ";
        for_each(V.begin(), V.end(), [](int a) {
            cout << a << " ";
        });
        cout << "]" << endl;
    }

    void printVector(vector<int>& V, char* msg)
    {

        cout << msg << "[ ";
        for_each(V.begin(), V.end(), [](int a) {
            cout << a << " ";
        });
        cout << "]" << endl;
    }

    CSR createIdentity(int size) {

    }

}

namespace MatrixOperator {

    CSR multiply(InputMatrix &W, InputMatrix &D) {

    }

    CSR scale(CSR &M, int s) {

    }

    CSR add(CSR &A, CSR &B) {

    }
}