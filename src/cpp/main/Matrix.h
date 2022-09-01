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

    CSR subtractToIdentity(CSR &M);

    void gaussianElimination(vvMatrix &M, vector<double> &augmentedColumn);

    vector<double> createAugmentedColumn(int n);

    double multiplyBy(vvMatrix &M, int x, int y, int index);

    void substractRow(vvMatrix &M, vector<double> &augmentedColumn, int row1, int row2, double multiplier);

    vector<double> calculatePageRank(vvMatrix &M);

}

namespace MatrixPrinter {

    void printInputMatrix(InputMatrix &input);

    void printCSR(CSR &input);

    void printAVector(vector<double>& V, char* msg);

    void printVector(vector<int>& V, char* msg);

    void printVvMatrix(vvMatrix &matrix);

}

namespace VectorOperator {
    void normalize(vector<double> &v);
}
