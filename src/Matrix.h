#include <list>
#include <string>
#include <vector>
#include <list>

using namespace std;

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
