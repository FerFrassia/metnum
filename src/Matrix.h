#include <list>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Matrix {
    public:
        Matrix(string file);
        void print();
        ~Matrix() {};
    private:
        vector<list<int>> graph;
        void addLink(string);
};
