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
    vlMatrix fullVlMatrix = convertCSRTovlMatrix(ipwd);
    //printf("fullMatrix: \n");
    //printVvMatrix(fullMatrix);

//<<<<<<< Updated upstream
//    printf("STARTING ORIGINAL PAGE RANK\n");
//    vector<double> pageRank = calculatePageRank(fullMatrix, epsilon);
//    printf("ENDING ORIGINAL PAGE RANK\n");
//    printf("STARTING NEW PAGE RANK\n");
//    vector<double> pageRankVl = calculatePageRankVl(fullVlMatrix, epsilon, input);
//    printf("ENDING NEW PAGE RANK\n");
//    if (pageRank.size() != pageRankVl.size()) {
//        printf("pageRankOrishinal size is different from the pageRankNew \n");
//    }
//    int errorCount = 0;
//    for (int i = 0; i < pageRank.size(); i++) {
//        if (pageRank[i] != pageRankVl[i]) {
//            printf("SOMETHING BROKE OMG OMG OMG!! pageRankOrishinal: %f. pageRankNew: %f\n", pageRank[i], pageRankVl[i]);
//            errorCount++;
//        }
//    }
//    if (errorCount > 0) {
//        printf("Oh boy, you've got %i errors. Better do something about it.\n", errorCount);
//    } else {
//        printf("Congrats sailor! You've made it through!\n");
//    }
//    normalize(pageRank);
//    auto end = chrono::steady_clock::now();
//    auto dif = end - start;
//    if (measuringTime) {
//        writeTimeResult(dif.count(), input + ".timeMeasure.out");
//    }
    
    /* CALCULO APROXIMACION */
//    vector<double> aprox(1, approximation(ipwd, pageRank, epsilon));
//    writeOutResult(aprox, p, input + ".aprox.out");
    for (int i = 2; i < fullMatrix.size(); ++i) {

       vvMatrix currentvvMatrix = MatrixBuilder::getSubvvMatrix(fullMatrix, i);
       vlMatrix currentVLMatrix = MatrixBuilder::getSubVLMatrix(fullVlMatrix, i);


        vector<double> pageRank = calculatePageRank(currentvvMatrix, epsilon);
        vector<double> pageRankVl = calculatePageRankVl(currentVLMatrix, epsilon);

        if (pageRank.size() != pageRankVl.size()) {
            printf("pageRankOrishinal size is different from the pageRankNew \n");
        }
        for (int j = 0; j < pageRank.size(); j++) {
            if (pageRank[j] != pageRankVl[j]) {
                printVvMatrix(currentvvMatrix);
                printVLMatrix(currentVLMatrix);
                printf("SOMETHING BROKE OMG OMG OMG!! pageRankOrishinal: %f. pageRankNew: %f\n", pageRank[j], pageRankVl[j]);
            }
        }

        cout << "dimension " << i << ":...OK" << endl;
    }


//    normalize(pageRank);
//    auto end = chrono::steady_clock::now();
//    auto dif = end - start;
//    if (measuringTime) {
//        writeTimeResult(dif.count(), input + ".timeMeasure.out");
//    }
//
//    /* CALCULO APROXIMACION */
//    vector<double> aprox(1, approximation(ipwd, pageRank, epsilon));
//    writeOutResult(aprox, p, input + ".aprox.out");
//
//    // char resultMsg[] = "result: \n";
//    // printAVector(pageRank, resultMsg);
//    writeOutResult(pageRank, p, input + ".out");
}
