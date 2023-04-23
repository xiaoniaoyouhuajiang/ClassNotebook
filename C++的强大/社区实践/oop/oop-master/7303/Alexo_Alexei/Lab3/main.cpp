#include <QCoreApplication>
#include <iostream>
#include "color.h"
#include "ellipse.h"
#include "point.h"
#include "regularpentagon.h"
#include "shape.h"
#include "square.h"
#include "vector.h"
#include "list.h"
#include "vector_dek.h"

void Change(stepik::list<Shape*> &shapes) {
    for(auto iter = shapes.begin(); iter != shapes.end(); iter++) {
        (*iter)->Scale(15);
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Square square(Color(255, 10, 144), Point(50,50), 15);
    Ellipse ellipse(Color(255, 10, 144), Point(50,50), 15, 20);
    RegularPentagon regularrentagon(Color(255, 10, 144), Point(50,50), 15);
    Square square_(Color(255, 10, 144), Point(50,50), 15);

    stepik::vector<double> vector1;
    vector1.push_back(2.5);
    vector1.push_back(5);
    vector1.push_back(3);
    vector1.push_back(4);
    vector1.push_back(6);

    stepik::vector<double> vector2;
    vector2.push_back(3);
    vector2.push_back(5);
    vector2.push_back(3);
    vector2.push_back(4);
    vector2.push_back(8);

    stepik::vector_dek<double> vector3(vector1.size());

    vector3.Dekart(vector1, vector2);

    std::cout << "Vector3: " << endl;
    for(int i = 0, s = vector3.size(); i < s; i++)
      std::cout << vector3[i] << " ";
        cout << endl;

    for(int i = 0, s = vector1.size(); i < s; i++)
      std::cout << vector1[i] << " ";
        cout << endl;

    for(int i = 0, s = vector2.size(); i < s; i++)
        std::cout << vector2[i] << " ";
          cout << endl;    
// /////////////////////////////////////////////////
    stepik::list<Shape*> myList;
    myList.push_back(&square);
    myList.push_back(&ellipse);
    myList.push_back(&regularrentagon);

    for(auto iter = myList.begin(); iter != myList.end(); iter++) {
       (*iter)->Print();
        std::cout << endl;
    }

    Change(myList);

    for(auto iter = myList.begin(); iter != myList.end(); iter++) {
       (*(*iter)).Print();
        std::cout << endl;
    }

    /*for(auto iter = myList.begin(); iter != myList.end(); iter++) {
        Square* square = dynamic_cast<Square*>(*iter);
        Ellipse* ellipse = dynamic_cast<Ellipse*>(*iter);
        RegularPentagon* rP = dynamic_cast<RegularPentagon*>(*iter);

        if (square)
            std::cout << *square << endl;

        if (ellipse)
            std::cout << *ellipse << endl;

        if (rP)
            std::cout << *rP << endl;
    }*/

    /*stepik::vector<int> vector4;
    vector4.push_back(0);
    vector4.push_back(1);
    vector4[0] = vector1[0];
    vector4[1] = vector1[1];
    for(int i = 0, s = vector4.size(); i < s; i++)
      std::cout << vector4[i] << endl;*/

//    vector<Shape*> = {square, ellipse};

    //vector<Shape*> vect;
    //vect.push_back(&square);
    //vect.push_back(&ellipse);

    /*for(int i = 0, s = vect.size(); i < s; i++) {
        Square* square = dynamic_cast<Square*>(vect[i]);
        Ellipse* ellipse = d for(auto iter = myList.begin(); iter != myList.end(); iter++) {
       std::cout << (*(*iter)) << endl;
    }ynamic_cast<Ellipse*>(vect[i]);
        RegularPentagon* rP  myList.push_back(&square);
    myList.push_back(&ellipse);= dynamic_cast<RegularPentagon*>(vect[i]);

        if (square)
            std::cout << *square << endl;

        if (ellipse)
            std::cout << *ellipse << endl;

        if (rP)
            std::cout << *rP << endl;
    }*/

    //cout << square << endl;
    /*square * 0.5;
    cout << square << endl;
    square + -5;
    cout << square << endl;
    square * 1;
    cout << square << endl;
    square * 3;
    cout << square << endl;

    square.Scale(0.5);
    cout << square << endl;
    square.Move(Point(100, 100));
    cout << square << endl;*/

    //cout << ellipse << endl;
    /*ellipse * 2;
    cout << ellipse << endl;
    ellipse.Scale(0.5);
    cout << ellipse << endl;
    ellipse + 15;
    cout << ellipse << endl;*/

    /*cout << regularrentagon << endl;
    regularrentagon * 2;
    cout << regularrentagon << endl;
    regularrentagon * 1;
    cout << regularrentagon << endl;
    regularrentagon * 3;
    cout << regularrentagon << endl;
    regularrentagon + 10;
    cout << regularrentagon << endl;
    regularrentagon.Scale(0.5);
    cout << regularrentagon << endl;
    regularrentagon.Move(Point(100, 100));
    cout << regularrentagon << endl;

    cout << square_ << endl;*/

    cout << "END!" << endl;

    return a.exec();
}
