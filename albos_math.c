#include <stdio.h>
#include "albos.h"

#define INF_DOUBLE (1 << (sizeof(double))) - 1
#define INF (1L <<(sizeof(long))) - 1

long abs_i(long x) {
  if(x >= 0) return x;
  else return -x; 
}

double abs_f(double x) {
  if(x >= 0) return x;
  else return -x;
}

double max_arr_f(double* values, int size) {  // TODO: testar
  double max = -INF_DOUBLE;
  for(int i = 0; i < size; i++) {
    if(values[i] > max) {
      max = values[i];
    }
  }
  return max;
}

long max_arr_i(long* values, int size) {  // TODO: testar
  long max = -INF;
  for(int i = 0; i < size; i++) {
    if(values[i] > max) {
      max = values[i];
    }
  }
  return max;
}

double pow_f(double base, int exponent) {  // TODO: testar
  int isNegative = 0;
  double raised = 1;
  if(exponent == 0) return 1;
  if(exponent < 0) {
   isNegative = 1;
   exponent = abs_i(exponent);
  }
  for(int i = 0; i < exponent; i++) {
    raised *= base;
  }
  if(isNegative) {
    return (1 / raised);
  } else {
    return raised;
  }
}

long pow_i(long base, int exponent) {  // TODO: testar
  int isNegative = 0;
  long raised = 1;
  if(exponent == 0) return 1;
  if(exponent < 0) {
   isNegative = 1;
   exponent = abs_i(exponent);
  }
  for(int i = 0; i < exponent; i++) {
    raised *= base;
  }
  if(isNegative) {
    return (1 / raised);
  } else {
    return raised;
  }
}

long sum_i(long* values, int size) {  // TODO: testar
  long sum = 0;
  for(int i = 0; i < size; i++) {
    sum += values[i];
  }
  return sum;
}

double sum_f(double* values, int size) {  // TODO: testar
  double sum = 0.0;
  for(int i = 0; i < size; i++) {
    sum += values[i];
  }
  return sum;
}




/* ERROR CALCULATIONS */

double absolute_error(double value, double approximateValue) {
  return abs_f(value - approximateValue);
}

double relative_error(double value, double approximateValue) {
  if(value) {
    return (absolute_error(value, approximateValue) / value);
  } else {
    printf("Invalid argument. (%f)\n", value);
    return -1.0;
  }
}

double relative_error_ea(double value, double absoluteError) {
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


/* VECTOR AND MATRICES NORMS */

double euclidean_norm_f(double* values, int size) {  // TODO: testar
  double sum = 0.0;
  for(int i = 0; i < size; i++) {
    sum += pow_f(values[i], 2);
  }
  return sum;
}

long euclidean_norm_i(long* values, int size) {  // TODO: testar
  long sum = 0;
  for(int i = 0; i < size; i++) {
    sum += pow_i(values[i], 2);
  }
  return sum;
}

double maximum_norm_f(double* values, int size) {  // TODO: testar
  return max_arr_f(values, size);
}

long maximum_norm_i(long* values, int size) {  // TODO: testar
  return max_arr_i(values, size);
}

double sum_norm_f(double* values, int size) {  // TODO: testar
  double sum = 0.0;
  for(int i = 0; i < size; i++) {
    sum += abs_f(values[i]);
  }
  return sum;
}

long sum_norm_i(long* values, int size) { // TODO: testar
  long sum = 0;
  for(int i = 0; i < size; i++) {
    sum += abs_i(values[i]);
  }
  return sum;
}
