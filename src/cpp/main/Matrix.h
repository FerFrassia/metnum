#include <list>
#include <string>
#include <vector>
#include <list>
#include <map>

using namespace std;

typedef map<int, map<int, double>> coordinateList;
typedef vector<double> diagonalMatrix;

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

    void printInputMatrix(InputMatrix &input);

    CSR buildD(InputMatrix &W);

    CSR convertInputMatrixToCsr(InputMatrix W);

    void printAVector(vector<double>& V, char* msg);
    void printVector(vector<int>& V, char* msg);

    CSR createIdentity(int size);

}

namespace MatrixOperator {

    void multiply(CSR &W, CSR &D);

    void scale(CSR &M, int s);

    void add(CSR &A, CSR &B);
}
