#include "Solver1.h"
#include "Matrix.h"
#include <iostream>

using namespace MatrixBuilder;
using namespace MatrixOperator;
using namespace MatrixPrinter;

void Solver1::read(std::string input, double p) {
    std::cout << "Leyendo archivo: " << input << std::endl;

    InputMatrix w = buildW(input);
    diagonalMatrix d = buildD(w);
    CSR wd = multiply(w, d);

    printInputMatrix(w);
    char msg[] = "D: ";
    printAVector(d, msg);
    printf("W*D: \n");
    printCSR(wd);

    CSR pwd = scale(wd, p);
    printf("pWD: \n");
    printCSR(pwd);

    CSR ipwd = subtractToIdentity(pwd);
    printf("ipwd: \n");
    printCSR(ipwd);


    vvMatrix fullMatrix = convertCSRTovvMatrix(ipwd);
    printf("fullMatrix: \n");
    printVvMatrix(fullMatrix);

    vector<double> pageRank = calculatePageRank(fullMatrix);
    char resultMsg[] = "result: \n";
    printAVector(pageRank, resultMsg);

//    MatrixBuilder::convertInputMatrixToCsr(inputGraph);

    // eliminacion sin pivoteo
//    for(i=1;i<n;i++)
//    {
//        for(j=i+1;j<n;j++)
//        {
//            float f=mat[j][i]/mat[i][i];
//            for(k=0;k<n+1;k++)
//            {
//                mat[j][k]=mat[j][k]-f*mat[i][k];
//            }
//        }
//    }

//    delete inputGraph;
}

void Solver1::solve(double p) {
    printf("Resolviendo con probabilidad: %f\n", p);
}
