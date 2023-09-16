#include "albos.h"
#include <stdio.h>

int main() {
  int intVector[3] = {-2, 1, 6};
  //float matrix[3][4] = { {25555, 2401, 247, 10373.69}, {2401, 247, 31, 962.73}, {247, 31, 7, 97.76} };
  int sizeRows = 4, sizeColumns = 5;
  float matrix[4][5] = { {3, 2, 1, 2, 141},
					  {6, 7, 4, 5, 382},
					  {3, 8, 6, 7, 403},
					  {9, 9, 7, 15, 677} };
  //float matrix[3][4] = { {3, -0.1, -0.2, 7.85}, {0.1, 7, -0.3, -19.3}, {0.3, -0.2, 10, 71.4} };

  //float *res = gauss_elimination(*matrix, 3, 4);
  gauss_resolution(*matrix, sizeRows, sizeColumns); 
  //float floatVector[3] = {1.2001, 0.99991, 0.92538};
  //float result = maximum_norm_f(floatVector, 3);
  //float resultFloat =  euclidean_norm_f(floatVector, 3);
  //  printf("int: %d\nfloat: %f", resultInt, resultFloat);
  //printf("result: %f\n", result);
 return 0;
}
