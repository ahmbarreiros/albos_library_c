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

extern int max_i(int x, int y);

extern int min_i(int x, int y);

extern float max_arr_f(float* values, int size);

extern int max_arr_i(int* values, int size);

extern double pow_f(float base, int exponent);

extern long pow_i(int base, int exponent);

extern long sum_i(int* values, int size);

extern double sum_f(float* values, int size);

/* ERROR CALCULATIONS */

extern float absolute_error(float value, float approximateValue);

extern double relative_error(float value, float approximateValue);

extern double relative_error_ea(float value, float absoluteError);

extern int compare_error(double error1, double error2);

/* VECTOR AND MATRICES NORMS */

extern float euclidean_norm_f(float* values, int size);

extern long euclidean_norm_i(int* values, int size);


extern float euclidean_norm_distance_f(float* valuesVectorA, int sizeVectorA,
				       float* valuesVectorB, int sizeVectorB);

// TODO: testar
extern long euclidean_norm_distance_i(int* valuesVectorA, int sizeVectorA,
				      int* valuesVectorB, int sizeVectorB);

extern float maximum_norm_f(float* values, int size);


extern int maximum_norm_i(int* values, int size);


extern float maximum_norm_distance_f(float* valuesVectorA, int sizeVectorA,
				     float* valuesVectorB, int sizeVectorB);
// TODO: testar
extern int maximum_norm_distance_i(int* valuesVectorA, int sizeVectorA,
				   int* valuesVectorB, int sizeVectorB);

extern float sum_norm_f(float* values, int size);

extern long sum_norm_i(int* values, int size);


extern float sum_norm_distance_f(float* valuesVectorA, int sizeVectorA,
				 float* valuesVectorB, int sizeVectorB);

// TODO: testar
extern int sum_norm_distance_i(int* valuesVectorA, int sizeVectorA,
			       int* valuesVectorB, int sizeVectorB);

extern float frobenius_norm_f(float* values, int sizeRows, int sizeColumns);

extern long frobenius_norm_i(int* values, int sizeRows, int sizeColumns);

extern float row_maximum_norm_f(float** values, int sizeRows, int sizeColumns);

extern long row_maximum_norm_i(int** values, int sizeRows, int sizeColumns);

extern float column_maximum_norm_f(float* values[], int sizeRows, int sizeColumns);

extern long column_maximum_norm_i(int** values, int sizeRows, int sizeColumns);

extern float* gauss(float* mat, int size);

extern void gauss_resolution(float* mat, int size);
