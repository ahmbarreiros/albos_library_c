#include <stdio.h>

long absi(long x) {
  if(x >= 0) return x;
  else return -x; 
}

double absf(double x) {
  if(x >= 0) return x;
  else return -x;
}

double absolute_error_integer(double value, double approximateValue) {
  return abs(value - approximateValue)
}

double relative_error(double value, double approximateValue) {
  
  return (absolute_error(value, approximateValue) / value);
}
