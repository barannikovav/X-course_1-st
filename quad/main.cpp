#include "quad.h"
#include "math.h"

int main(void){
	double a, b, c, x_1, x_2 = NAN;
	int solve_quad_return_code, ret_val = 0;

	ret_val = get_input(&a, &b, &c);
	if (ret_val != 3) {
		print_errnum(ret_val);
	}
	solve_quad_return_code = solve_eq(a, b, c, &x_1, &x_2);
	print_solutions(solve_quad_return_code, x_1, x_2);
	
	return 0;
}