/*

  Albos library - Personal C library for Antônio H. M. Barreiros

  functions are PascalCase
  variables are PascalCase
  types are PascalCase
  constants are UPPERCASE
  parameters are PascalCase  

*/

#include <stdio.h>

#define INF_FLOAT (1 << (sizeof(double))) + 1
#define INF (1L <<(sizeof(int))) - 1
#define DOUBLE_INF 1.0e8

/* BASIC OPERATIONS */
extern long Abs_i(long x);

extern double Abs_f(double x);

extern int Max_i(int x, int y);

extern int Min_i(int x, int y);

extern float MaxArr_f(float* Values, int Size);

extern int MaxArr_i(int* Values, int Size);

extern double Pow_f(float Base, int Exponent);

extern long Pow_i(int Base, int Exponent);

extern long Sum_i(int* Values, int Size);

extern double Sum_f(float* Values, int Size);

/* ERROR CALCULATIONS */

extern float AbsoluteError(float Value, float ApproximateValue);

extern double RelativeError(float Value, float ApproximateValue);

extern double RelativeErrorEA(float Value, float AbsoluteError);

extern int CompareError(double Error1, double Error2);

/* VECTOR AND MATRICES NORMS */

extern float EuclideanNorm(float* Values, int Size);

extern float EuclideanNormDistance(float* ValuesVectorA, int SizeVectorA,
				   float* ValuesVectorB, int SizeVectorB);

extern float MaximumNorm(float* Values, int Size);

extern float MaximumNormDistance(float* ValuesVectorA, int SizeVectorA,
				 float* ValuesVectorB, int SizeVectorB);

extern float SumNorm(float* Values, int Size);

extern float SumNormDistance(float* ValuesVectorA, int SizeVectorA,
			     float* ValuesVectorB, int SizeVectorB);

extern float FrobeniusNorm(float* Values, int SizeRows, int SizeColumns);

extern float RowMaximumNorm(float** Values, int SizeRows, int SizeColumns);

extern float ColumnMaximumNorm(float* Values[], int SizeRows, int SizeColumns);

extern float* gauss_elimination(float* mat, int sizeRows, int sizeColumns);

extern void gauss_resolution(float* mat, int sizeRows, int sizeColumns);

extern double fint(float x);

extern double simpsons13(float inferior_limit, float superior_limit, unsigned long n);
