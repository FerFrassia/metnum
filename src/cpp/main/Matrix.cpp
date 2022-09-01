#include "Matrix.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;
using namespace MatrixBuilder;
using namespace MatrixOperator;
using namespace MatrixPrinter;

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
    InputMatrix buildW(string file) {
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

    diagonalMatrix buildD(InputMatrix &W) {
        diagonalMatrix D(W.grade.size());
        for (double i = 0; i < D.size(); ++i) {
            D[i] = double(W.grade[i]) == 0 ? 0 : 1 / double(W.grade[i]);
        }
        return D;
    }

    CSR convertInputMatrixToCsr(InputMatrix &W) {
        /*prints de debug
        printf("about to convert input matrix: \n");
        printInputMatrix(W);
        */

        CSR result;
        int ia_i = 0;
        for (double i = 0; i < W.grade.size(); ++i) { //esto se puede escribir con un iterador, y el siguiente acceso es O(1) en lugar de O(logn), pero hace falta que todas las claves estén definidas en el primer map, aunque sea con un map vacío asociado.
            if (W.graph.find(i) != W.graph.end()) {
                for (map<int, double>::iterator referencingIterator = W.graph[i].begin(); referencingIterator != W.graph[i].end(); ++referencingIterator) {
                    result.A.push_back(referencingIterator->second);
                    result.JA.push_back(referencingIterator->first);
                    ia_i+= 1;
                }
            }
            result.IA.push_back(ia_i);
        }

        return result;
    }

    vvMatrix convertCSRTovvMatrix(CSR &M) {
        vvMatrix result;
        int n = M.IA.size() - 1;
        for (int i = 0; i < n; ++i) {
            vector<double> row;
            int row_start = M.IA[i];
            for (int j = 0; j < n; ++j) {

                /*
                 * Si la columna que me indica JA es la misma sobre la que voy a agregar en la matriz resultado, agreggo el valor de A.
                 * Caso contrario agrego un 0
                 */
                if (M.JA[row_start] == j) {
                    row.push_back(M.A[row_start]);
                    row_start++;
                } else {
                    row.push_back(0);
                }

            }
            result.push_back(row);
        }
        return result;
    }

}

namespace MatrixOperator {

    CSR multiply(InputMatrix &W, diagonalMatrix &D) {
        for (map<int, map<int, double>>::iterator referencedIter = W.graph.begin(); referencedIter != W.graph.end(); ++referencedIter) {
            int referencedPage = referencedIter->first;
            for (map<int, double>::iterator referencingIter = referencedIter->second.begin(); referencingIter != referencedIter->second.end(); ++referencingIter) {
                int referencingPage = referencingIter->first;
                W.graph[referencedPage][referencingPage] = D[referencingPage];
            }
        }
        return convertInputMatrixToCsr(W);
    }

    CSR scale(CSR &M, double s) {
        for (double i = 0; i < M.A.size(); ++i) {
            M.A[i] = M.A[i] * s;
        }
        return M;
    }

    CSR subtractToIdentity(CSR &M) {
        CSR result;
        int n = M.IA.size();
        int row_length = 0;

        for (int i = 0; i < n - 1; ++i) {
            int row_start = M.IA[i];
            int row_end = M.IA[i + 1];
            row_length += row_end - row_start + 1; // sumo 1 por el 1 aportado por la matriz identidad
            while (M.JA[row_start] < i && row_start < row_end) {
                // agrego elementos de la matriz original, previos a la diagonal
                result.A.push_back(-M.A[row_start]);
                result.JA.push_back(M.JA[row_start]);
                row_start++;
            }
            // agrego elementos de la identidad
            result.A.push_back(1);
            result.JA.push_back(i);
            while (i < M.JA[row_start] && row_start < row_end) {
                // agrego elementos de la matriz original, posteriores a la diagonal
                result.A.push_back(-M.A[row_start]);
                result.JA.push_back(M.JA[row_start]);
                row_start++;
            }
            result.IA.push_back(row_length);
        }

        return result;
    }

    void gaussianElimination(vvMatrix &M, vector<double> &augmentedColumn) {
        int n = M.size();

        for(int i = 0; i < n - 1; i++) {
            for(int j = i+1; j <= n - 1; j++) {
                if(M[i][i] != 0) {
                    double x = multiplyBy(M, i, j, i);
                    substractRow(M, augmentedColumn, j, i, x);
                }
            }
        }
    }

    vector<double> createAugmentedColumn(int n) {
        vector<double> vect(n, 1);
        return vect;
    }

    double multiplyBy(vvMatrix &M, int x, int y, int index) {
        return M[y][index] / M[x][index];
    }

    void substractRow(vvMatrix &M, vector<double> &augmentedColumn, int row1, int row2, double multiplier) {
        for(int i = 0; i < M[row1].size(); i++) {
            M[row1][i] -= M[row2][i] * multiplier;
        }
        augmentedColumn[row1] -= augmentedColumn[row2] * multiplier;
    }

    vector<double> calculatePageRank(vvMatrix &M) {
        vector<double> augmentedColumn = createAugmentedColumn(M.size());
        gaussianElimination(M, augmentedColumn);

        int n = M.size();
        vector<double> r(n);

        for (int i = n - 1; i >= 0; i--) {
            r[i] = augmentedColumn[i];
            for (int j = n - 1; j > i; j--) {
                r[i] = r[i] - r[j] * M[i][j];
            }

            if (M[i][i] != 0) {
                r[i] /= M[i][i];
            } else {
                r[i] = 0; // ?
            }
        }

        return r;
    }

}

namespace MatrixPrinter {

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

    void printInputMatrix(InputMatrix &input) {
        printMatrixValues(input.graph);
        printGrades(input.grade);
    }

    extern void printCSR(CSR &input) {
        printf("CSR : \n");

        char msgA[] = "A: ";
        printAVector(input.A, msgA);
        printf("\n");

        char msgJA[] = "JA: ";
        printVector(input.JA, msgJA);
        printf("\n");

        char msgIA[] = "IA: ";
        printVector(input.IA, msgIA);
        printf("\n");
    }

    void printAVector(vector<double>& V, char* msg) {
        cout << msg << "[ ";
        for_each(V.begin(), V.end(), [](double a) {
            cout << a << " ";
        });
        cout << "]" << endl;
    }

    void printVector(vector<int>& V, char* msg) {

        cout << msg << "[ ";
        for_each(V.begin(), V.end(), [](int a) {
            cout << a << " ";
        });
        cout << "]" << endl;
    }

    void printVvMatrix(vvMatrix &matrix) {
        int n = matrix.size();
        for (int i = 0; i < n; i++) {
            cout << "[ ";
            vector<double> row = matrix[i];
            for (int j = 0; j < n; j++) {
                cout << row[j];
                if (j < n - 1) {
                    cout << ", ";
                } else {
                    cout << " ]" << endl;
                }
            }
        }
    }

}