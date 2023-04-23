#include <iostream>
#include <random>
#include <ctime>


#include "../include/shapes.h"
#include "../include/shared_ptr_and_vector.h"

//6. Поиск первых отличающихся друг от друга элементов двух последовательностей по определенному критерию.
//7. Создать упорядоченную разность двух диапазонов.


void gen( stepik::vector< stepik::shared_ptr<Shape> >* arr, int n )
{
    std::mt19937 mt {std::random_device()()};

    std::uniform_int_distribution<int> rndnum(0, 255);
    std::uniform_int_distribution<int> class_type(0, 1);

    for( size_t i = 0; i < n; ++i )
    {
        switch (class_type(mt)){
        case 0:
        {
            Shape* bc = new Triangle( rndnum(mt) % 50, rndnum(mt) % 50, rndnum(mt) % 50, rndnum(mt) % 50, rndnum(mt) % 50, rndnum(mt) % 50 );
            bc->set_color(rndnum(mt),rndnum(mt),rndnum(mt));
            arr->push_back(stepik::shared_ptr<Shape>(bc));
            break;
        }
        case 1:
        {
            Shape* bp = new Parallelogram ( rndnum(mt) % 50, rndnum(mt) % 50, rndnum(mt) % 50, rndnum(mt) % 50, rndnum(mt) % 50, rndnum(mt) % 50 );
            bp->set_color(rndnum(mt),rndnum(mt),rndnum(mt));
            arr->push_back(stepik::shared_ptr<Shape>(bp));
            break;
        }
        }
    }
}


//сравнивает два элемента на соответствие заданному критерию: центр равен заданной точке
bool equal(point p, stepik::shared_ptr<Shape> elem1, stepik::shared_ptr<Shape> elem2)
{
    if ((elem1.get()->get_center() == p && elem2.get()->get_center() == p)
            || (elem1.get()->get_center() != p && elem2.get()->get_center() !=p)) return 1;
    else return 0;
}

//находит индекс первых отличающихся друг от друга элементов (одного индекса) двух последовательностей по заданному критерию
int find(point p, stepik::vector< stepik::shared_ptr<Shape> > arr1, stepik::vector< stepik::shared_ptr<Shape> > arr2)
{
    int n = arr1.size() > arr2.size() ? arr2.size() : arr1.size();
    for( int i = 0; i < n; ++i)
    {
        if (equal(p, arr1[i], arr2[i]) == 0) return i;
    }
    return -1;
}

//находит разность двух диапазонов: из первого диапазона вычитаются элементы, которые равны по критерию с элементами другого диапазона (одного индекса)
stepik::vector<stepik::shared_ptr<Shape>> difference(point p, stepik::vector< stepik::shared_ptr<Shape> > arr1, stepik::vector< stepik::shared_ptr<Shape> > arr2 )
{
    stepik::vector<stepik::shared_ptr<Shape>> buff;
    int n = arr1.size();
    for (int i = 0; i < n; ++i)
    {
        if (equal(p, arr1[i], arr2[i]) == 0) buff.push_back(arr1[i]);
    }
    return buff;
}

void print(stepik::vector< stepik::shared_ptr<Shape> > arr)
{
    for( size_t i = 0; i < arr.size(); ++i )
    {
        std::cout << *arr.at(0).get();
    }
}

int main()
{
    stepik::vector< stepik::shared_ptr<Shape> > arr1;
    gen(&arr1, 1000);
    //std::cout << "arr1: \n";
    //print(arr1);
    stepik::vector< stepik::shared_ptr<Shape> > arr2;
    gen(&arr2, 1000);
   // std::cout << "arr2: \n";
  //  print(arr2);

    std::cout << "Enter the center: \n";
    double x;
    double y;
    std::cin >> x >> y;
    point p;
    p.x = x;
    p.y = y;

    int index;
    if( (index = find(p, arr1, arr2)) != -1 ) {
        std:: cout << "found: ";
        std::cout << *arr1[index].get() << " --- " << *arr2[index].get() << '\n';
        std::cout << "index = " << index;
    }
    else
        std::cout << "Not found" << '\n';

    stepik::vector< stepik::shared_ptr<Shape> > res = difference(p, arr1, arr2);
    if (res.empty()) std::cout << "difference = 0";
    else {std:: cout << "difference:\n";
    print (res);}
    return 0;
}
