#include "test_create_matrix.h"
#include <iostream>
#include <filesystem>

using namespace std;


void RunAllTestsForCreateMatrix(){
    filesystem::path currentPath = filesystem::current_path();
    string resourcesDirectory = currentPath.generic_string() + "/../enunciado/tests/";

    TestFileWithNoLinksReturnsEmptyMatrix(resourcesDirectory);
    TestFileWithNoLinksReturnsEmptyGrades(resourcesDirectory);
    TestUnorderedInputIsOrderedByMatrix(resourcesDirectory);
}

void TestFileWithNoLinksReturnsEmptyMatrix(string resourcesDirectory){
    TEST

    given("An empty Connectivity Matrix")
    InputMatrix inputGraph = MatrixBuilder::buildW(resourcesDirectory + "test_sin_links.txt");

    then("Returned InputMatrix must be empty")

    assert(inputGraph.graph.empty());

    END_TEST
}

void TestFileWithNoLinksReturnsEmptyGrades(string resourcesDirectory){
    TEST

    given("An empty Connectivity Matrix")
    InputMatrix inputGraph = MatrixBuilder::buildW(resourcesDirectory+ "test_sin_links.txt");

    then("Returned grades must be all 0")

    vector<int> grades = inputGraph.grade;
    assert(grades.size() == 5);
    for (unsigned int i = 0; i < 5; i++) {
        assert(grades[i] == 0);
    }

    END_TEST
}

void TestUnorderedInputIsOrderedByMatrix(string resourcesDirectory){
    TEST

    given("A non empty Connectivity Matrix")
    InputMatrix inputGraph = MatrixBuilder::buildW(resourcesDirectory + "test_aleatorio_desordenado.txt");

    then("Returned InputMatrix must be not empty")

    coordinateList matrixGraph = inputGraph.graph;
    assert(matrixGraph.size() == 4); // since row 2 has no contents, it's not added

    // fila 1
    assert(matrixGraph[0][0] == 0);
    assert(matrixGraph[0][1] == 1);
    assert(matrixGraph[0][2] == 1);
    assert(matrixGraph[0][3] == 1);

    // fila 2
    assert(matrixGraph[1].empty());

    // fila 3
    assert(matrixGraph[2][0] == 1);
    assert(matrixGraph[2][1] == 0);
    assert(matrixGraph[2][2] == 0);
    assert(matrixGraph[2][3] == 1);

    // fila 4
    assert(matrixGraph[3][0] == 1);
    assert(matrixGraph[3][1] == 1);
    assert(matrixGraph[3][2] == 1);

    // fila 4
    assert(matrixGraph[4][0] == 1);
    assert(matrixGraph[4][1] == 1);
    assert(matrixGraph[4][2] == 1);
    assert(matrixGraph[4][3] == 1);

    vector<int> grades = inputGraph.grade;
    assert(grades[0] == 3);
    assert(grades[1] == 3);
    assert(grades[2] == 3);
    assert(grades[3] == 3);
    assert(grades[4] == 0);

    END_TEST
}