#include "rectangle.h"
#include "ellipse.h"
#include "sectorellipse.h"

int main()
{
    Rectangle test1({-1.0, -2.0}, {5.0, 2.0});
    cout << test1;
    test1.Turn(M_PI/2);
    test1.toScale(2);
    test1.Moving({0.0, 0.0});
    cout << test1;

    Ellipse test2({-3.3, 0.0}, {3.3, 0.0}, 15.5);
    cout << test2;
    test2.Turn(M_PI/2);
    test2.Turn(M_PI/2);
    test2.toScale(3.0);
    test2.toScale(1.0/3.0);
    test2.Moving({4.0, 4.0});
    cout << test2;

    SectorEllipse test3({0.0, 4.2}, {0.0, -4.2}, 10.95, 0.52, 1.4);
    cout << test3;
    test3.getColor();
    test3.setColor({255, 0, 0});
    test3.getColor();

    Rectangle a({-1.0, -2.0}, {5.0, 2.0});
    cout << a;
    Ellipse b({-3.3, 0.0}, {3.3, 0.0}, 15.5);
    cout << b;
    SectorEllipse c({0.0, 4.2}, {0.0, -4.2}, 10.95, 0.52, 1.4);
    cout << c;

    cout << test1;

    return 0;
}
