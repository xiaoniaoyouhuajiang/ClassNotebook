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
#define N 1000 
using namespace stepik;

int main() {

	stepik::vector <string> colors {"red", "blue", "white", "yellow", "green", "black", "purple", "pink", "grey", "orange"};
	
	stepik::vector<shared_ptr<Shape>> test (N);
    srand(time(nullptr));
    for (int i = 0; i < 1000; i++){
        int a = rand() % 3;
        if(a == 0)
            test[i]=shared_ptr<Shape>(new Circle(rand()%10+1, new Dot(rand()%10, rand()%10), colors[rand()%10]));
        else if (a==1)
            test[i]=shared_ptr<Shape>(new Rectangle(rand()%10, rand()%10,rand()%10+1, rand()%10+1, colors[rand()%10]));
        else
            test[i]=shared_ptr<Shape>(new Trapezoid(rand()%5, rand()%5, rand()%9+6, rand()%9+6, rand()%5+1, rand()%10+6,  colors[rand()%10]));
    }

	sequencing (test, 500);
	std:: cout << "The first 500 elements are ordered" << std::endl; 
	std::cout << "Are the sums of the perimeters of figures 100 to 200 and 300 to 350 equal?"<< std::endl;
    if (sum_prm (test, 100, 200, 300, 350))
        std::cout << "Answer:  yes";
    else std::cout << "Answer:  no";
}