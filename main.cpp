#include "albos.h"
#include <stdio.h>
#include <math.h>

int main() {
  
  //float matrix[3][4] = { {25555, 2401, 247, 10373.69}, {2401, 247, 31, 962.73}, {247, 31, 7, 97.76} };
  
  //TODO: error, possible division by 0
  /* float matrix[3][4] = {{0, 8, 2, -7}, {3, 5, 2, 8}, {6, 2, 8, 26}}; */
  
  //float matrix[2][3] = {{0.0003, 3, 2.0001}, {1, 1, 1}};
  //int sizeRows = 3, sizeColumns = 4;
  
  /* float matrix[3][4] = { {3, -0.1, -0.2, 7.85}, */
  /* 			 {0.1, 7, -0.3, -19.3}, */
  /* 			 {0.3, -0.2, 10, 71.4} }; */

  //float *res = gauss_elimination(*matrix, 3, 4);
  //gauss_resolution(*matrix, sizeRows, sizeColumns);
  // float InferiorLimit = 0;
  // float SuperiorLimit = 1;
  // unsigned long n = (SuperiorLimit - InferiorLimit) / 2;
  // double result = simpsons13(InferiorLimit, SuperiorLimit, 10);
  // printf("result: %f\n", result);

  double res = limit(1e6);
  printf("result: %f\n", res);
 return 0;
}
