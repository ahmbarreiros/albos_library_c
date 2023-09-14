#include "albos.h"
#include <stdio.h>

int main() {
  int intVector[3] = {-2, 1, 6};
  //float matrix[3][4] = { {25555, 2401, 247, 10373.69}, {2401, 247, 31, 962.73}, {247, 31, 7, 97.76} };
  float matrix[3][4] = { {3, -0.1, -0.2, 7.85}, {0.1, 7, -0.3, -19.3}, {0.3, -0.2, 10, 71.4} };
  int size = 3;
  gauss(*matrix, 3);
  float floatVector[3] = {1.2001, 0.99991, 0.92538};
  float result = maximum_norm_f(floatVector, 3);
  //float resultFloat =  euclidean_norm_f(floatVector, 3);
  //  printf("int: %d\nfloat: %f", resultInt, resultFloat);
  printf("result: %f\n", result);
 return 0;
}
