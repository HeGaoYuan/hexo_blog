extern "C" {
#include "math.h"
}
#include <iostream>
using namespace std;

int main(){
  int a = add(2, 5);
  int b = power(2, 5);  
  cout << "add(2, 5) is: " << a << endl;
  cout << "power(2, 5) is: " << b << endl;
  return 0;
}
