#include "Solver1.h"
#include "Matrix.h"
#include <iostream>
 
void Solver1::read(std::string input) {
    std::cout << "Leyendo archivo: " << input << std::endl;
    Matrix *inputGraph = new Matrix(input);
    delete inputGraph;
}

void Solver1::solve(double p) {
    printf("Resolviendo con probabilidad: %f\n", p);
}
