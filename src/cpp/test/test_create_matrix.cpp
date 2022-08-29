#include "test_create_matrix.h"


void RunAllTestsForCreateMatrix(){
    TestFileWithNoLinksReturnsEmptyMatrix();
    TestFileWithNoLinksReturnsEmptyGrades();
    TestUnorderedInputIsOrderedByMatrix();
//    TestCatedraAleatorioMatrixParsedCorrectly();
}

void TestFileWithNoLinksReturnsEmptyMatrix(){
    TEST

    given("An empty Connectivity Matrix")
    InputMatrix inputGraph = MatrixBuilder::buildW("../../../enunciado/tests/test_sin_links.txt");

    then("Returned InputMatrix must be empty")

    assert(inputGraph.graph.empty());

    END_TEST
}

void TestFileWithNoLinksReturnsEmptyGrades(){
    TEST

    given("An empty Connectivity Matrix")
    InputMatrix inputGraph = MatrixBuilder::buildW("../../../enunciado/tests/test_sin_links.txt");

    then("Returned grades must be all 0")

    vector<int> grades = inputGraph.grade;
    assert(grades.size() == 5);
    for (unsigned int i = 0; i < 5; i++) {
        assert(grades[i] == 0);
    }

    END_TEST
}

void TestUnorderedInputIsOrderedByMatrix(){
    TEST

    given("A non empty Connectivity Matrix")
    InputMatrix inputGraph = MatrixBuilder::buildW("../../../enunciado/tests/test_aleatorio_desordenado.txt");

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

void TestCatedraAleatorioMatrixParsedCorrectly(){
    TEST

//    given("A list of cartesian points and a special point")
//    Point point_of_interest = Point(2, 5, 1);
//    Point closest = Point(2, 4, 3);
//    Cluster cluster = {Point(7, 1, 3), Point(4, 2, 3), closest, Point(1, 1, 1)};
//
//    // when("Calling TransformPointsFromCartesianToPolar")
//    Point result = Point(-1, -1, -1);
//    // result = sweep::PopClosestVertexTo(cluster, point_of_interest);
//
//    then("The points should have their polar attributes loaded")
//    assert(closest == result);

    END_TEST
}

//void TestFindSweepStartingAngle1(){
//    TEST
//
//    given("A list of angles")
//    vector<Point> angles = {Point(0, 0, 0, 0, 0.2), Point(1, 0, 0, 0, 0.6), Point(2, 0, 0, 0, 1.7),
//                            Point(3, 0, 0, 0, 1.9)};
//
//    // when("Calling FindMaxAngleSeparation")
//    float starting_angle;
//    // starting_angle = sweep::FindSweepStartingAngle(angles);
//
//    then("The points should have their polar attributes loaded")
//    float expected = 1.15;
//    assert(fequals(expected, starting_angle));
//
//    END_TEST
//}

//void TestFindSweepStartingAngle2(){
//    TEST
//
//    given("A list of angles")
//    vector<Point> angles = {Point(0, 0, 0, 0, 0.2), Point(1, 0, 0, 0, 0.6), Point(2, 0, 0, 0, 1.0),
//                            Point(3, 0, 0, 0, 1.4)};
//
//    // when("Calling FindMaxAngleSeparation")
//    float starting_angle;
//    // starting_angle = sweep::FindSweepStartingAngle(angles);
//
//    then("The points should have their polar attributes loaded")
//    float expected = 1.8;
//    assert(fequals(expected, starting_angle));
//
//    END_TEST
//}