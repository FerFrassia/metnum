#include "Solver.h"

class Solver1 : public Solver {
    public:
        void solve(std::string input, double p, double eps, bool measuringTime);
        virtual ~Solver1() { };
};
