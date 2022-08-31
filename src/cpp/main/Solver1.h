#include "Solver.h"

class Solver1 : public Solver {
    public:
        void read(std::string input, double p);
        void solve(double p);
        virtual ~Solver1() { };
};
