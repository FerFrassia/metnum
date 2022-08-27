#include "Solver1.h"
#include "Matrix.h"
#include <iostream>

void Solver1::read(std::string input) {
    std::cout << "Leyendo archivo: " << input << std::endl;
//    Matrix *inputGraph = new Matrix(input);
//    inputGraph->print();
    inputMatrix inputGraph = MatrixBuilder::buildW(input);
    MatrixBuilder::printInputMatrix(inputGraph);

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
