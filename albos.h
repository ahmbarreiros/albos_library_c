/*

Albos library - Personal C library for Antônio H. M. Barreiros

functions are snake_case
variables are camelCase
types are PascalCase
constants are UPPERCASE
macros are ALL_CAPS
parameters are camelCase  

*/

#include <stdio.h>


/* BASIC OPERATIONS */
extern long abs_i(long x);

extern double abs_f(double x);

extern double max_arr_f(double* values, int size);

extern long max_arr_i(long* values, int size);

extern double pow_f(double base, int exponent);

extern long pow_i(long base, int exponent);

extern long sum_i(long* values, int size);

extern double sum_f(double* values, int size);

/* ERROR CALCULATIONS */

extern double absolute_error(double value, double approximateValue);

extern double relative_error(double value, double approximateValue);

extern double relative_error_ea(double value, double absoluteError);

extern int compare_error(double error1, double error2);

/* VECTOR AND MATRICES NORMS */

extern double euclidean_norm_f(double* values, int size);

extern long euclidean_norm_i(long* values, int size);

extern double maximum_norm_f(double* values, int size);

extern long maximum_norm_i(long* values, int size);

extern double sum_norm_f(double* values, int size);

extern long sum_norm_i(long* values, int size);
