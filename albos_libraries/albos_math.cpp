#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "albos.h"

#define INF (1L <<(sizeof(int))) - 1
#define DOUBLE_INF 1.0e8

 // THIS IS A TEMPLATE FOR DOCUMENTING FUNCTIONS
/**
 * @brief Brief description of the function.
 *
 * Detailed description of the function's purpose, behavior, and usage.
 * Include information about parameters, return values, and any exceptions.
 *
 * @param  (type) param1: Description of parameter 1.
 * @param  (type) param2: Description of parameter 2.
 * @return (type) Description of the return value (if applicable).
 *
 * @note Any additional notes or special considerations.
 * @warning Any warnings or potential issues.
 * @see Related functions or references.
 */


/** BASIC OPERATIONS */

/**
 * @brief Calculates the maximum value of a float array.
 *
 * Given an array of floating point values, calculates the biggest value within it.
 *
 * @param  (float*) Arr : Array of floating point values.
 * @param  (int)    Size: Size of the array.
 * @return (float)  The biggest value of the array "arr".
 *
 * @warning This function is for floating point values only; for integers, check reference.
 * @see MaxArr_i() for integer values.
 */
float MaxArr_f(float* Arr, int Size) { 
  float max = -INF_FLOAT;
  for(int i = 0; i < Size; i++) {
    if(Arr[i] > max) {
      max = Arr[i];
    }
  }
  return max;
}


/**
 * @brief Calculates the maximum value of an integer array.
 *
 * Given an array of integer values, calculates the biggest value within it.
 *
 * @param  (int*) Arr :  Array of integer values.
 * @param  (int)  Size:  Size of the array.
 * @return (int)  The biggest value of the array "arr".
 *
 * @warning This function is for floating point values only; for integers, check reference.
 * @see MaxArr_i() for integer values.
 */
int MaxArr_i(int* Arr, int Size) {  
  int max = -INF;
  for(int i = 0; i < Size; i++) {
    if(Arr[i] > max) {
      max = Arr[i];
    }
  }
  return max;
}


/**
 * @brief Calculates the power of an integer value.
 *
 * Given a number (base), calculates the multiplication of this number n (exponent) times.
 * For example, 8 to the power 2 is equal to 8 * 8 = 64.
 *
 * @param  (int)  Base    : Base number of the equation.
 * @param  (int)  Exponent: Exponent number of the equation.
 * @return (long) The solution of the base to the power of the exponent.
 *
 * @note    This function does not accepts floating point exponents because it would involve nth root computation.
 * @warning This function is for integer bases; for floating point bases, check reference.
 * @see Pow_f() for floating point bases.
 */
long Pow_i(int Base, int Exponent) { 
  int isNegative = 0;
  long Raised = 1;
  if(Exponent == 0) return 1;
  if(Exponent < 0) {
   isNegative = 1;
   Exponent = Abs(Exponent);
  }
  if(Exponent == 1) return Base;
  else if(Exponent == 2) return (Base*Base);
  for(int i = 0; i < Exponent; i++) {
    Raised *= Base;
  }
  if(isNegative) {
    return (1 / Raised);
  } else {
    return Raised;
  }
}


/**
 * @brief Calculates the power of a floating point value.
 *
 * Given a number (base), calculates the multiplication of this number n (exponent) times.
 * For example, 8.0 to the power 2 is equal to 8.0 * 8.0 = 64.0.
 *
 * @param  (float)  Base    : Base number of the equation.
 * @param  (int)    Exponent: Exponent number of the equation.
 * @return (double) The solution of the base to the power of the exponent.
 *
 * @note    This function does not accepts floating point exponents because it would involve nth root computation.
 * @warning This function is for floating point bases; for integer bases, check reference.
 * @see Pow_i() for integer bases.
 */
double Pow_f(float Base, int Exponent) {  
  int isNegative = 0;
  double Raised = 1;
  if(Exponent == 0) return 1;
  if(Exponent < 0) {
   isNegative = 1;
   Exponent = Abs(Exponent);
  }
  if(Exponent == 1) return Base;
  else if(Exponent == 2) return (Base*Base);
  for(int i = 0; i < Exponent; i++) {
    Raised *= Base;
  }
  if(isNegative) {
    return (1 / Raised);
  } else {
    return Raised;
  }
}


/**
 * @brief Calculates the sum of the elements of an array.
 *
 * Given an array of integer values, calculates the sum of all elements.
 *
 * @param  (int*) Arr : Array of integers.
 * @param  (int)  Size: Size of the array.
 * @return (long) The sum of elements of the array "arr".
 *
 * @warning This function is for arrays of integer values; for arrays of floating point values, check reference
 * @see Sum_f() for arrays of floating point values.
 */
long Sum_i(int* Arr, int Size) {  
  long Sum = 0;
  for(int i = 0; i < Size; i++) {
    Sum += Arr[i];
  }
  return Sum;
}


/**
 * @brief Calculates the sum of the elements of an array.
 *
 * Given an Array of floating point values, calculates the sum of all elements.
 *
 * @param  (int*) Arr : Array of floats.
 * @param  (int)  Size: Size of the Array.
 * @return (long) The sum of elements of the Array "Arr".
 *
 * @warning This function is for Arrays of float values; for Arrays of integers, check reference
 * @see Sum_i() for Arrays of integer values.
 */
double Sum_f(float* Arr, int Size) {  
  double Sum = 0.0;
  for(int i = 0; i < Size; i++) {
    Sum += Arr[i];
  }
  return Sum;
}





/** ERROR CALCULATIONS */


/**
 * @brief Calculates the absolute error between the real value and approximate value..
 *
 * Used for error measurement, given the real value and approximate value, computates
 * the absolute error.
 *
 * @param  (float) Value           : Real value of a measurement.
 * @param  (float) ApproximateValue: Approximate value of a measurement.
 * @return (float) The absolute error of the approximate value.
 *
 * @see RelativeError()    for relative error measurement.
 * @see RelativeErrorEA() for calculating relative error using an absolute error.
 * @see CompareError()    for comparing two errors.
 */
float AbsoluteError(float Value, float ApproximateValue) {
  return Abs(Value - ApproximateValue);
}


/**
 * @brief Calculates the relative error between the real value and approximate value.
 *
 * Used for error measurement, given the real value and approximate value, computates
 * the relative error.
 * This calculation illustrates the "quality" of the error. This differs from absolute
 * error, where absolute error does not takes in consideration the order of magnitude
 * of the value being calculated.
 *
 * @param  (float) Value           : Real value of a measurement.
 * @param  (float) ApproximateValue: Approximate value of a measurement.
 * @return (float) The relative error of the approximate value.
 *
 * @see AbsoluteError()    for absolute error measurement.
 * @see RelativeErrorEA() for calculating the relative error using an absolute error.
 * @see CompareError()     for comparing two errors.
 */
double RelativeError(float Value, float ApproximateValue) {
  if(Value) {
    return (AbsoluteError(Value, ApproximateValue) / Value);
  } else {
    printf("Invalid argument. (%f)\n", Value);
    return -1.0;
  }
}


/**
 * @brief Calculates the relative error between the real value and an absolute error.
 *
 * Used for error measurement, given the real value and absolute error, computates
 * the relative error.
 * The absolute error is the absolute difference between the real value and approximate value. 
 * This calculation illustrates the "quality" of the error. This differs from absolute
 * error, where absolute error does not takes in consideration the order of magnitude
 * of the value being calculated.
 *
 * @param  (float) Value           : Real value of a measurement.
 * @param  (float) AbsoluteError: Absolute error of a measurement.
 * @return (float) The relative error of the measurement.
 *
 * @see AbsoluteError() for absolute error measurement.
 * @see RelativeError() for calculating the relative error using an approximate value.
 * @see CompareError()  for comparing two errors.
 */
double RelativeErrorEA(float Value, float AbsoluteError) {
  if(Value) {
    return (AbsoluteError / Value);
  } else {
    printf("Invalid argument. (%f)\n", Value);
    return -1.0;
  }
}


/**
 * @brief Compare two error measurements of the same kind.
 *
 * @param  (float) Error1: The first error measurement..
 * @param  (float) Error2: The second error measurement.
 * @return (int)   The number representing the error. 1 represents the parameter error1, 2 represents the parameter error2.
 *
 * @warning beware of which kind of error measurements are being compared, if an absolute error is being compared with an relative error, issues may appear.
 * @see AbsoluteError()    for absolute error measurement.
 * @see RelativeError()    for calculating the relative error using an approximate value.
 * @see AbsoluteErrorEA() for calculating the relative error using an absolute error.
 */
int CompareError(double Error1, double Error2) {
  return (Error1 < Error2 ? 1 : 2);
}





/** VECTOR NORMS */

//NOTE: give better description of following functions
/**
 * @brief Calculates the euclidean norm of a vector.
 * 
 * @param  (float*) Values: Array of floats.
 * @param  (int)    Size  : Size of the array.
 * @return (float)  The square root of the euclidean norm of a vector.
 *
 * @note This function does not calculate the final result of the function. Instead, it calculates the value of the square root of the norm.
 * @warning This function is for one float vector only, for two, check reference. 
 * @see EucliedanNormDistance() for the distance of two vectors with euclidean norm.
 */
float EuclideanNorm(float* Values, int Size) { 
  float Sum = 0.0;
  for(int i = 0; i < Size; i++) {
    Sum += Pow_f(Values[i], 2);
  }
  return Sum;
}

/**
 * @brief Calculates the distance between to vectos with euclidean norm.
 * 
 * @param  (float*) ValuesVectorA: Vector A coordinates.
 * @param  (int)    SizeVectorA  : Size of vector A.
 * @param  (float*) ValuesVectorB: Vector B coordinates.
 * @param  (int)    SizeVectorB  : Size of vector B.
 * @return (float)  The square root of the euclidean norm between two vectors.
 *
 * @note This function does not calculate the final result of the function. Instead, it calculates the value of the square root of the norm.
 * @warning This function is for measuring the distance between two vectors. For one vector, check reference.
 * @see EucliedanNorm() for one vector only.
 */
float EuclideanNormDistance(float* ValuesVectorA, int SizeVectorA,
			    float* ValuesVectorB, int SizeVectorB) {
  float Sum = 0.0;
  int Biggest = Max(SizeVectorA, SizeVectorB);
  int Smallest = Min(SizeVectorA, SizeVectorB);
  for(int i = 0; i < Biggest; i++) {
    if(i <= Smallest) {
      Sum += Pow_f((ValuesVectorA[i] - ValuesVectorB[i]), 2);
    } else if(Smallest == SizeVectorA) {
      Sum += Pow_f(ValuesVectorA[i], 2);
    } else if(Smallest == SizeVectorB){
      Sum += Pow_f(ValuesVectorB[i], 2);
    }
  }
  return Sum;
}


float MaximumNorm(float* Values, int Size) { 
  float Max = -INF_FLOAT;
  for(int i = 0; i < Size; i++) {
    if(Max < Abs(Values[i])) {
      Max = Abs(Values[i]);
    }
  }
  if(Max != -INF_FLOAT) return Max;
  else return -1.0;
}

float MaximumNormDistance(float* ValuesVectorA, int SizeVectorA,
			  float* ValuesVectorB, int SizeVectorB) {
  float Max = -INF_FLOAT;
  int Biggest = Max(SizeVectorA, SizeVectorB);
  int Smallest = Min(SizeVectorA, SizeVectorB);
  float CurrentValue = 0.0;
  for(int i = 0; i < Biggest; i++) {
    CurrentValue = 0.0;
    if(i <= Smallest) {
      CurrentValue = Abs(ValuesVectorA[i] - ValuesVectorB[i]);
    } else if(Smallest == SizeVectorA) {
	CurrentValue = Abs(ValuesVectorA[i]);
    } else if(Smallest == SizeVectorB){
	CurrentValue = Abs(ValuesVectorB[i]);
    }
    if(CurrentValue > Max) {
      Max = CurrentValue;
    }
  }
  if(Max != -INF_FLOAT) return Max;
  else return -1.0;
}

float SumNorm(float* Values, int Size) {  
  float Sum = 0.0;
  for(int i = 0; i < Size; i++) {
    Sum += Abs(Values[i]);
  }
  return Sum;
}

float SumNormDistance(float* ValuesVectorA, int SizeVectorA,
		      float* ValuesVectorB, int SizeVectorB) {  
  float Sum = 0.0;
  int Biggest = Max(SizeVectorA, SizeVectorB);
  int Smallest = Min(SizeVectorA, SizeVectorB);
  for(int i = 0; i < Biggest; i++) {
    if(i <= Smallest) {
      Sum += Abs(ValuesVectorA[i] - ValuesVectorB[i]);
    } else if(Smallest == SizeVectorA) {
      Sum += Abs(ValuesVectorA[i]);
    } else if(Smallest == SizeVectorB) {
      Sum += Abs(ValuesVectorB[i]);
    }
  }
  return Sum;
}

/* MATRICES NORMS */

float FrobeniusNorm(float* Values, int SizeRows, int SizeColumns) {
  float Sum = 0.0;
  for(int i = 0; i < SizeRows; i++) {
    for(int j = 0; j < SizeColumns; j++) {
      Sum += Pow_f(Values[i*SizeColumns + j], 2);
    }
  }
  return Sum;
}

float RowMaximumNorm(float** Values, int SizeRows, int SizeColumns) {
  float Sum = 0.0;
  float MaxSum = -INF_FLOAT;
  for(int i = 0; i < SizeRows; i++) {
    Sum = 0.0;
    for(int j = 0; j < SizeColumns; j++) {
      Sum += Abs(Values[i][j]);
    }
    if(MaxSum < Sum) {
      MaxSum = Sum;
    }
  }
  return MaxSum;
}

float ColumnMaximumNorm(float* Values[], int SizeRows, int SizeColumns) {
  float Sum = 0.0;
  float MaxSum = -INF_FLOAT;
  for(int j = 0; j < SizeColumns ; j++) {
    Sum = 0.0;
    for(int i = 0; i < SizeRows; i++) {
      Sum += Abs(Values[i][j]);
    }
    if(MaxSum < Sum) {
      MaxSum = Sum;
    }
  }
  return MaxSum;
}

float* gauss_elimination(float* mat, int sizeRows, int sizeColumns) {
  int k = 0, i = 0, j = 0;
  float m = 0;
  for(k = 0; k < sizeRows; k++) {
    for(i = k + 1; i < sizeColumns; i++) {
      m = mat[i*(sizeColumns) + k] / mat[k*(sizeColumns) + k];
      for(j = k; j < sizeColumns+1; j++) {
	mat[i*(sizeColumns) + j] = mat[i*(sizeColumns) + j] - (m * mat[k*(sizeColumns) + j]);
      }
    }
    
  }

  for(int rows = 0; rows < sizeRows; rows++) {
    for(int columns = 0; columns < sizeColumns; columns++) {
      printf("%f ", mat[rows*(sizeColumns) + columns]);
    }
    printf("\n");
  }
  printf("\n");
  return mat;
}

/** LINEAR SYSTEM */
void gauss_resolution(float* mat, int sizeRows, int sizeColumns) {
  int k = 0, i = 0, j = 0;
  float m = 0, s = 0;
  float *x = (float*)malloc(sizeColumns * sizeof(float));
  for(i = 0; i < sizeRows; i++) {
    x[i] = 0;
  }
  for(k = 0; k < sizeRows; k++) {
    for(i = k + 1; i < sizeColumns; i++) {
      if(mat[(k*(sizeColumns)) + k] == 0) {
	printf("1\n");
	m = 1;
      } else {
	m = mat[(i*(sizeColumns)) + k] / mat[(k*(sizeColumns)) + k];
      }
      for(j = k; j < sizeColumns+1; j++) {
	mat[(i*(sizeColumns)) + j] = mat[(i*(sizeColumns)) + j] - (m*mat[(k*(sizeColumns)) + j]);
      }
    }
    if(mat[(sizeRows*sizeRows) + (sizeRows - 2)] == 0) {
      printf("2\n");
      x[sizeRows-1] = mat[(sizeRows*sizeRows) + sizeRows-1];
    } else {
      x[sizeRows-1] = mat[(sizeRows*sizeRows) + sizeRows-1] / mat[(sizeRows*sizeRows) + (sizeRows - 2)];
    }
    for(i = sizeRows-2; i >= 0; i--) {
      s = 0;
      for(j = i+1; j < sizeRows; j++) {
	s = s + mat[i*(sizeColumns) + j] * x[j];
      }
      if(mat[(i*sizeColumns) + i] == 0) {
	printf("3\n");
	x[i] = (mat[i*(sizeColumns) + sizeRows] - s);
      } else {
	x[i] = (mat[i*(sizeColumns) + sizeRows] - s) / mat[(i*sizeColumns) + i];
      }
    }
  }

  for(int rows = 0; rows < sizeRows; rows++) {
    
    printf("%f ", x[rows]);
    
    printf("\n");
  }
  printf("\n");
  //TODO: norm(a*x-b)
  free(x);
}


/** INTEGRATION */

double fint(float x) {
  // FUNCTION f(x) in Zf(x)dx. Change this as necessary
  //  ((float)1.0 / pow_f(x, 3))
  return x;
}

double simpsons13(float inferior_limit, float superior_limit, unsigned long n) {
  unsigned long m;;
  if(n % 2 != 0) {
    m = n - 1;
  } else {
    m = n;
  }
  double a = inferior_limit;
  double b = superior_limit;
  double xa = a;
  double xb = b;
  double ya = fint(xa);
  double yb = fint(xb);
  double dx = (xb - xa) / m;
  unsigned long m1 = m - 1;
  unsigned long m2 = m - 2;
  double y2 = 0, vy2 = 0, y4 = 0, vy4 = 0;
  for(int j = 1; j <= m1; j++) {
    double xj = xa + j*dx;
    if(j % 2 != 0) {
      vy4 = fint(xj);
      y4 = y4 + vy4;
    } else {
      vy2 = fint(xj);
      y2 = y2 + vy2;
    }
  }
  y4 = 4*y4;
  y2 = 2*y2;
  double result = (ya + yb + y2 + y4)*dx*(1.0/3);
  return result;
}


double limit(int n) {
  float TermsToInfinity[11];
  for(int i = n-11; i < n; i++) {
    float value = fint(i);
    if(value >= 1e8) {
      return 1e8;
    } else {
      TermsToInfinity[i] = value;
    }
  }
  int hasLimit = 1;
  int divergent = 0;
  for(int x = n-11; x < n; x++) {
    if((int)TermsToInfinity[x] != (int)TermsToInfinity[n-1]) {
      divergent = (int)TermsToInfinity[x];
      hasLimit = 0;
    }
  }
  float rounded = TermsToInfinity[n-1];
  if(!hasLimit) {
    if(TermsToInfinity[n-1] >= 1e5) {
      return 1e8;
    } else {
      return -1;
    }
  } else {
    return rounded;
  }
}
