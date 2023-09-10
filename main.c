#include "albos.h"
#include <stdio.h>

int main() {
  float intVector[3] = {1.0, 1.0, 1.0};
  float floatVector[3] = {1.2001, 0.99991, 0.92538};
  float result = sum_norm_distance_f(intVector, 3, floatVector, 3);
  //float resultFloat =  euclidean_norm_f(floatVector, 3);
  //  printf("int: %d\nfloat: %f", resultInt, resultFloat);
  printf("result: %f\n", result);
 return 0;
}
