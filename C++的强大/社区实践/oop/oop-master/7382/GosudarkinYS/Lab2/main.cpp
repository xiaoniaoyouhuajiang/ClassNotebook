#include <iostream>
#include <list>

#include "shape.h"

void ShapeHandler(std::list<Shape>& list);

int main()
{
    Circle example(Coord(1, 1), 3);
    example.SetColor(RGB(14, 68, 145));
    example.Rotate(PI, Coord(0,0));
    example.PrintInfo();

    Trapezium tr(Coord(-1, 2), Coord(1, 2), Coord(2, 0), Coord(-2, -1));
    tr.Rotate(PI, Coord(-2, -1));
    tr.PrintInfo();

    std::list<Shape*> mList = {&example, &tr};
    

    return 0;
}

void ShapeHandler(std::list<Shape*>& list)
{
    for(auto it = list.begin(); it != list.end(); it++)
    {
	if((*it)->GetType() == CIRCLE) 	    (*it)->Replace(Coord(-2,0));
	else if((*it)->GetType() == SECTOR)
	    (*it)->Scale(2.0);
	else if((*it)->GetType() == TRAPEZIUM)
	    (*it)->Rotate(PI,Coord(0,0));
    }
}
