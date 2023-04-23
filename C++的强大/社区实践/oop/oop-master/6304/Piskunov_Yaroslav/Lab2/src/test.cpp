#include "shape.hpp"

int main()
{
    eclipse a(0, 0, 4, 10);
    NOtrap b(0, 0, 4, 10, 6);
    trap c(0, 0, 4, 10, 6, 3);
    shape* figures[3] = {&a, &b, &c};

    for (int i=0; i<3; i++)
    {
        figures[i]->printBoth();

        figures[i]->changePosition(3, 3);
        figures[i]->setColor(0xC0C0C0);
        figures[i]->printBoth();

        figures[i]->zoom(2);
        figures[i]->printBoth();

        figures[i]->setRotateValue(M_PI/2);
        figures[i]->printBoth();
        cout << endl << endl << endl;
    }
    return 0;
}


