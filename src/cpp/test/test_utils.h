#ifndef METNUM_TEST_UTILS_H
#define METNUM_TEST_UTILS_H


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define TEST printf("%s... ", __func__);
#define END_TEST printf("PASSED\n");
#define IGNORE if(0)
#define given(x)
#define when(x)
#define then(x)
#define And(x)
#define Case(x)
#define cleanup

#define EPSILON 0.00001


bool fequals(float a, float b);

#endif //METNUM_TEST_UTILS_H