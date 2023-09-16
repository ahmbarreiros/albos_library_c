#include <stdio.h>
#include <stdlib.h>
#include "albos.h"

#define INF_FLOAT (1 << (sizeof(float))) - 1
#define INF (1L <<(sizeof(int))) - 1

long abs_i(long x) {
  if(x >= 0) return x;
  else return -x; 
}

double abs_f(double x) {
  if(x >= 0) return x;
  else return -x;
}

int max_i(int x, int y) {
  if(x > y) return x;
  else return y;
}

int min_i(int x, int y) {
  if(x <= y) return x;
  else return y;
}

float max_arr_f(float* values, int size) { 
  float max = -INF_FLOAT;
  for(int i = 0; i < size; i++) {
    if(values[i] > max) {
      max = values[i];
    }
  }
  return max;
}

int max_arr_i(int* values, int size) {  
  int max = -INF;
  for(int i = 0; i < size; i++) {
    if(values[i] > max) {
      max = values[i];
    }
  }
  return max;
}

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

long sum_i(int* values, int size) {  
  long sum = 0;
  for(int i = 0; i < size; i++) {
    sum += values[i];
  }
  return sum;
}

double sum_f(float* values, int size) {  
  double sum = 0.0;
  for(int i = 0; i < size; i++) {
    sum += values[i];
  }
  return sum;
}




/* ERROR CALCULATIONS */

float absolute_error(float value, float approximateValue) {
  return abs_f(value - approximateValue);
}

double relative_error(float value, float approximateValue) {
  if(value) {
    return (absolute_error(value, approximateValue) / value);
  } else {
    printf("Invalid argument. (%f)\n", value);
    return -1.0;
  }
}

double relative_error_ea(float value, float absoluteError) {
  if(value) {
    return (absoluteError / value);
  } else {
    printf("Invalid argument. (%f)\n", value);
    return -1.0;
  }
}

int compare_error(double error1, double error2) {
  return (error1 < error2 ? 1 : 2);
}


/* VECTOR NORMS */

float euclidean_norm_f(float* values, int size) { 
  float sum = 0.0;
  for(int i = 0; i < size; i++) {
    sum += pow_f(values[i], 2);
  }
  return sum;
}

long euclidean_norm_i(int* values, int size) {  
  long sum = 0;
  for(int i = 0; i < size; i++) {
    sum += pow_i(values[i], 2);
  }
  return sum;
}

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
  /* for(int rows = 0; rows < size; rows++) { */
  /*   for(int columns = 0; columns < size+1; columns++) { */
  /*     printf("%f ", mat[rows*(size+1) + columns]); */
  /*   } */
  /*   printf("\n"); */
  /* } */
  
  for(k = 0; k < sizeRows; k++) {
    for(i = k + 1; i < sizeColumns; i++) {
      //printf("mat1 = %f\n", mat[i*(size+1) + k]);
      //printf("\t %f / %f\n", mat[i*(size+1) + k], mat[k*(size+1) + k]);
      m = mat[i*(sizeColumns) + k] / mat[k*(sizeColumns) + k];
      //printf("mat2 = %f\n", mat[k*(size+1) + k]);
      //printf("m = %f\n", m);
      // mat[i*(size + 1) + k] = 0;
      
      for(j = k; j < sizeColumns+1; j++) {
	//printf("mat3 = %f\n", mat[i*(size+1) + j]);
	mat[i*(sizeColumns) + j] = mat[i*(sizeColumns) + j] - (m * mat[k*(sizeColumns) + j]);
	//printf("mat4 = %f\n", mat[i*(size+1) + j]);
	for(int rows = 0; rows < sizeRows; rows++) {
	  for(int columns = 0; columns < sizeColumns; columns++) {
	    printf("%f ", mat[rows*(sizeColumns) + columns]);
	  }
	  printf("\n");
	}
	printf("\n");
      }
    }
    
  }

  for(int rows = 0; rows < sizeRows; rows++) {
    for(int columns = 0; columns < sizeColumns; columns++) {
      printf("%f ", mat[rows*(sizeColumns) + columns]);
    }
    printf("\n");
  }
  printf("cabou\n");
  return mat;
}

void gauss_resolution(float* mat, int size) {
  int k = 0, i = 0, j = 0;
  float m = 0, s = 0;
  float *x = malloc(size * sizeof(float));
  for(i = 0; i < size; i++) {
    x[i] = 0;
  }
  /* printf("1\n"); */
  /* for(int rows = 0; rows < size; rows++) { */
  /*   printf("%f ", x[rows]); */
  /*   printf("\n"); */
  /* } */
  /* printf("\n"); */

  for(k = 0; k < size; k++) {
    for(i = k + 1; i < size+1; i++) {
      m = mat[i * (size + 1) + k] / mat[k*(size+1) + k];
      for(j = k; j < size+2; j++) {
	mat[i*(size+1) + j] = mat[i*(size+1) + j] - (m*mat[k*(size+1) + j]);
      }
    }
    printf("\tafter\n");
    /* for(int rows = 0; rows < size; rows++) { */
    /*   for(int columns = 0; columns < size+1; columns++) { */
    /* 	printf("%f ", mat[rows*(size+1) + columns]); */
    /*   } */
    /*   printf("\n"); */
    /* } */
    //printf("cabou\n");
    //printf("%f\n", x[size-1]);
    printf("\t %f / %f\n", mat[size*size + size-1], mat[size*size + size-2]);
    x[size-1] = mat[size*size + size-1] / mat[size*size + size-2];
    printf("%f\n", x[size-1]);
    for(i = size-2; i >= 0; i--) {
      s = 0;
      for(j = i+1; j < size; j++) {
	printf("\tantes: %f\n", s);
	s = s + mat[i*(size+1) + j] * x[j];
	printf("\tdepois: %f\n", s);
      }
      printf("\tantes X: %f\n", x[i]);
      x[i] = (mat[i*(size+1) + size] - s) / mat[i*(size+1) + i];
      printf("\tdepois X: %f\n", x[i]);
    }
  }

  for(int rows = 0; rows < size; rows++) {
    
    printf("%f ", x[rows]);
    
    printf("\n");
  }

  //TODO: norm(a*x-b)
  free(x);
}
