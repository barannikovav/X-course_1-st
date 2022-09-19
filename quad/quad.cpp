#include "quad.h"
 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

//--------------------------------------------------------------------------------------------------------

int Is_Zero(const double num) {

	if (fabs(num) <= Flt_Epsilon) {
		return 1;
	}
	else {
		return 0;
	}

}

//--------------------------------------------------------------------------------------------------------

void print_errnum(const int errnum) {
	switch (errnum) {
		case ERR_NULL_PTR:
			puts("Error code -1 - argument pointer is NULL");
			break;

		case ERR_NAN_INF_ARG:
			puts("Error code -2 - argument variable is not a number or infinity");
			break;

		case ERR_INF_ARG:
			puts("Error code -3 - argument variable is infinity");
			break;
		case ERR_INV_INP:
			puts("Error code -4 - invalid input");
			break;
		case ERR_READ_LINE:
			puts("Error code -5 - unable to read input line");
			break;
		default:
			printf("Unknown error code %d\n", errnum);
			break;
	}

	return;
}

//--------------------------------------------------------------------------------------------------------

int get_input(double* a, double* b, double* c) {
	char line[20];

	RET_ASSERT(a == NULL || b == NULL || c == NULL, ERR_NULL_PTR);

	while (1) {
		RET_ASSERT(fgets(line, sizeof(line), stdin) == NULL, ERR_READ_LINE);

		if (sscanf(line, " %lf %lf %lf", a, b, c) == 3) {
			return 3;
		} 
		else {
			puts("Invalid input! Please, use defined format of program input with numeric values: [a] [b] [c]");
		}
	}
}

//--------------------------------------------------------------------------------------------------------

int solve_linear(const double b, const double c, double* x) {
	if (Is_Zero(b)) {
		if (Is_Zero(c)) {
			return INT_MAX;
		} 
		else {
			return NO_SOLUTIONS;
		}

	}
	else {
		if (Is_Zero(c)) {
			*x = 0;
		} 
		else {
			*x = -c / b;
		}

		return ONE_SOLUTION;
	}
}

//--------------------------------------------------------------------------------------------------------

int solve_quad(const double a, const double b, const double c, double* x_1, double* x_2) {

	if (Is_Zero(b)) {
		if (Is_Zero(c)) {
			*x_1 = 0;
			return ONE_SOLUTION;
		}
		else {
			if (-c / a > 0) {
				*x_1 = sqrt(-c / a);
				*x_2 = -sqrt(-c / a);
				return TWO_SOLUTIONS;
			}
			else {
				return NO_SOLUTIONS;
			}
		}
	}
	else {
		if (Is_Zero(c)) {
			*x_1 = 0;
			*x_2 = -b / a;
			return TWO_SOLUTIONS;
		}
		else {
			double Desc = b * b - 4 * a * c;
			if (Desc > 0) {
				*x_1 = (-b + sqrt(Desc))/(2 * a);
				*x_2 = (-b - sqrt(Desc))/(2 * a);
				return TWO_SOLUTIONS;
			}
			else if (Is_Zero(Desc)) {
				*x_1 = -b / (2 * a);
				return ONE_SOLUTION;
			}
			else {
				return NO_SOLUTIONS;
			}
		}
	}

}

//--------------------------------------------------------------------------------------------------------

int solve_eq(const double a, const double b, const double c, double* x_1, double* x_2) {

	//RET_ASSERT(x_1 == NULL || x_2 == NULL, ERR_NULL_PTR);
	//RET_ASSERT(!(isfinite(a) && isfinite(b) && isfinite(c)), ERR_NAN_INF_ARG);

	if (Is_Zero(a)) {
		return solve_linear(b, c, x_1);
	} 
	else {
		return solve_quad(a, b, c, x_1, x_2);
	}
}

//--------------------------------------------------------------------------------------------------------

void print_solutions(const int solve_quad_return_code, const double x_1, const double x_2) {
	switch (solve_quad_return_code) {
		case NO_SOLUTIONS:
			puts("No solutions!");
			break;

		case ONE_SOLUTION:
			printf("x = %.2lf\n", x_1);
			break;

		case TWO_SOLUTIONS:
			printf("x_1 = %.2lf; x_2 = %.2lf\n", x_1, x_2);
			break;

		case INT_MAX:
			puts("Infinite number of solutions!");
			break;
			
		default:
			print_errnum(solve_quad_return_code);
			break;
	}

	return;
}

//--------------------------------------------------------------------------------------------------------

