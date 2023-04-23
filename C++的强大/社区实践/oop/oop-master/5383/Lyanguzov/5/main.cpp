#include <iostream>
#include <algorithm>

#include "methodslab5.h"

using namespace stepik;

void printVector(vector< shared_ptr<Shape> > &container, std::string name)
{
    std::cout << "Vector #" + name + ":" << std::endl;
    for(auto it = container.begin(); it != container.end(); it++)
    {
        (*it)->print(std::cout);
    }
    std::cout << std::endl << "___________" << std::endl;

}

int main(/*int argc, char *argv[]*/)
{
    system("clear");
    vector< shared_ptr<Shape> > v1;
    vector< shared_ptr<Shape> > v2;

    Shape *e = new Ellipse(0, 0, 5, 10, 0, 1, Color(165, 90, 50));
    Shape *e2 = new Ellipse(0, 0, 10, 5, 0, 1, Color(165, 90, 90));
    Shape *r = new Round(5, 0, 10);
    Shape *a = new Arc(0, 0, -M_PI/2, M_PI/2, 10);
    Shape *r2 = new Round(-50, -50, 10, 0, 1, Color(220, 0, 0));

    Shape *r3 = new Round(30, 30, 5);


    char inputType;
    std::cout << "Choose vectors type: 0 - from code, 1 - randomGenerate" << std::endl;
    //std::cin >> inputType;
    inputType = '0';
    if(inputType == '1')
    {
        v1 = createRandomShapeVector(10);
        v2 = createRandomShapeVector(10);
    }
    else
    {
        v1.push_back(shared_ptr<Shape>(r3));
        v1.push_back(shared_ptr<Shape>(e));
        v1.push_back(shared_ptr<Shape>(r2));
        v1.push_back(shared_ptr<Shape>(e2));
        v1.push_back(shared_ptr<Shape>(r));

        v2.push_back(shared_ptr<Shape>(e));
        v2.push_back(shared_ptr<Shape>(r2));
        v1.push_back(shared_ptr<Shape>(r3));

        std::cout << std::endl << "Origin Vectors:" << std::endl;
        printVector(v1, "v1");
        printVector(v2, "v2");

        std::cout << std::endl << "___________" << std::endl << std::endl;
    }

    std::cout << std::endl << "Unmodify Algorithm:" << std::endl;
    // 1) Проверка разделен ли диапазон на две группы по заданному критерию.
    bool isSplitted = std::is_partitioned( v1.begin(), v1.end(), isIntersectWith);
    if(isSplitted)
    {
        std::cout << "Container v1 is split by stl algorithm" << std::endl;
    }
    else
    {
        std::cout << "Container v1 is not split by stl algorithm" << std::endl;
    }

    std::cout << std::endl << "Unmodify Algorithm:" << std::endl;
    // 1) Проверка разделен ли диапазон на две группы по заданному критерию.
    isSplitted = std::is_partitioned( v2.begin(), v2.end(), isIntersectWith);
    if(isSplitted)
    {
        std::cout << "Container v2 is split by stl algorithm" << std::endl;
    }
    else
    {
        std::cout << "Container v2 is not split by stl algorithm" << std::endl;
    }

    std::cout << std::endl << "Modify Algorithm:" << std::endl;
    // 2) Создать упорядоченную разность двух диапазонов.
    vector< shared_ptr<Shape> > difference = makeSortedDifference(v1, v2);
    //std::set_difference(v1.begin(), v1.begin(), v2.begin(), v2.end(), difference.begin(), cmp);
    std::cout << "Difference size = " << difference.size() << std::endl << std::endl;

    if(inputType != '1')
    {
        printVector(difference, "Sorted difference between v1 and v2");
    }

    delete e;
    delete e2;
    delete r;
    delete r2;
    delete r3;
    delete a;
    return 0;
}
