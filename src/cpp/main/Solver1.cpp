#include "Solver1.h"
#include "Matrix.h"
#include "IO.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <chrono>

using namespace MatrixBuilder;
using namespace MatrixOperator;
using namespace MatrixPrinter;
using namespace VectorOperator;
using namespace IO;

bool useCSR = true;

void Solver1::solve(std::string input, double p, double epsilon, bool measuringTime) {
    std::cout << "Leyendo archivo: " << input << std::endl;
    // printf("Resolviendo con probabilidad: %f\n", p);
    printf("Resolviendo con epsilon: %f\n", epsilon);
    auto start = chrono::steady_clock::now();

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

    vvMatrix fullMatrix;
    //printInputMatrix(w);
    //char msg[] = "D: ";
    //printAVector(d, msg);
    //printf("W*D: \n");
    //printCSR(wd);
    InputMatrix w = buildW(input);
    diagonalMatrix d = buildD(w);
    CSR ipwd;

    if (!useCSR) {
        multiplyInPlace(w, d);
        scale(w, p);
        fullMatrix = subtractToIdentity(w);
    }else {
        CSR wd = multiply(w, d);
        CSR pwd = scale(wd, p);
        //printf("pWD: \n");
        //printCSR(pwd);
        ipwd = subtractToIdentity(pwd);
        //printf("ipwd: \n");
        //printCSR(ipwd);
        fullMatrix = convertCSRTovvMatrix(ipwd);
        //printf("fullMatrix: \n");
        //printVvMatrix(fullMatrix);
    }

    vector<double> pageRank = calculatePageRank(fullMatrix, epsilon);
    normalize(pageRank);
    auto end = chrono::steady_clock::now();
    auto dif = end - start;
    if (measuringTime) {
        writeTimeResult(dif.count(), input + ".timeMeasure.out");
    }
    
    /* CALCULO APROXIMACION */
    vector<double> aprox;
    if (!useCSR) {
        aprox.push_back(approximation(fullMatrix, pageRank, epsilon));
    } else {
        aprox.push_back(approximation(ipwd, pageRank, epsilon));
    }
    writeOutResult(aprox, p, input + ".aprox.out");

    // char resultMsg[] = "result: \n";
    // printAVector(pageRank, resultMsg);
    writeOutResult(pageRank, p, input + ".out");
}
