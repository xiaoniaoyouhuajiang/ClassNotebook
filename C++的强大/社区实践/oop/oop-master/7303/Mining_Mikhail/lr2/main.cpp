#include "shape.h"
#include "circle.h"
#include "ellipse.h"
#include "ellipse_sector.h"

using namespace std;

int main()
{
    cout << "Creating array of base class pointers, point them on every class and rotating:\n\n";
    Shape* Circle_item = new Circle(3, {1,1});
    cout << "Circle:\n" << *(Circle_item) << endl;
    Circle_item->rotate(M_PI/2);
    Circle_item->set_color(RED);
    cout << "Rotating Circle:\n" << *(Circle_item) << endl;
    delete Circle_item;
    Shape* Ellipse_item = new Ellipse(3, 2, {2,2});
    cout << "Ellipse:\n" << *(Ellipse_item) << endl;
    Ellipse_item->move({-1, -1});
    cout << "Moving Ellipse:\n" << *(Ellipse_item) << endl;
    Ellipse_item->rotate(M_PI/2);
    cout << "Rotating Ellipse:\n" << *(Ellipse_item) << endl;
    Shape* Ellipse_sec_item = new Ellipse_Sector({5, M_PI/4}, {3, M_PI}, {5,5});
    cout << "Ellipse sector:\n" << *(Ellipse_sec_item) << endl;
    Ellipse_sec_item->rotate(M_PI/2);
    cout << "Rotating Ellipse sector:\n" << *(Ellipse_sec_item) << endl;

    return 0;
}
