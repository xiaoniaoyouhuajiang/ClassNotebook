#include <iostream>
#include "figure.hpp"
#include "vector.hpp"
#include "shared_ptr.hpp"
#include "functions.hpp"

int main()
{
    shapeVec a;
    shapeVec b;
    
    generateShapes(a,5000);
    generateShapes(a,5000);
    
    std::cout << isPartitioned(a) << "\n";
    std::cout << (intersection(a, b)).size();
}
