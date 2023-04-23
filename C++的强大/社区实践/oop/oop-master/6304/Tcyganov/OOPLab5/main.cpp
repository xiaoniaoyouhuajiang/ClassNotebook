#include <iostream>
//#include <algorithm>
#include <vector>
#include <memory>
#include <ctime>
#include "Pentagon.h"
#include "Line.h"
#include "Ellipse.h"
#include "shared_ptr.h"
#include "vector.h"

Point GetRandomPoint(){
    Point p;
    p.x = rand() / (float)RAND_MAX * 1000;
    p.y = rand() / (float)RAND_MAX * 1000;
    return p;
}

bool isNoOne(stepik::vector<stepik::shared_ptr<Shape>> shapes, float perimeter)
{
    for (size_t i = 0; i < shapes.size(); i++)
    {
        if (shapes[i]->Perimeter() > perimeter)
            return 1;
    }
    return 0;
}


 void Copy(stepik::vector<stepik::shared_ptr<Shape>> & shapes, float perimeter) {
     size_t i = 0; size_t k = 0;
     while (i < shapes.size()) {
         if (shapes[i]->Perimeter() > perimeter) {
             shapes.erase(&shapes[i]);
             std::cout << i + k << " deleted" << std::endl;
             k++;
         }
         else
             i++;
     }
 }

 void out(stepik::vector<stepik::shared_ptr<Shape>> shapes){
     for (size_t i = 0; i < shapes.size(); i++)
     {
         cout << shapes[i]->Perimeter() << " ";
     }
     cout << endl;
 }

int main()
{
    srand(time(0));
    stepik::vector<stepik::shared_ptr<Shape>> shapes;
    for (size_t i = 0; i < 1000; i++)
    {
        stepik::shared_ptr<Shape> shape;
        switch (rand() % 3)
        {
        case 0:
            shape = stepik::shared_ptr<Shape>(
                new Line(GetRandomPoint(), GetRandomPoint())
            );
            shapes.push_back(stepik::shared_ptr<Shape>(shape));
            break;
        case 1:
            shape = stepik::shared_ptr<Shape>(
                new Ellipse(GetRandomPoint(), GetRandomPoint())
            );
            shapes.push_back(stepik::shared_ptr<Shape>(shape));
            break;
        case 2:
            shape = stepik::shared_ptr<Shape>(new Pentagon(GetRandomPoint(),GetRandomPoint(),GetRandomPoint(),GetRandomPoint(),GetRandomPoint()));
            shapes.push_back(stepik::shared_ptr<Shape>(shape));
            break;
        }
    }
    cout << isNoOne(shapes, 500) << endl;
    out(shapes);
    system("PAUSE");
    Copy(shapes, 500);
    cout << isNoOne(shapes, 501) << endl;
    out(shapes);
    return 0;
};
