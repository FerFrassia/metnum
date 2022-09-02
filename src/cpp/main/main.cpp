#include <iostream>
#include "Solver1.h"

/*
 * ./tp1 <archivo> <p>
 */

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Formato de entrada: " << argv[0] << " <archivo> <p>" << std::endl;
        return 1;
    }
    
    std::string input = argv[1];
    double p = std::atof(argv[2]);

    Solver *instance = new Solver1();
    instance->solve(input, p);
    delete instance;

    return 0;
}
