#include "quad_test.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//--------------------------------------------------------------------------------------------------------

int Is_Equal(const double num_1, const double num_2) {

	if (fabs(num_1 - num_2) <= Flt_Epsilon) {
		return 1;
	}
	else {
		return 0;
	}

}


//--------------------------------------------------------------------------------------------------------

int get_test_input(double* a, double* b, double* c, double* x_1, double* x_2, int* num_roots, FILE* fp) {
	char line[50];
	double a_l, b_l, c_l, x_1_l, x_2_l = 0.0/0.0; // defining local copies for middle tests
	int n = 0;

	RET_ASSERT(a == NULL || b == NULL || c == NULL || x_1 == NULL || x_2 == NULL || num_roots == NULL, ERR_NULL_PTR);

	if (fgets(line, sizeof(line), fp) != NULL) {

		if ((n = sscanf(line, " %lf %lf %lf %d %lf %lf", &a_l, &b_l, &c_l, num_roots, &x_1_l, &x_2_l)) > 3) {

			RET_ASSERT(!(isfinite(a_l) && isfinite(b_l) && isfinite(c_l)), ERR_NAN_INF_ARG);
			*a = a_l;
			*b = b_l;
			*c = c_l;

			switch (*num_roots) {
				case NO_SOLUTIONS:
					break;

				case ONE_SOLUTION:
					
					RET_ASSERT(!(isfinite(x_1_l)), ERR_NAN_INF_ARG);
					*x_1 = x_1_l;
					break;

				case TWO_SOLUTIONS:

					RET_ASSERT(!(isfinite(x_1_l) && isfinite(x_2_l)), ERR_NAN_INF_ARG);
					*x_1 = x_1_l;
					*x_2 = x_2_l;
					break;

				default:
					printf("get_test_input: invalid number of roots [%d]\n", *num_roots);
					return ERR_INV_INP;

			}

			return n;
		}
		else{
			printf("get_test_input: wrong number of scanned arguments [%d]\n", n);
			printf(" %lf %lf\n", *a, *b);
			return ERR_SCAN_VAL;
		}

	}
	else {

		return ERR_INV_IN;
	}

}

//--------------------------------------------------------------------------------------------------------

int val_solution(const double tx, const double x) {
	if (Is_Equal(tx, x)) {

		return 1;
	}
	else {
		printf("Test Failed! Expected value: %lf. Obtained value: %lf\n", tx, x);

		return 0;
	}

}

//--------------------------------------------------------------------------------------------------------

int validate_solutions(int num_roots, const double x_1, const double x_2, const double tx_1, const double tx_2) {

	if (num_roots == 1) {

		return val_solution(tx_1, x_1);
	}
	else  {

		return val_solution(tx_1, x_1) && val_solution(tx_2, x_2);
	} 

}