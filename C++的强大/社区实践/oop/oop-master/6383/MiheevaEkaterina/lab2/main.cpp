#include <iostream>
//#include "Shape.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "Square.h"
//#include "Ellipse.h"
//#include "Rectangle.h"
//#include "Square.h"

using namespace std;

int main()
{
    Colour colour(1,2,4);
    Point p(1.0,2.3),
    p1(3,4);
    //Shape(colour);
    Ellipse el(colour,3,p,2,3);
    cout<<el;
    try {
       Rectangle rectangle(colour,2,3);
        cout<<rectangle;
    }
    catch (char * msg){
        cout<<msg<<endl;
    }
    try{
        Square square(colour);
        cout<<square;
    }
    catch (char *msg){
        cout<<msg<<endl;
    }
    return 0;
}

