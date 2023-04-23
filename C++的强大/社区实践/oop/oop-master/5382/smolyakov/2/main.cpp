
#include <iostream>
#include "figure.h"

int main() {
  Shape* b = new Rhombus(2, 3.14/4.0);
  Parallelogram c(50, 50);
  //std::cout << b <<" " << c<< " " << b.pointLocal(Point(1,0.01)) << " " << c.isInsideOfAnother(b)  << std::endl; 

  
  
  std::cout << *b << std::endl;
  return 1;
}
