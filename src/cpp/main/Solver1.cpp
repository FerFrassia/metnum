#include "Solver1.h"
#include "Matrix.h"
#include "IO.h"
#include <iostream>
#include <fstream>
#include <iostream>

using namespace MatrixBuilder;
using namespace MatrixOperator;
using namespace MatrixPrinter;
using namespace VectorOperator;
using namespace IO;

void Solver1::solve(std::string input, double p, double epsilon) {
    std::cout << "Leyendo archivo: " << input << std::endl;
    //printf("Resolviendo con probabilidad: %f\n", p);
    printf("Resolviendo con epsilon: %f\n", epsilon);

    // Chequear que el input tiene links
    string line;
    ifstream myfile (input);

    getline(myfile, line); //number of pages
    int numberOfPages = stoi(line);
    getline(myfile, line); //number of links

    if (stoi(line) == 0) {
        // matriz sin links
        double rank = double(1) / double(numberOfPages);
        vector<double> res(numberOfPages, rank);
        writeOutResult(res, p, input + ".out");
        return;
    }

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

    vector<double> pageRank = calculatePageRank(fullMatrix, epsilon);
    normalize(pageRank);
    
    /* CALCULO APROXIMACION */
    vector<double> aprox(1, approximation(ipwd, pageRank, epsilon));
    writeOutResult(aprox, p, input + ".aprox.out");

    // char resultMsg[] = "result: \n";
    // printAVector(pageRank, resultMsg);
    //writeOutResult(pageRank, p, input + ".propio.out");
}
