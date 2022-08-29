#ifndef METNUM_TEST_CREATE_MATRIX_H
#define METNUM_TEST_CREATE_MATRIX_H

#include <utility>
#include "test_utils.h"
#include "../main/Matrix.h"

void RunAllTestsForCreateMatrix();
void TestFileWithNoLinksReturnsEmptyMatrix();
void TestFileWithNoLinksReturnsEmptyGrades();
void TestUnorderedInputIsOrderedByMatrix();
void TestCatedraAleatorioMatrixParsedCorrectly();

#endif //METNUM_TEST_CREATE_MATRIX_H