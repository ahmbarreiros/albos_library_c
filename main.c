#include "albos.h"
#include <stdio.h>

int main() {

  //double result = 15.0 / 7;
  
  /* double absError = absolute_error(7.4, 7.3); */
  double relError1 = relative_error((15/7.0), 2.142);
  double relError2 = relative_error((15/7.0), 2.143);
  printf("err1: %f\nerr2: %f\n", relError1, relError2);
  double result = compare_error(relError1, relError2);
  printf("result: %f\n", result);
  /* printf("absolute: %f\nrelative: %f\nin percentage: %f\%", absError, relError, (relError * 100)); */
  
 return 0;
}
