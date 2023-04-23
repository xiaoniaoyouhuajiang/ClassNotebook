#include "vector.h"
#include "shared_ptr.h"
#include "figure.h"
#include "lab_fun.h"
#include <iostream>


int main () {
  shapeVec a;
  shapeVec b;

  generateShapes(a,5000);
  generateShapes(a,5000);

  std::cout << isPartitioned(a) << "\n";
  std::cout << (intersection(a, b)).size();
  
  return 0;
}
