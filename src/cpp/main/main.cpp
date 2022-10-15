#include <iostream>
#include "Solver1.h"
#include <math.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Formato de entrada: " << argv[0] << " <archivo> <p>" << std::endl;
        return 1;
    }

    bool measuringTime = false;
    double eps = pow(10, -6);
    bool comparePreviousImplementation = false;
    for (int i = 0; i < argc; i++) {
        std::string currentArg = argv[i];
        if (currentArg == "-t") {
            measuringTime = true;
        }
        if (currentArg == "-e") {
            int coef = std::atof(argv[i+1]);
            eps = pow(10, -coef);
        }
        if (currentArg == "-cmp") {
            comparePreviousImplementation = true;
        }
    }

    std::string input = argv[1];
    double p = std::atof(argv[2]);

    Solver *instance = new Solver1();
    instance->solve(input, p, eps, measuringTime, comparePreviousImplementation);
    delete instance;

    return 0;
}
