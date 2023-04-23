#include <iostream>
#include "shape.h"
#include "pentagon.h"
#include "triangle.h"
#include "trap.h"

int main() {

  Triangle t({0, 0}, {2, 2}, {-2, -2});
  std::cout << t << std::endl << std::endl;

  t.rotate(50);
  std::cout << t << std::endl << std::endl;

  RegularPentagon p({0, 0}, 2);
  std::cout << p << std::endl << std::endl;

  p*2;
  std::cout << p << std::endl << std::endl;

  p.move(2, 2);
  std::cout << p << std::endl << std::endl;

  p.rotate(25);
  std::cout << p << std::endl << std::endl;

  Trap tr({0, 2}, {2, 2}, {-2, -2}, {4, -2});
  std::cout << tr << std::endl << std::endl;

  tr.rotate(12);
  std::cout << tr << std::endl << std::endl;
}
