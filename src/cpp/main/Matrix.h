#include <list>
#include <string>
#include <vector>
#include <list>
#include <map>

using namespace std;

typedef map<int, map<int, double>> coordinateList;
typedef vector<double> diagonalMatrix;
typedef vector<vector<double>> vvMatrix;

struct CSR {
    vector<double> A;
    vector<int> JA;
    vector<int> IA {0};
};

struct InputMatrix {
    coordinateList graph;
    vector<int> grade;
};

namespace MatrixBuilder {

    list<string> split(string originalString, char delim);

    void addLink(InputMatrix &W, string originalString);

    InputMatrix buildW(string file);

    diagonalMatrix buildD(InputMatrix &W);

    CSR convertInputMatrixToCsr(InputMatrix &W);

    vvMatrix convertCSRTovvMatrix(CSR &M);

}

namespace MatrixOperator {

    CSR multiply(InputMatrix &W, diagonalMatrix &D);

    CSR scale(CSR &WD, double s);

    CSR add(CSR &A, CSR &B);

    CSR subtractToIdentity(CSR &M);

    vvMatrix gaussianElimination(vvMatrix &M);

}

namespace MatrixPrinter {

    void printInputMatrix(InputMatrix &input);

    void printCSR(CSR &input);

    void printAVector(vector<double>& V, char* msg);

    void printVector(vector<int>& V, char* msg);

}
