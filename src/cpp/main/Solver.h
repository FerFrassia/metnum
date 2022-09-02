#include <string>
#include <list>
#include <sstream>
#include <algorithm>


class Solver {
public:
    Solver() { };
    virtual void solve(std::string input, double p) = 0;
    virtual ~Solver() { };
};

