#include "triangle.h"

Triangle::Triangle(rgb color, double x1, double y1, double x2, double y2, double x3, double y3) : Shape(color)
{
    one.setPoint(x1,y1);
    two.setPoint(x2,y2);
    three.setPoint(x3,y3);
    setCenter();
}

void Triangle::setCenter(){
    double x12 = (one.getX() + two.getX())/2;
    double y12 = (one.getY() + two.getY())/2;
    double x13 = (one.getX()+three.getX())/2;
    double y13 = (one.getY()+three.getY())/2;
    double expression1 = y12*(three.getX()-x12)/(three.getY()-y12)/(two.getX()-x13) - x12/(two.getX()-x13) + x13/(two.getX()-x13) - y13/(two.getY()-y13);
    double expression2 = (three.getX()-x12)/(three.getY()-y12)/(two.getX()-x13) - 1/(two.getY()-y13);
    double y = expression1/expression2;
    double x = (y-y12)*(three.getX()-x12)/(three.getY()-y12) + x12;
    setMainCenter(x,y);
}

void Triangle::show()
{
    QGraphicsScene *scene = new QGraphicsScene;
    scene->setSceneRect(-500, -500, 1000, 1000);
    scene->addLine(0,-500,0,500);
    scene->addLine(-500,0,500,0);

    rgb clr = getShapeColor();
    QColor color(clr.getRed(), clr.getGreen(), clr.getBlue());
    QPen pen;
    pen.setColor(color);
    pen.setWidth(3);

    scene->addLine(one.getX(), one.getY(), two.getX(), two.getY(), pen);
    scene->addLine(two.getX(), two.getY(), three.getX(), three.getY(), pen);
    scene->addLine(three.getX(), three.getY(), one.getX(), one.getY(), pen);

    QGraphicsView *view = new QGraphicsView;
    view->setScene(scene);
    view->show();
}

void Triangle::move(double x, double y)
{
    Point firstCenter = getMainCenter();
    Point diff(x - firstCenter.getX(), y - firstCenter.getY());
    one.setX(one.getX() + diff.getX());
    one.setY(one.getY() + diff.getY());
    two.setX(two.getX() + diff.getX());
    two.setY(two.getY() + diff.getY());
    three.setX(three.getX() + diff.getX());
    three.setY(three.getY() + diff.getY());
    setMainCenter(x, y);
}

void Triangle::turn(double deg)
{
    Point firstCenter = getMainCenter();
    one.setY((one.getY() - one.getX()*sin(deg*PI/180)/cos(deg*PI/180)) / (sin(deg*PI/180)*sin(deg*PI/180)/cos(deg*PI/180)+cos(deg*PI/180)));
    one.setX((one.getX() + one.getY()*sin(deg*PI/180)) / cos(deg*PI/180));
    two.setY((two.getY() - two.getX()*sin(deg*PI/180)/cos(deg*PI/180)) / (sin(deg*PI/180)*sin(deg*PI/180)/cos(deg*PI/180)+cos(deg*PI/180)));
    two.setX((two.getX() + two.getY()*sin(deg*PI/180)) / cos(deg*PI/180));
    three.setY((three.getY() - three.getX()*sin(deg*PI/180)/cos(deg*PI/180)) / (sin(deg*PI/180)*sin(deg*PI/180)/cos(deg*PI/180)+cos(deg*PI/180)));
    three.setX((three.getX() + three.getY()*sin(deg*PI/180)) / cos(deg*PI/180));
    setCenter();
    move(firstCenter.getX(), firstCenter.getY());
}

void Triangle::scale(double coeff)
{
    Point firstCenter = getMainCenter();
    Point sizeOneTwo(two.getX() - one.getX(), two.getY() - one.getY());
    Point sizeOneThree(three.getX() - one.getX(), three.getY() - one.getY());
    sizeOneTwo.setPoint(coeff * sizeOneTwo.getX(), coeff * sizeOneTwo.getY());
    sizeOneThree.setPoint(coeff * sizeOneThree.getX(), coeff * sizeOneThree.getY());
    two.setX(one.getX() + sizeOneTwo.getX());
    two.setY(one.getY() + sizeOneTwo.getY());
    three.setX(one.getX() + sizeOneThree.getX());
    three.setY(one.getY() + sizeOneThree.getY());

    setCenter();
    move(firstCenter.getX(), firstCenter.getY());
}

std::ostream& Triangle::printShape(std::ostream &out, Shape &shape)
{
    rgb clr = shape.getShapeColor();
    out << "Triangle: (" << one.getX() << ", " << one.getY() << ") (" << two.getX() << ", " << two.getY() << ") (" << three.getX() << ", " << three.getY() << ")\n";
    out << "          Center of shape: (" << center.getX() << ", " << center.getY() << ")\n";
    out << "          ID: " << shape.getId() << " Color: (" << clr.getRed() << ", " << clr.getGreen() << ", " << clr.getBlue() << ")\n";
    return out;
}

Triangle::Triangle(const Triangle &other) : Shape()
{
    one = other.one;
    two = other.two;
    three = other.three;
    center = other.center;
    color = other.color;
    id = count;
}

Triangle Triangle::operator +(const Triangle& other)
{
    Triangle tmp;
    tmp.one = this->one + other.one;
    tmp.two = this->two + other.two;
    tmp.three = this->three + other.three;
    tmp.setCenter();
    tmp.color.setColor((this->color.getRed()+other.color.getRed())/2, (this->color.getGreen()+other.color.getGreen())/2, (this->color.getBlue()+other.color.getBlue())/2);
    return tmp;
}

Triangle Triangle::operator +(double value)
{
    Triangle tmp = *this;
    tmp.one = tmp.one + value;
    tmp.two = tmp.two + value;
    tmp.three = tmp.three + value;
    tmp.setCenter();
    return tmp;
}
