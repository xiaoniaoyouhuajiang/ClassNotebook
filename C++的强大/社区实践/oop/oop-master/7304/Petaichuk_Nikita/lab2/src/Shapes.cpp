#include "Shapes.h"

//Определение методов класса Shape
Shape::Shape(RadiusVector center, Color color)
{
    this->center = center;
    this->color = color;
    id = next_id;
    next_id++;
}

Shape::~Shape()
{
    cout << "Shape destructor called" << endl;
}

void Shape::changeColor(Color color)
{
    this->color = color;
}

void Shape::changeColor(unsigned int red, unsigned int green, unsigned int blue)
{
    this->color = Color(red, green, blue);
}

Color Shape::getColor() const
{
    return color;
}

RadiusVector Shape::getCenterCoordinates() const
{
    return center;
}

unsigned int Shape::getID() const
{
    return id;
}

//-----------------------------------------------
//Определение методов класса Circle
Circle::Circle(RadiusVector center, Color color, double radius) :
  Shape(center, color)
{
    this->radius = radius;
}

Circle::Circle(const Circle &other) :
  Shape(other.center, other.color)
{
    this->radius = other.radius;
}

Circle& Circle::operator=(const Circle &other)
{
    if (this != &other)
    {
        this->center = other.center;
        this->color = other.color;
        this->radius = other.radius;
    }
    return *this;
}

Circle::~Circle()
{
    cout << "Circle destructor called" << endl;
}

void Circle::move(RadiusVector destination)
{
    center = destination;
}

void Circle::scale(double coefficient)
{
    radius *= coefficient;
}

void Circle::rotate(double angle)
{
    //Этот комментарий поворачивает круг на заданный угол. Не удаляйте его.
}

double Circle::getRadius() const
{
    return radius;
}

//-----------------------------------------------
//Определение методов класса Rombus
Rombus::Rombus(RadiusVector center, Color color, double side_size, double angle) :
  Shape(center, color)
{
    this->side_size = side_size;
    this->angle = angle;
 
    double first_diagonal = sqrt(2 * side_size * side_size * (1 - cos(angle * M_PI / 180.0)));
    double second_diagonal = sqrt(2 * side_size * side_size * (1 - cos((180 - angle) * M_PI / 180.0)));
    left_vertex = RadiusVector(center.getX() - first_diagonal / 2, center.getY());
    right_vertex = RadiusVector(center.getX() + first_diagonal / 2, center.getY());
    upper_vertex = RadiusVector(center.getX(), center.getY() + second_diagonal / 2);
    lower_vertex = RadiusVector(center.getX(), center.getY() - second_diagonal / 2);
}

Rombus::Rombus(const Rombus &other) :
  Shape(other.center, other.color),
  left_vertex(other.left_vertex),
  right_vertex(other.right_vertex),
  upper_vertex(other.upper_vertex),
  lower_vertex(other.lower_vertex),
  side_size(other.side_size),
  angle(other.angle)
{
}

Rombus& Rombus::operator=(const Rombus &other)
{
    if (this != &other)
    {
        center = other.center;
        color = other.color;
        left_vertex = other.left_vertex;
        right_vertex = other.right_vertex;
        upper_vertex = other.upper_vertex;
        lower_vertex = other.lower_vertex;
        side_size = other.side_size;
        angle = other.angle;
    }
    return *this;
}

Rombus::~Rombus()
{
    cout << "Rombus destructor called" << endl;
}

void Rombus::move(RadiusVector destination)
{
    //Вычисление вектора смещения и смещение координат вершин
    RadiusVector move_vector = destination - center;
    left_vertex += move_vector;
    right_vertex += move_vector;
    upper_vertex += move_vector;
    lower_vertex += move_vector;
    center = destination;
}

void Rombus::scale(double coefficient)
{
    //Масштабирование размеров
    side_size *= coefficient;

    //Изменение координат вершин
    RadiusVector left_vector = left_vertex - center;
    left_vector *= coefficient;
    left_vertex = center + left_vector;

    RadiusVector right_vector = right_vertex - center;
    right_vector *= coefficient;
    right_vertex = center + right_vector;

    RadiusVector upper_vector = upper_vertex - center;
    upper_vector *= coefficient;
    upper_vertex = center + upper_vector;

    RadiusVector lower_vector = lower_vertex - center;
    lower_vector *= coefficient;
    lower_vertex = center + lower_vector;
}

void Rombus::rotate(double angle)
{
    //Нормализация угла
    if (angle >= 360)
        while (angle >= 360)
            angle -= 360;
    else if (angle < 0)
        while (angle < 0)
            angle += 360;
    
    //Смещение фигуры в начало координат
    left_vertex -= center;
    right_vertex -= center;
    upper_vertex -= center;
    lower_vertex -= center;

    //Поворот фигуры с помощью матрицы поворота
    double new_x, new_y;
    new_x = left_vertex.getX()*cos(angle * M_PI / 180.0) - left_vertex.getY()*sin(angle * M_PI / 180.0);
    new_y = left_vertex.getX()*sin(angle * M_PI / 180.0) + left_vertex.getY()*cos(angle * M_PI / 180.0);
    left_vertex.setX(new_x);
    left_vertex.setY(new_y);
    new_x = right_vertex.getX()*cos(angle * M_PI / 180.0) - right_vertex.getY()*sin(angle * M_PI / 180.0);
    new_y = right_vertex.getX()*sin(angle * M_PI / 180.0) + right_vertex.getY()*cos(angle * M_PI / 180.0);
    right_vertex.setX(new_x);
    right_vertex.setY(new_y);
    new_x = upper_vertex.getX()*cos(angle * M_PI / 180.0) - upper_vertex.getY()*sin(angle * M_PI / 180.0);
    new_y = upper_vertex.getX()*sin(angle * M_PI / 180.0) + upper_vertex.getY()*cos(angle * M_PI / 180.0);
    upper_vertex.setX(new_x);
    upper_vertex.setY(new_y);
    new_x = lower_vertex.getX()*cos(angle * M_PI / 180.0) - lower_vertex.getY()*sin(angle * M_PI / 180.0);
    new_y = lower_vertex.getX()*sin(angle * M_PI / 180.0) + lower_vertex.getY()*cos(angle * M_PI / 180.0);
    lower_vertex.setX(new_x);
    lower_vertex.setY(new_y);

    //Возврат на прежнюю позицию
    left_vertex += center;
    right_vertex += center;
    upper_vertex += center;
    lower_vertex += center;
}

void Rombus::printVertexCoordinates()
{
    cout << "Vertexes:" << endl;
    cout << "    -) Left: (" << left_vertex.getX() << ", " << left_vertex.getY() << ")" << endl;
    cout << "    -) Right: (" << right_vertex.getX() << ", " << right_vertex.getY() << ")" << endl;
    cout << "    -) Upper: (" << upper_vertex.getX() << ", " << upper_vertex.getY() << ")" << endl;
    cout << "    -) Lower: (" << lower_vertex.getX() << ", " << lower_vertex.getY() << ")" << endl;
}

double Rombus::getSideSize() const
{
    return side_size;
}

double Rombus::getAngle() const
{
    return angle;
}

//-----------------------------------------------
//Определение методов класса Trapezium
Trapezium::Trapezium(RadiusVector upper_base_center, RadiusVector lower_base_center, Color color,
                     double upper_base_size, double lower_base_size) :
  Shape(RadiusVector((upper_base_center.getX() + lower_base_center.getX()) / 2,
                     (upper_base_center.getY() + lower_base_center.getY()) / 2), color)
{
    this->upper_base_size = upper_base_size;
    this->lower_base_size = lower_base_size;

    height = upper_base_center.getY() - lower_base_center.getY();
    left_upper_vertex = upper_base_center - RadiusVector(upper_base_size / 2, 0);
    right_upper_vertex = upper_base_center + RadiusVector(upper_base_size / 2, 0);
    left_lower_vertex = lower_base_center - RadiusVector(lower_base_size / 2, 0);
    right_lower_vertex = lower_base_center + RadiusVector(lower_base_size / 2, 0);
}

Trapezium::Trapezium(const Trapezium &other) : 
  Shape(other.center, other.color),
  left_upper_vertex(other.left_upper_vertex),
  right_upper_vertex(other.right_upper_vertex),
  left_lower_vertex(other.left_lower_vertex),
  right_lower_vertex(other.right_lower_vertex),
  upper_base_size(other.upper_base_size),
  lower_base_size(other.lower_base_size),
  height(other.height)
{
}

Trapezium& Trapezium::operator=(const Trapezium &other)
{
    if (this != &other)
    {
        center = other.center;
        color = other.color;
        left_upper_vertex = other.left_upper_vertex;
        right_upper_vertex = other.right_upper_vertex;
        left_lower_vertex = other.left_lower_vertex;
        right_lower_vertex = other.right_lower_vertex;
        upper_base_size = other.upper_base_size;
        lower_base_size = other.lower_base_size;
        height = other.height;
    }
    return *this;
}

Trapezium::~Trapezium()
{
    cout << "Trapezium destructor called" << endl;
}

void Trapezium::move(RadiusVector destination)
{
    //Вычисление вектора смещения и смещение координат вершин
    RadiusVector move_vector = destination - center;
    left_upper_vertex += move_vector;
    right_upper_vertex += move_vector;
    left_lower_vertex += move_vector;
    right_lower_vertex += move_vector;
    center = destination;
}

void Trapezium::scale(double coefficient)
{
    //Масштабирование размеров
    upper_base_size *= coefficient;
    lower_base_size *= coefficient;
    height *= coefficient;

    //Изменение координат вершин
    RadiusVector left_upper_vector = left_upper_vertex - center;
    left_upper_vector *= coefficient;
    left_upper_vertex = center + left_upper_vector;

    RadiusVector right_upper_vector = right_upper_vertex - center;
    right_upper_vector *= coefficient;
    right_upper_vertex = center + right_upper_vector;

    RadiusVector left_lower_vector = left_lower_vertex - center;
    left_lower_vector *= coefficient;
    left_lower_vertex = center + left_lower_vector;

    RadiusVector right_lower_vector = right_lower_vertex - center;
    right_lower_vector *= coefficient;
    right_lower_vertex = center + right_lower_vector;
}

void Trapezium::rotate(double angle)
{
    //Нормализация угла
    if (angle >= 360)
        while (angle >= 360)
            angle -= 360;
    else if (angle < 0)
        while (angle < 0)
            angle += 360;
    
    //Смещение фигуры в начало координат
    left_upper_vertex -= center;
    right_upper_vertex -= center;
    left_lower_vertex -= center;
    right_lower_vertex -= center;

    //Поворот фигуры с помощью матрицы поворота
    double new_x, new_y;
    new_x = left_upper_vertex.getX()*cos(angle * M_PI / 180.0) - left_upper_vertex.getY()*sin(angle * M_PI / 180.0);
    new_y = left_upper_vertex.getX()*sin(angle * M_PI / 180.0) + left_upper_vertex.getY()*cos(angle * M_PI / 180.0);
    left_upper_vertex.setX(new_x);
    left_upper_vertex.setY(new_y);
    new_x = right_upper_vertex.getX()*cos(angle * M_PI / 180.0) - right_upper_vertex.getY()*sin(angle * M_PI / 180.0);
    new_y = right_upper_vertex.getX()*sin(angle * M_PI / 180.0) + right_upper_vertex.getY()*cos(angle * M_PI / 180.0);
    right_upper_vertex.setX(new_x);
    right_upper_vertex.setY(new_y);
    new_x = left_lower_vertex.getX()*cos(angle * M_PI / 180.0) - left_lower_vertex.getY()*sin(angle * M_PI / 180.0);
    new_y = left_lower_vertex.getX()*sin(angle * M_PI / 180.0) + left_lower_vertex.getY()*cos(angle * M_PI / 180.0);
    left_lower_vertex.setX(new_x);
    left_lower_vertex.setY(new_y);
    new_x = right_lower_vertex.getX()*cos(angle * M_PI / 180.0) - right_lower_vertex.getY()*sin(angle * M_PI / 180.0);
    new_y = right_lower_vertex.getX()*sin(angle * M_PI / 180.0) + right_lower_vertex.getY()*cos(angle * M_PI / 180.0);
    right_lower_vertex.setX(new_x);
    right_lower_vertex.setY(new_y);

    //Возврат на прежнюю позицию
    left_upper_vertex += center;
    right_upper_vertex += center;
    left_lower_vertex += center;
    right_lower_vertex += center;
}

void Trapezium::printVertexCoordinates()
{
    cout << "Vertexes:" << endl;
    cout << "    -) Left upper: (" << left_upper_vertex.getX() << ", " << left_upper_vertex.getY() << ")" << endl;
    cout << "    -) Right upper: (" << right_upper_vertex.getX() << ", " << right_upper_vertex.getY() << ")" << endl;
    cout << "    -) Left lower: (" << left_lower_vertex.getX() << ", " << left_lower_vertex.getY() << ")" << endl;
    cout << "    -) Right lower: (" << right_lower_vertex.getX() << ", " << right_lower_vertex.getY() << ")" << endl;
}

double Trapezium::getUpperBaseSize() const
{
    return upper_base_size;
}
    
double Trapezium::getLowerBaseSize() const
{
    return lower_base_size;
}

double Trapezium::getHeight() const
{
    return height;
}

//-----------------------------------------------
//Определение перегруженных операторов <<
ostream& operator<<(ostream &os, const Circle &circle)
{
    os << "ID: " << circle.id << endl
    << "Type: Circle" << endl
    << "Center: " << circle_center << endl
    << circle.color
    << "Size parameters:" << endl
    << "    -) Radius: " << circle.radius << endl;
    return os;
}

ostream& operator<<(ostream &os, const Rombus &rombus)
{
    os << "ID: " << rombus.id << endl
    << "Type: Rombus" << endl
    << "Center: " << rombus_center << endl
    << rombus.color
    << "Size parameters:" << endl
    << "    -) Side: " << rombus.side_size << endl
    << "    -) Angle: " << rombus.angle << endl;
    return os;
}

ostream& operator<<(ostream &os, const Trapezium &trapezium)
{
    os << "ID: " << trapezium.id << endl
    << "Type: Trapezium" << endl
    << "Center: " << trapezium_center << endl
    << trapezium.color
    << "Size parameters:" << endl
    << "    -) Upper base: " << trapezium.upper_base_size << endl
    << "    -) Lower base: " << trapezium.lower_base_size << endl
    << "    -) Height: " << trapezium.height << endl;
    return os;
}
