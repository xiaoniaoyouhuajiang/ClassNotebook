#include "ellipse.h"
#include "shape.h"
void Ellipse::scale(double coefficient) {
    e_a *= coefficient;
    e_b *= coefficient;
}
