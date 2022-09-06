#include "Solver1.h"
#include "Matrix.h"
#include "IO.h"
#include <iostream>

using namespace MatrixBuilder;
using namespace MatrixOperator;
using namespace MatrixPrinter;
using namespace VectorOperator;
using namespace IO;

void Solver1::solve(std::string input, double p) {
    //std::cout << "Leyendo archivo: " << input << std::endl;
    //printf("Resolviendo con probabilidad: %f\n", p);

    InputMatrix w = buildW(input);
    diagonalMatrix d = buildD(w);
    CSR wd = multiply(w, d);

    //printInputMatrix(w);
    //char msg[] = "D: ";
    //printAVector(d, msg);
    //printf("W*D: \n");
    //printCSR(wd);

    CSR pwd = scale(wd, p);
    //printf("pWD: \n");
    //printCSR(pwd);

    CSR ipwd = subtractToIdentity(pwd);
    //printf("ipwd: \n");
    //printCSR(ipwd);


    vvMatrix fullMatrix = convertCSRTovvMatrix(ipwd);
    //printf("fullMatrix: \n");
    //printVvMatrix(fullMatrix);

    vector<double> pageRank = calculatePageRank(fullMatrix);
    normalize(pageRank);
    //char resultMsg[] = "result: \n";
    //printAVector(pageRank, resultMsg);
    writeOutResult(pageRank, p, input + ".out");
}
