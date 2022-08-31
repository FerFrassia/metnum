#include <string>
#include <list>
#include <sstream>
#include <algorithm>


class Solver {
public:
    Solver() { };
    virtual void read(std::string input, double p) = 0;
    virtual void solve(double p) = 0;
    virtual ~Solver() { };
};

