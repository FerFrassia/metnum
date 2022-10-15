#include "Matrix.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <math.h>

using namespace std;
using namespace MatrixBuilder;
using namespace MatrixOperator;
using namespace MatrixPrinter;

double kahanSum(vector<double> &v)
{
    double sum = 0.0;
 
    double c = 0.0;
 
    for(double n : v) {
        double y = n - c;
        double t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sum;
}

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

            for (int i=0; i<numberOfPages; ++i) {
                result.graph[i] = map<int, double>();
            }

            getline(myfile, line); //number of links
            while(getline(myfile, line)) {
                addLink(result, line); //add each link
            }
            myfile.close();
        } else {
            cout << "unable to open file: " << file << "\n";
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
        CSR result;
        int ia_i = 0;
        for (double i = 0; i < W.grade.size(); ++i) {
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
                if (M.JA[row_start] == j && row_start < M.IA[i+1]) {
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

    vlMatrix convertCSRTovlMatrix(CSR &M) {
        vlMatrix result;
        int n = M.IA.size() - 1;
        for (int i = 0; i < n; ++i) {
            list<tuple<int, double>> row;
            int row_start = M.IA[i];
            for (int j = 0; j < n; ++j) {

                /*
                 * Si la columna que me indica JA es la misma sobre la que voy a agregar en la matriz resultado, agreggo el valor de A.
                 * Caso contrario agrego un 0
                 */
                if (M.JA[row_start] == j && row_start < M.IA[i+1]) {
                    row.push_back(make_tuple(j, M.A[row_start]));
//                    row.push_back(M.A[row_start]);
                    row_start++;
//                } else {
//                    row.push_back(0);
                }

            }
            result.push_back(row);
        }
        return result;
    }

    vvMatrix getSubvvMatrix(const vvMatrix &m, const int size) {
        vvMatrix result;
        for (int i = 0; i < size; ++i) {
            vector<double> rowI;
            for (int j = 0; j < size; ++j) {
                rowI.push_back(m[i][j]);
            }
            result.push_back(rowI);
        }
        return result;
    }

    vlMatrix getSubVLMatrix(vlMatrix &m, const int size) {
        vlMatrix result;
        for (int i = 0; i < size; ++i) {
            row rowI;
            for (row::iterator it = m[i].begin(); it != m[i].end(); ++it) {
                int currentColumn = get<0>(*it);
                double currentValue = get<1>(*it);
                if (currentColumn < size) {
                    rowI.push_back(make_tuple(currentColumn, currentValue));
                } else {
                    break;
                }
            }
            result.push_back(rowI);
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

    vector<double> matrixVectorMultiplication(CSR & M, vector<double> &x) {
        vector<double> res;
        int n = M.IA.size();

        for (int i = 0; i < n - 1; ++i) {
            int row_start = M.IA[i];
            int row_end = M.IA[i + 1];
            vector<double> sum_array;
            while (row_start < row_end) {
                sum_array.push_back(M.A[row_start] * x[M.JA[row_start]]);
                row_start++;
            }
            res.push_back(kahanSum(sum_array));
        }

        return res;
    };

    double findColumnValueForIT(row &r, row::iterator &it, int column) {
        while (it != r.end()) {
            int itColumn = get<0>(*it);
            if (column < itColumn) {
                return 0;
            } else if (column == get<0>(*it)) {
                return get<1>(*it);
            } else {
                ++it;
            }
        }
        return 0;
    }

    void replaceColumnValue(row &target, row::iterator &itOfTarget, int j, double subtrahend, double epsilon, int targetRowIndex) {
        bool foundOriginalValueToSubtract = false;
        for (row::iterator it = target.begin(); it != target.end(); ++it) {
            if (get<0>(*it) > j) {
                itOfTarget = target.insert(it, make_tuple(j, -subtrahend));
                foundOriginalValueToSubtract = true;
                break;
            } else if (get<0>(*it) == j) {
                double originalValue = get<1>(*it);
                double newValue = originalValue - subtrahend;
                if (abs(newValue) > epsilon) {
                    *it = make_tuple(j, newValue);
                } else {
                    if (get<0>(*itOfTarget) == j) {++itOfTarget;}
                    target.erase(it);
                }
                foundOriginalValueToSubtract = true;
                break;
            }
        }
        if (!foundOriginalValueToSubtract) {
            target.push_back(make_tuple(j, -subtrahend));
        }
    }

    void vlSubstractRow(row &pivot, row &target, row::iterator &itOfTarget, vector<double> &augmentedColumn, int n, int targetRowIndex, int pivotRowIndex, double multiplier, double epsilon) {
        row::iterator pivotIterator = pivot.begin();
        for(double i = 0; i < n; i++) {
            double subtrahend = findColumnValueForIT(pivot, pivotIterator, i) * multiplier;
            double toBeSubstracted = findColumnValueForIT(target, itOfTarget, i);

            if (abs(subtrahend) > epsilon) {
                replaceColumnValue(target, itOfTarget, i, subtrahend, epsilon, targetRowIndex);
            }
        }
        if (abs(augmentedColumn[pivotRowIndex] * multiplier) > epsilon) {
            augmentedColumn[targetRowIndex] -= augmentedColumn[pivotRowIndex] * multiplier;
        }
    }

    void vlGaussianElimination(vlMatrix &M, vector<double> &augmentedColumn, double epsilon) {
        int n = M.size();

        vector<row::iterator> rowIterators;
        for (int i = 0; i < n; ++i) {
            rowIterators.push_back(M[i].begin());
        }

        for(int i = 0; i < n - 1; i++) {
            row pivot = M[i];
            double pivotColumnValue = get<1>(*(rowIterators[i]));
            for(int j = i+1; j <= n - 1; j++) {
                //printf("Pivot is row: %d. Target is row: %d\n", i, j);
                if (j == 72 && i == 4) {
                    int stopHere2 = 3;
                }
                double targetColumnValue = findColumnValueForIT(M[j], rowIterators[j], i);
                if (targetColumnValue != 0) {
                    if (abs(pivotColumnValue) > epsilon) {
                        double x = (targetColumnValue / pivotColumnValue);
                        vlSubstractRow(pivot, M[j], rowIterators[j], augmentedColumn, n, j, i, x, epsilon);
                    }
                }
            }
        }
    }

    double findColumnValue(row &target, int j) {
        row::iterator it;
        for (it = target.begin(); it != target.end(); ++it) {
            if (get<0>(*it) == j) {
                return get<1>(*it);
            }
        }
        return 0;
    }

    void printMatrixAfterGE(vlMatrix &M, string input) {
        ofstream myfile;
        myfile.open(input + "_errors");
        int size = M.size();
        for (int i = 0; i < size; i++) {
            row r_i = M[i];
            row::iterator it;
            for (it = r_i.begin(); it != r_i.end(); ++it) {
               int currentColumn = get<0>(*it);
               if (currentColumn < i) {
                   cout << "### ERROR ### Iterating row[" << i << "] found that there is a value in column[" << currentColumn << "] value: " << get<1>(*it) << endl;
                   myfile << "### ERROR ### Iterating row[" << i << "] found that there is a value in column[" << currentColumn << "] value: " << get<1>(*it) << "\n";
               }
//               for (int j = 0; j < currentColumn; j++) {
//                   myfile << "0 ";
//               }
//                myfile << get<1>(*it) << " ";
            }
//            myfile << "\n";
        }
        myfile.close();
        cout << "Finished writing file" << endl;
    }

    vector<double> calculatePageRankVl(vlMatrix &M, double epsilon) {
        vector<double> augmentedColumn = createAugmentedColumn(M.size());
        vlGaussianElimination(M, augmentedColumn, epsilon);


        int n = M.size();
        vector<double> r(n);

        for (int i = n - 1; i >= 0; i--) {
            r[i] = augmentedColumn[i];
            for (int j = n - 1; j > i; j--) {
                row r_i = M[i];
                double subtrahend = r[j] * findColumnValue(r_i, j);
                if (abs(subtrahend) > epsilon) {
                    r[i] -= subtrahend;
                }
            }

            row r_i = M[i];
            double r_i_value = findColumnValue(r_i, i);
            if (r_i_value != 0) {
                if (abs(r[i]) > epsilon) {
                    r[i] /= r_i_value;
                } else {
                    r[i] = 0;
                }
            } else {
                r[i] = 0; // ?
            }
        }

        return r;
    }

    vector<double> createAugmentedColumn(int n) {
        vector<double> vect(n, 1);
        return vect;
    }

    void gaussianElimination(vvMatrix &M, vector<double> &augmentedColumn, double epsilon) {
        int n = M.size();

        for(int i = 0; i < n - 1; i++) {
            for(int j = i+1; j <= n - 1; j++) {
                if(abs(M[i][i]) > epsilon) {
                    double x = multiplyBy(M, i, j, i);
                    substractRow(M, augmentedColumn, j, i, x, epsilon);
                } else {
                    M[i][i] = double(0);
                }
                if (16 < n && 22 < n) {
                    if (M[16][22] != 0) {

                    }
                }
            }
        }
    }

    double multiplyBy(vvMatrix &M, int x, int y, int index) {
        return M[y][index] / M[x][index];
    }

    void substractRow(vvMatrix &M, vector<double> &augmentedColumn, int row1, int row2, double multiplier, double epsilon) {
        for(double i = 0; i < M[row1].size(); i++) {
            double subtrahend = M[row2][i] * multiplier;
            if (abs(subtrahend) > epsilon) {
                M[row1][i] -= subtrahend;
            }
        }
        if (abs(augmentedColumn[row2] * multiplier) > epsilon) {
            augmentedColumn[row1] -= augmentedColumn[row2] * multiplier;
        }
    }

    vector<double> calculatePageRank(vvMatrix &M, double epsilon) {
        vector<double> augmentedColumn = createAugmentedColumn(M.size());
        gaussianElimination(M, augmentedColumn, epsilon);

        int n = M.size();
        vector<double> r(n);

        for (int i = n - 1; i >= 0; i--) {
            r[i] = augmentedColumn[i];
            for (int j = n - 1; j > i; j--) {
                double subtrahend = r[j] * M[i][j];
                if (abs(subtrahend) > epsilon) {
                    r[i] -= subtrahend;
                }
            }

            if (M[i][i] != 0) {
                if (abs(r[i]) > epsilon) {
                    r[i] /= M[i][i];
                } else {
                    r[i] = 0;
                }
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
                page += +"[(" + to_string(iter->first) + ", " + to_string(iter->second) + ")] -> ";
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

    void printAVector(vector<double> &V, char *msg) {
        cout << msg << "[ ";
        for_each(V.begin(), V.end(), [](double a) {
            cout << a << " ";
        });
        cout << "]" << endl;
    }

    void printVector(vector<int> &V, char *msg) {

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

    void printVLMatrix(vlMatrix &matrix) {
        for (double i = 0; i < matrix.size(); ++i) {
            cout << "[" << i << "]: ";
            for (row::iterator it = matrix[i].begin(); it != matrix[i].end(); ++it) {
                cout << "(" << get<0>(*it) << "," << get<1>(*it) << ") ";
            }
            cout << endl;
        }
    }

}

namespace VectorOperator {
    void normalize(vector<double> &v) {
        double sum = kahanSum(v);
        for (double i = 0; i < v.size(); ++i) {
            v[i] = v[i] / sum;
        }
    }

    double approximation(CSR &M, vector<double> &x, double epsilon) {
        vector<double> res = matrixVectorMultiplication(M, x);
        for (double i = 0; i < res.size(); ++i) {
            if (abs(x[i]) > epsilon) {
                res[i] -= x[i];
            }
        }
        return norm2(res);
    }

    double norm2(vector<double> &v) {
        vector<double> sum_array;
        for (double i = 0; i < v.size(); ++i) {
            sum_array.push_back(pow(v[i], 2));
        }
        double res = kahanSum(sum_array);
        return sqrt(res);
    }
}