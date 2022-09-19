#ifndef QUAD_TEST_
#define QUAD_TEST_
#include "quad.h"
#include <stdio.h>

//const int BUFSIZ = 4096;
const double NaN = 0.0/0.0;

enum quad_test_error_codes{
	ERR_ARG_NUM = -6,   // Error code -1 - wrong number of function arguments
	ERR_OPEN_FILE = -7, // Error code -2 - can't open file
	ERR_INV_IN = -8,		// Error code -4 - invalid input
	ERR_SCAN_VAL = -9   // Error code -5 - error scanning values
};

int Is_Equal(const double num_1, const double num_2);

int get_test_input(double* a, double* b, double* c, double* x_1, double* x_2, int* num_roots, FILE* fp);

int val_solution(const double tx, const double x);

int validate_solutions(int num_roots, const double x_1, const double x_2, const double tx_1, const double tx_2);

#endif