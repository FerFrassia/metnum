#include "Solver.h"
#include "Matrix.h"

class Solver1 : public Solver {
    public:
        void solve(std::string input, double p, double eps, bool measuringTime, bool comparePreviousImplementation);
        virtual ~Solver1() { };
    private:
        void compareAgainstPreviousImplementation(CSR &ipwd, double epsilon, vector<double> &pageRankVl);
};
