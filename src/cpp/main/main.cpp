#include <iostream>
#include "Solver1.h"
#include <math.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Formato de entrada: " << argv[0] << " <archivo> <p>" << std::endl;
        return 1;
    }

    double eps = pow(10, -6);
    if (argc > 2) {
        int coef = std::atof(argv[3]);
        eps = pow(10, -coef);
    }

    std::string input = argv[1];
    double p = std::atof(argv[2]);

    Solver *instance = new Solver1();
    instance->solve(input, p, eps);
    delete instance;

    return 0;
}
