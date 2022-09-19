#ifndef QUAD_
#define QUAD_


const double Flt_Epsilon = 1.19209290E-07F; // decimal constant 

#define RET_ASSERT(expr, errnum) \
	if (expr) \
		return errnum

enum error_codes{
	NO_SOLUTIONS = 0,  		 // Return code for no solutions case
	ONE_SOLUTION = 1,  		 // Return code for one solution case
	TWO_SOLUTIONS = 2, 		 // Return code for two solutions case
	ERR_NULL_PTR = -1, 		 // Error code -1 - argument pointer is NULL
	ERR_NAN_INF_ARG = -2,  // Error code -2 - argument variable is not a number or infinite
	ERR_INF_ARG = -3,	 		 // Error code -3 - argument variable is infinite
	ERR_INV_INP = -4,	 		 // Error code -4 - invalid input
	ERR_READ_LINE = -5 		 // Error code -5 - unable to read input line
};

// checks if double variable is zero
int Is_Zero(const double num);

// prints discription of errnum
void print_errnum(const int errnum);

// gets input for quadratic equation
int get_input(double* a, double* b, double* c);

// solves linear equation
int solve_linear(const double b, const double c, double* x);

// solves quadratic equation
int solve_quad(const double a, const double b, const double c, double* x_1, double* x_2);

// solves input equation
int solve_eq(const double a, const double b, const double c, double* x_1, double* x_2);

// prints equation solutions
void print_solutions(const int solve_quad_return_code, const double x_1, const double x_2);

#endif