//TODO * split solve eq to linear and quad
// 		 * create input func
//		 * create macros
 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#define FLT_EPSILON 1.19209290E-07F // decimal constant 

//--------------------------------------------------------------------------------------------------------

enum {
	NO_SOLUTIONS = 0,  // Return code for no solutions case
	ONE_SOLUTION = 1,  // Return code for one solution case
	TWO_SOLUTIONS = 2, // Return code for two solutions case
	ERR_NULL_PTR = -1, // Error code -1 - argument pointer is NULL
	ERR_NAN_ARG = -2,  // Error code -2 - argument variable is not a number
	ERR_INF_ARG = -3,	 // Error code -3 - argument variable is infinite
	ERR_INV_INP = -4,	 // Error code -4 - invalid input
	ERR_READ_LINE = -5 // Error code -5 - unable to read input line
};

void print_errnum(const int errnum) {
	switch (errnum) {
		case -1:
			puts("Error code -1 - argument pointer is NULL");
			break;

		case -2:
			puts("Error code -2 - argument variable is not a number");
			break;

		case -3:
			puts("Error code -3 - argument variable is infinity");
			break;
		case -4:
			puts("Error code -4 - invalid input");
			break;
		case -5:
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
	if (a == NULL || b == NULL || c == NULL) {
		return ERR_NULL_PTR;
	}

	while (1) {
		if (fgets(line, sizeof(line), stdin) == NULL) {
			return ERR_READ_LINE;
		}
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
	if (fabs(b) <= FLT_EPSILON) {
		if (fabs(c) <= FLT_EPSILON) {
			return INT_MAX;
		} 
		else {
			return NO_SOLUTIONS;
		}

	}
	else {
		if (fabs(c) <= FLT_EPSILON) {
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

	if (fabs(b) <= FLT_EPSILON) {
		if (fabs(c) <= FLT_EPSILON) {
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
		if (fabs(c) <= FLT_EPSILON) {
			*x_1 = 0;
			*x_2 = -b / a;
			return TWO_SOLUTIONS;
		}
		else {
			double Determinant = b * b - 4 * a * c;
			if (Determinant > 0) {
				*x_1 = (-b + sqrt(Determinant))/(2 * a);
				*x_2 = (-b - sqrt(Determinant))/(2 * a);
				return TWO_SOLUTIONS;
			}
			else if (fabs(Determinant) <= FLT_EPSILON) {
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

	if (x_1 == NULL || x_2 == NULL) {
		return ERR_NULL_PTR;
	}
	else if (isnan(a) || isnan(b) || isnan(c)) {
		return ERR_NAN_ARG;
	}
	else if (isinf(a) || isinf(b) || isinf(c)) {
		return ERR_INF_ARG;
	}

	if (fabs(a) <= FLT_EPSILON) {
		return solve_linear(b, c, x_1);
	} 
	else {
		return solve_quad(a, b, c, x_1, x_2);
	}
}

//--------------------------------------------------------------------------------------------------------

void print_solutions(const int solve_quad_return_code, const double x_1, const double x_2) {
	switch (solve_quad_return_code) {
		case 0:
			puts("No solutions!");
			break;

		case 1:
			printf("x = %.2lf\n", x_1);
			break;

		case 2:
			printf("x_1 = %.2lf; x_2 = %.2lf\n", x_1, x_2);
			break;

		case INT_MAX:
			puts("Infinite number of solutions!");
			break;
			
		default:
			print_errnum(solve_quad_return_code);
	}

	return;
}

//--------------------------------------------------------------------------------------------------------

int main(void){
	double a, b, c, x_1, x_2;
	int solve_quad_return_code, ret_val;

	ret_val = get_input(&a, &b, &c);
	if (ret_val != 3) {
		print_errnum(ret_val);
	}
	solve_quad_return_code = solve_quad(a, b, c, &x_1, &x_2);
	print_solutions(solve_quad_return_code, x_1, x_2);
	
	return 0;
}