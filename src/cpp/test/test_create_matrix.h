#ifndef METNUM_TEST_CREATE_MATRIX_H
#define METNUM_TEST_CREATE_MATRIX_H

#include <utility>
#include "test_utils.h"
#include "../main/Matrix.h"

void RunAllTestsForCreateMatrix();
void TestFileWithNoLinksReturnsEmptyMatrix(string resourcesDirectory);
void TestFileWithNoLinksReturnsEmptyGrades(string resourcesDirectory);
void TestUnorderedInputIsOrderedByMatrix(string resourcesDirectory);

#endif //METNUM_TEST_CREATE_MATRIX_H