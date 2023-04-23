#include "Shapes.h"

unsigned int Shape::next_id = 0;

int main()
{
    Shape *first_shape = new Circle(RadiusVector(10.0, 10.0), Color(255, 255, 255), 10.0);
    Shape *second_shape = new Rombus(RadiusVector(), Color(), 9.0, 60.0);
    Shape *third_shape = new Trapezium(RadiusVector(-10.0, -10.0), RadiusVector(-10.0, -20.0), Color(0, 0, 255), 15.0, 25.0);

    cout << "BEFORE CHANGING:" << endl;
    cout << "------------------------------------" << endl; 
    cout << *((Circle *) first_shape);
    cout << *((Rombus *) second_shape);
    ((Rombus *) second_shape)->printVertexCoordinates();
    cout << *((Trapezium *) third_shape);
    ((Trapezium *) third_shape)->printVertexCoordinates();
    cout << "------------------------------------" << endl << endl;

    first_shape->changeColor(Color(127, 127, 127));
    first_shape->move(RadiusVector(0.0, 0.0));
    first_shape->scale(10.0);
    first_shape->rotate(77.7);

    second_shape->changeColor(100, 200, 50);
    second_shape->move(RadiusVector(50, -90));
    second_shape->scale((double) 1 / 3);
    second_shape->rotate(90.0);

    third_shape->changeColor(Color(255, 255, 0));
    third_shape->move(RadiusVector(-15, 40));
    third_shape->scale(0.2);
    third_shape->rotate(180.0);

    cout << "AFTER CHANGING:" << endl;
    cout << "------------------------------------" << endl; 
    cout << *((Circle *) first_shape);
    cout << *((Rombus *) second_shape);
    ((Rombus *) second_shape)->printVertexCoordinates();
    cout << *((Trapezium *) third_shape);
    ((Trapezium *) third_shape)->printVertexCoordinates();
    cout << "------------------------------------" << endl << endl;

    delete first_shape;
    delete second_shape;
    delete third_shape;
    return 0;
}
