#include <list>
#include <string>
#include <vector>
#include <list>

using namespace std;

struct CSR {
    vector<double> A;
    vector<int> JA;
    vector<int> IA {0};
};

typedef vector<list<int>> inputMatrix;
typedef vector<double> diagonalMatrix;

namespace MatrixBuilder {

    list<string> split(string originalString, char delim);

    void addLink(inputMatrix &W, string originalString);

    inputMatrix buildW(string file);

    void printInputMatrix(inputMatrix &input);

    CSR buildD(inputMatrix &W);

    CSR convertInputMatrixToCsr(inputMatrix W);

    void printAVector(vector<double>& V, char* msg);
    void printVector(vector<int>& V, char* msg);

    CSR createIdentity(int size);

}

namespace MatrixOperator {

    void multiply(CSR &W, CSR &D);

    void scale(CSR &M, int s);

    void add(CSR &A, CSR &B);
}

class Matrix {
    public:
        Matrix(string file);
        Matrix();
        void print(Matrix* matrix);
        ~Matrix() {};
    private:
        vector<list<int>> graph;
        void addLink(Matrix* matrix, string);
        int size();
        list<int> get(Matrix* matrix, int column);
        Matrix* generateW(string file);
        vector<double> generateD(Matrix w);
        vector<vector<double>> multiply(Matrix w, vector<double> d);
};
