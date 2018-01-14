//math.c
#include "math.h"

int add(int x, int y){
  return x+y;
}

long long power(int x, int n){
  long long result = 1;
  for(int i = 0; i < n; i++){
    result *= x;
  }
  return result;
}
