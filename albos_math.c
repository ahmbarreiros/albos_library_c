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
 * @brief Return the absolute value of a integer number.
 *
 * Given a integer value "x", returns the absolute value of the number.
 * It accepts and returns long numbers.
 *
 * @param  (long) x: Long integer.
 * @return (long) Integer "x" that represents the absolute value of parameter "x".
 *
 * @warning This function is for integer values only; for floats, check reference.
 * @see abs_f() for floating point values.
 */
long abs_i(long x) {
  
  if(x >= 0) return x;
  else return -x; 
}


/**
 * @brief Return the absolute value of a floating point number.
 *
 * Given a floating point value "x", returns the absolute value of the number.
 * It accepts and returns double numbers.
 *
 * @param  (double) x: Floating point value.
 * @return (double) Double value "x" that represents the absolute value of parameter "x".
 *
 * @warning This function is for floating values only; for integers, check reference.
 * @see abs_i() for integer values.
 */
double abs_f(double x) {
  if(x >= 0) return x;
  else return -x;
}


/**
 * @brief Given two integer values, returns the biggest.
 *
 * @param  (int) x: Integer value.
 * @param  (int) y: Integer value.
 * @return (int) Compares parameters "x" and "y", and returns the biggest value between them.
 *
 * @warning This function is for integer values only; for floats, check reference.
 * @see min_i() for smallest comparison.
 */
int max_i(int x, int y) {
  if(x > y) return x;
  else return y;
}


/**
 * @brief Given two integer values, returns the smallest.
 *
 * @param  (int) x: Integer value.
 * @param  (int) y: Integer value.
 * @return (int) Compares parameters "x" and "y", and returns the smallest value between them.
 *
 * @warning This function is for integer values only; for floats, check reference.
 * @see max_i() for biggest comparison.
 */
int min_i(int x, int y) {
  if(x <= y) return x;
  else return y;
}


/**
 * @brief Calculates the maximum value of a float array.
 *
 * Given an array of floating point values, calculates the biggest value within it.
 *
 * @param  (float*) arr : Array of floating point values.
 * @param  (int)    size: Size of the array.
 * @return (float)  The biggest value of the array "arr".
 *
 * @warning This function is for floating point values only; for integers, check reference.
 * @see max_arr_i() for integer values.
 */
float max_arr_f(float* arr, int size) { 
  float max = -INF_FLOAT;
  for(int i = 0; i < size; i++) {
    if(arr[i] > max) {
      max = arr[i];
    }
  }
  return max;
}


/**
 * @brief Calculates the maximum value of an integer array.
 *
 * Given an array of integer values, calculates the biggest value within it.
 *
 * @param  (int*) arr :  Array of integer values.
 * @param  (int)  size:  Size of the array.
 * @return (int)  The biggest value of the array "arr".
 *
 * @warning This function is for floating point values only; for integers, check reference.
 * @see max_arr_i() for integer values.
 */
int max_arr_i(int* values, int size) {  
  int max = -INF;
  for(int i = 0; i < size; i++) {
    if(values[i] > max) {
      max = values[i];
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
 * @param  (int)  base    : Base number of the equation.
 * @param  (int)  exponent: Exponent number of the equation.
 * @return (long) The solution of the base to the power of the exponent.
 *
 * @note    This function does not accepts floating point exponents because it would involve nth root computation.
 * @warning This function is for integer bases; for floating point bases, check reference.
 * @see pow_f() for floating point bases.
 */
long pow_i(int base, int exponent) { 
  int isNegative = 0;
  long raised = 1;
  if(exponent == 0) return 1;
  if(exponent < 0) {
   isNegative = 1;
   exponent = abs_i(exponent);
  }
  if(exponent == 1) return base;
  else if(exponent == 2) return (base*base);
  for(int i = 0; i < exponent; i++) {
    raised *= base;
  }
  if(isNegative) {
    return (1 / raised);
  } else {
    return raised;
  }
}


/**
 * @brief Calculates the power of a floating point value.
 *
 * Given a number (base), calculates the multiplication of this number n (exponent) times.
 * For example, 8.0 to the power 2 is equal to 8.0 * 8.0 = 64.0.
 *
 * @param  (float)  base    : Base number of the equation.
 * @param  (int)    exponent: Exponent number of the equation.
 * @return (double) The solution of the base to the power of the exponent.
 *
 * @note    This function does not accepts floating point exponents because it would involve nth root computation.
 * @warning This function is for floating point bases; for integer bases, check reference.
 * @see pow_i() for integer bases.
 */
double pow_f(float base, int exponent) {  
  int isNegative = 0;
  double raised = 1;
  if(exponent == 0) return 1;
  if(exponent < 0) {
   isNegative = 1;
   exponent = abs_i(exponent);
  }
  if(exponent == 1) return base;
  else if(exponent == 2) return (base*base);
  for(int i = 0; i < exponent; i++) {
    raised *= base;
  }
  if(isNegative) {
    return (1 / raised);
  } else {
    return raised;
  }
}


/**
 * @brief Calculates the sum of the elements of an array.
 *
 * Given an array of integer values, calculates the sum of all elements.
 *
 * @param  (int*) arr : Array of integers.
 * @param  (int)  size: Size of the array.
 * @return (long) The sum of elements of the array "arr".
 *
 * @warning This function is for arrays of integer values; for arrays of floating point values, check reference
 * @see sum_f() for arrays of floating point values.
 */
long sum_i(int* arr, int size) {  
  long sum = 0;
  for(int i = 0; i < size; i++) {
    sum += arr[i];
  }
  return sum;
}


/**
 * @brief Calculates the sum of the elements of an array.
 *
 * Given an array of floating point values, calculates the sum of all elements.
 *
 * @param  (int*) arr : Array of floats.
 * @param  (int)  size: Size of the array.
 * @return (long) The sum of elements of the array "arr".
 *
 * @warning This function is for arrays of float values; for arrays of integers, check reference
 * @see sum_i() for arrays of integer values.
 */
double sum_f(float* arr, int size) {  
  double sum = 0.0;
  for(int i = 0; i < size; i++) {
    sum += arr[i];
  }
  return sum;
}





/** ERROR CALCULATIONS */


/**
 * @brief Calculates the absolute error between the real value and approximate value..
 *
 * Used for error measurement, given the real value and approximate value, computates
 * the absolute error.
 *
 * @param  (float) value           : Real value of a measurement.
 * @param  (float) approximateValue: Approximate value of a measurement.
 * @return (float) The absolute error of the approximate value.
 *
 * @see relative_error()    for relative error measurement.
 * @see relative_error_ea() for calculating relative error using an absolute error.
 *  @see compare_error()    for comparing two errors.
 */
float absolute_error(float value, float approximateValue) {
  return abs_f(value - approximateValue);
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
 * @param  (float) value           : Real value of a measurement.
 * @param  (float) approximateValue: Approximate value of a measurement.
 * @return (float) The relative error of the approximate value.
 *
 * @see absolute_error()    for absolute error measurement.
 * @see relative_error_ea() for calculating the relative error using an absolute error.
 * @see compare_error()     for comparing two errors.
 */
double relative_error(float value, float approximateValue) {
  if(value) {
    return (absolute_error(value, approximateValue) / value);
  } else {
    printf("Invalid argument. (%f)\n", value);
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
 * @param  (float) value           : Real value of a measurement.
 * @param  (float) absoluteError: Absolute error of a measurement.
 * @return (float) The relative error of the measurement.
 *
 * @see absolute_error() for absolute error measurement.
 * @see relative_error() for calculating the relative error using an approximate value.
 * @see compare_error()  for comparing two errors.
 */
double relative_error_ea(float value, float absoluteError) {
  if(value) {
    return (absoluteError / value);
  } else {
    printf("Invalid argument. (%f)\n", value);
    return -1.0;
  }
}


/**
 * @brief Compare two error measurements of the same kind.
 *
 * @param  (float) error1: The first error measurement..
 * @param  (float) error2: The second error measurement.
 * @return (int)   The number representing the error. 1 represents the parameter error1, 2 represents the parameter error2.
 *
 * @warning beware of which kind of error measurements are being compared, if an absolute error is being compared with an relative error, issues may appear.
 * @see absolute_error()    for absolute error measurement.
 * @see relative_error()    for calculating the relative error using an approximate value.
 * @see absolute_error_ea() for calculating the relative error using an absolute error.
 */
int compare_error(double error1, double error2) {
  return (error1 < error2 ? 1 : 2);
}





/** VECTOR NORMS */

//NOTE: give better description of following functions
/**
 * @brief Calculates the euclidean norm of a vector.
 * 
 * @param  (float*) values: Array of floats.
 * @param  (int)    size  : Size of the array.
 * @return (float)  The square root of the euclidean norm of a vector.
 *
 * @note This function does not calculate the final result of the function. Instead, it calculates the value of the square root of the norm.
 * @warning This function is for one float vector only, for two, check reference. 
 * @see euclidean_norm_i() for integers.
 * @see eucliedan_norm_distance_f() for the distance of two vectors with euclidean norm.
 */
float euclidean_norm_f(float* values, int size) { 
  float sum = 0.0;
  for(int i = 0; i < size; i++) {
    sum += pow_f(values[i], 2);
  }
  return sum;
}


//TODO: remove this function, as it is redundant to euclidean_norm_f().
long euclidean_norm_i(int* values, int size) {  
  long sum = 0;
  for(int i = 0; i < size; i++) {
    sum += pow_i(values[i], 2);
  }
  return sum;
}


/**
 * @brief Calculates the distance between to vectos with euclidean norm.
 * 
 * @param  (float*) valuesVectorA: Vector A coordinates.
 * @param  (int)    sizeVectorA  : Size of vector A.
 * @param  (float*) valuesVectorB: Vector B coordinates.
 * @param  (int)    sizeVectorB  : Size of vector B.
 * @return (float)  The square root of the euclidean norm between two vectors.
 *
 * @note This function does not calculate the final result of the function. Instead, it calculates the value of the square root of the norm.
 * @warning This function is for measuring the distance between two vectors. For one vector, check reference.
 * @see eucliedan_norm_f() for one vector only.
 */
float euclidean_norm_distance_f(float* valuesVectorA, int sizeVectorA,
				float* valuesVectorB, int sizeVectorB) {
  float sum = 0.0;
  int biggest = max_i(sizeVectorA, sizeVectorB);
  int smallest = min_i(sizeVectorA, sizeVectorB);
  for(int i = 0; i < biggest; i++) {
    if(i <= smallest) {
      sum += pow_f((valuesVectorA[i] - valuesVectorB[i]), 2);
    } else if(smallest == sizeVectorA) {
      sum += pow_f(valuesVectorA[i], 2);
    } else if(smallest == sizeVectorB){
      sum += pow_f(valuesVectorB[i], 2);
    }
  }
  return sum;
}

//TODO: delete this function as its redundant
long euclidean_norm_distance_i(int* valuesVectorA, int sizeVectorA,
			       int* valuesVectorB, int sizeVectorB) {
  long sum = 0;
  int biggest = max_i(sizeVectorA, sizeVectorB);
  int smallest = min_i(sizeVectorA, sizeVectorB);
  for(int i = 0; i < biggest; i++) {
    if(i <= smallest) {
      sum += pow_i((valuesVectorA[i] - valuesVectorB[i]), 2);
    } else if(smallest == sizeVectorA) {
      sum += pow_i(valuesVectorA[i], 2);
    } else if(smallest == sizeVectorB){
      sum += pow_i(valuesVectorB[i], 2);
    }
  }
  return sum;
}

float maximum_norm_f(float* values, int size) { 
  float max = -INF_FLOAT;
  for(int i = 0; i < size; i++) {
    if(max < abs_f(values[i])) {
      max = abs_f(values[i]);
    }
  }
  if(max != -INF_FLOAT) return max;
  else return -1.0;
}

int maximum_norm_i(int* values, int size) {
  int max = -INF;
  for(int i = 0; i < size; i++) {
    if(max < abs_i(values[i])) {
      max = abs_i(values[i]);
    }
  }
  if(max != -INF) return max;
  else return -1;
}

float maximum_norm_distance_f(float* valuesVectorA, int sizeVectorA,
			      float* valuesVectorB, int sizeVectorB) {
  float max = -INF_FLOAT;
  int biggest = max_i(sizeVectorA, sizeVectorB);
  int smallest = min_i(sizeVectorA, sizeVectorB);
  float currentValue = 0.0;
  for(int i = 0; i < biggest; i++) {
    currentValue = 0.0;
    if(i <= smallest) {
      currentValue = abs_f(valuesVectorA[i] - valuesVectorB[i]);
    } else if(smallest == sizeVectorA) {
	currentValue = abs_f(valuesVectorA[i]);
    } else if(smallest == sizeVectorB){
	currentValue = abs_f(valuesVectorB[i]);
    }
    if(currentValue > max) {
      max = currentValue;
    }
  }
  if(max != -INF_FLOAT) return max;
  else return -1.0;
}


int maximum_norm_distance_i(int* valuesVectorA, int sizeVectorA,
			      int* valuesVectorB, int sizeVectorB) {
  int max = -INF;
  int biggest = max_i(sizeVectorA, sizeVectorB);
  int smallest = min_i(sizeVectorA, sizeVectorB);
  int currentValue = 0;
  for(int i = 0; i < biggest; i++) {
    currentValue = 0.0;
    if(i <= smallest) {
      currentValue = abs_f(valuesVectorA[i] - valuesVectorB[i]);
    } else if(smallest == sizeVectorA) {
	currentValue = abs_f(valuesVectorA[i]);
    } else if(smallest == sizeVectorB){
	currentValue = abs_f(valuesVectorB[i]);
    }
    if(currentValue > max) {
      max = currentValue;
    }
  }
  if(max != -INF) return max;
  else return -1;
}

float sum_norm_f(float* values, int size) {  
  float sum = 0.0;
  for(int i = 0; i < size; i++) {
    sum += abs_f(values[i]);
  }
  return sum;
}

long sum_norm_i(int* values, int size) { 
  long sum = 0;
  for(int i = 0; i < size; i++) {
    sum += abs_i(values[i]);
  }
  return sum;
}


float sum_norm_distance_f(float* valuesVectorA, int sizeVectorA,
			  float* valuesVectorB, int sizeVectorB) {  
  float sum = 0.0;
  int biggest = max_i(sizeVectorA, sizeVectorB);
  int smallest = min_i(sizeVectorA, sizeVectorB);
  for(int i = 0; i < biggest; i++) {
    if(i <= smallest) {
      sum += abs_f(valuesVectorA[i] - valuesVectorB[i]);
    } else if(smallest == sizeVectorA) {
      sum += abs_f(valuesVectorA[i]);
    } else if(smallest == sizeVectorB) {
      sum += abs_f(valuesVectorB[i]);
    }
  }
  return sum;
}


int sum_norm_distance_i(int* valuesVectorA, int sizeVectorA,
			int* valuesVectorB, int sizeVectorB) {  
  int sum = 0.0;
  int biggest = max_i(sizeVectorA, sizeVectorB);
  int smallest = min_i(sizeVectorA, sizeVectorB);
  for(int i = 0; i < biggest; i++) {
    if(i <= smallest) {
      sum += abs_f(valuesVectorA[i] - valuesVectorB[i]);
    } else if(smallest == sizeVectorA) {
      sum += abs_f(valuesVectorA[i]);
    } else if(smallest == sizeVectorB) {
      sum += abs_f(valuesVectorB[i]);
    }
  }
  return sum;
}

/* MATRICES NORMS */

float frobenius_norm_f(float* values, int sizeRows, int sizeColumns) {
  float sum = 0.0;
  for(int i = 0; i < sizeRows; i++) {
    for(int j = 0; j < sizeColumns; j++) {
      sum += pow_f(values[i*sizeColumns + j], 2);
    }
  }
  return sum;
}

long frobenius_norm_i(int* values, int sizeRows, int sizeColumns) {
  long sum = 0;
  for(int i = 0; i < sizeRows; i++) {
    for(int j = 0; j < sizeColumns; j++) {
      sum += pow_i(values[i*sizeColumns + j], 2);
    }
  }
  return sum;
}

float row_maximum_norm_f(float** values, int sizeRows, int sizeColumns) {
  float sum = 0.0;
  float maxSum = -INF_FLOAT;
  for(int i = 0; i < sizeRows; i++) {
    sum = 0.0;
    for(int j = 0; j < sizeColumns; j++) {
      sum += abs_f(values[i][j]);
    }
    if(maxSum < sum) {
      maxSum = sum;
    }
  }
  return maxSum;
}

long row_maximum_norm_i(int** values, int sizeRows, int sizeColumns) {
  long sum = 0;
  long maxSum = -INF;
  for(int i = 0; i < sizeRows; i++) {
    sum = 0;
    for(int j = 0; j < sizeColumns; j++) {
      sum += abs_i(values[i][j]);
    }
    if(maxSum < sum) {
      maxSum = sum;
    }
  }
  return maxSum;
}

float column_maximum_norm_f(float* values[], int sizeRows, int sizeColumns) {
  float sum = 0.0;
  float maxSum = -INF_FLOAT;
  for(int j = 0; j < sizeColumns ; j++) {
    sum = 0.0;
    for(int i = 0; i < sizeRows; i++) {
      sum += abs_f(values[i][j]);
    }
    if(maxSum < sum) {
      maxSum = sum;
    }
  }
  return maxSum;
}

long column_maximum_norm_i(int** values, int sizeRows, int sizeColumns) {
  long sum = 0;
  long maxSum = -INF;
  for(int j = 0; j < sizeColumns; j++) {
    sum = 0;
    for(int i = 0; i < sizeRows; i++) {
      sum += abs_i(values[i][j]);
    }
    if(maxSum < sum) {
      maxSum = sum;
    }
  }
  return maxSum;
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
  float *x = malloc(sizeColumns * sizeof(float));
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
  return exp(x);
}

double simpsons13(float inferior_limit, float superior_limit, unsigned long n) {
  //printf("sl: %f\n", superior_limit);
  
  unsigned long m;;
  if(n % 2 != 0) {
    m = n - 1;
  } else {
    m = n;
  }
  //printf("\tn: %d\n", n);
  //printf("\tm: %f\n", m);
  double a = inferior_limit;
  double b = superior_limit;
  double xa = a;
  double xb = b;
  double ya = fint(xa);
  double yb = fint(xb);
  //printf("\ta: %f\n", a);
  //printf("\txa: %f\n", xa);
  //printf("\tb: %f\n", b);
  //printf("\txb: %f\n", xb);
  //printf("\tya: %f\n", ya);
  //printf("\tyb: %f\n", yb);
  double dx = (xb - xa) / m;

  printf("\tdx: %f\n", dx);
  unsigned long m1 = m - 1;
  unsigned long m2 = m - 2;
  //printf("\tm1: %f\n", m1);
  //printf("\tm2: %f\n", m2);

  double y2 = 0, vy2 = 0, y4 = 0, vy4 = 0;
  //printf("\ty2: %f\n", y2);
  //printf("\tvy2: %f\n", vy2);
  //printf("\ty4: %f\n", y4);
  //printf("\tvy4: %f\n", vy4);
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
  //printf("\t\ty2: %f\n", y2);
  //printf("\t\tvy2: %f\n", vy2);
  //printf("\t\ty4: %f\n", y4);
  //printf("\t\tvy4: %f\n\n", vy4);
  y4 = 4*y4;
  y2 = 2*y2;
  //printf("\t\ty2: %f\n", y2);
  //printf("\t\tvy2: %f\n", vy2);
  //printf("\t\ty4: %f\n", y4);
  //printf("\t\tvy4: %f\n\n", vy4);
  double result = (ya + yb + y2 + y4)*dx*(1.0/3);
  return result;
}
