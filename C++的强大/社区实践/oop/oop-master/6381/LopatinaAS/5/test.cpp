#include "Circle.h"
#include "Rectangle.h"
#include "Trapezoid.h"
#include "Shape.h"
#include "vector.h"
#include "shared_ptr.h"
#include "func.h"
#include <ostream>
#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>
using namespace stepik;

int main() {

	stepik::vector <string> colors {"red", "blue", "white", "yellow", "green", "black", "purple", "pink", "grey", "orange"};
	
	stepik::vector<shared_ptr<Shape>> sh_test (5);
    srand(time(nullptr));
    for (int i = 0; i < 5; i++){
        int a = rand() % 3;
        if(a == 0)
            sh_test[i]=shared_ptr<Shape>(new Circle(5, new Dot(10, 10), colors[rand()%10]));
        else if (a==1)
            sh_test[i]=shared_ptr<Shape>(new Rectangle(1, 1, 5, 5, colors[rand()%10]));
        else
            sh_test[i]=shared_ptr<Shape>(new Trapezoid(2, 4, 1, 1, 2, 4, colors[rand()%10]));
    }

     std::cout <<  "Initial shapes: " << std::endl;
     output(sh_test);

    std::cout << "We order the first 5 shapes"<< std::endl;
    sequencing(sh_test, 5);
    output(sh_test);

    std::cout << "Are the sums of the perimeters of figures 1 to 3 and 4 to 5 equal?"<< std::endl;
    if (sum_prm (sh_test, 0, 2, 3, 4))
        std::cout << "Answer: yes";
    else std::cout << "Answer: no";

}