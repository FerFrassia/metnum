#include <string>
#include <list>
#include <sstream>
#include <algorithm>


class Solver {
public:
    Solver() { };
    virtual void solve(std::string input, double p, double eps, bool measuringTime) = 0;
    virtual ~Solver() { };
};

