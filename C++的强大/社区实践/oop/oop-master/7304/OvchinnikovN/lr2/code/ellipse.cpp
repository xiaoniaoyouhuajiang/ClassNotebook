#include "ellipse.h"

Ellipse::Ellipse(rgb color, double x, double y, double height, double width) : Shape(color)
{
    this->height = height;
    this->width = width;
    setMainCenter(x, y);
    double c = sqrt(width>height ? width*width/4 - height*height/4 : height*height/4 - width*width/4);
    f1.setY(height/2);
    f1.setX(x - c);
    f2.setY(height/2);
    f2.setX(x + c);
}

void Ellipse::show()
{
    QGraphicsScene *scene = new QGraphicsScene;
    scene->setSceneRect(-500, -500, 1000, 1000);

    rgb clr = getShapeColor();
    QColor color(clr.getRed(), clr.getGreen(), clr.getBlue());
    QPen pen;
    pen.setColor(color);
    pen.setWidth(3);

    Point centralPoint = getMainCenter();
    scene->addEllipse(centralPoint.getX() - width/2, centralPoint.getY() - height/2, width, height, pen);

    QGraphicsView *view = new QGraphicsView;
    view->setScene(scene);
    view->show();
}

void Ellipse::move(double x, double y)
{
    Point firstCenter = getMainCenter();
    Point diff(x - firstCenter.getX(), y - firstCenter.getY());
    f1.setX(f1.getX() + diff.getX());
    f1.setY(f1.getY() + diff.getY());
    f2.setX(f2.getX() + diff.getX());
    f2.setY(f2.getY() + diff.getY());
    setMainCenter(x,y);
    show();
}

void Ellipse::turn(double deg)
{
    f1.setY((f1.getY() - f1.getX()*sin(deg*PI/180)/cos(deg*PI/180)) / (sin(deg*PI/180)*sin(deg*PI/180)/cos(deg*PI/180)+cos(deg*PI/180)));
    f1.setX((f1.getX() + f1.getY()*sin(deg*PI/180)) / cos(deg*PI/180));
    f2.setY((f2.getY() - f2.getX()*sin(deg*PI/180)/cos(deg*PI/180)) / (sin(deg*PI/180)*sin(deg*PI/180)/cos(deg*PI/180)+cos(deg*PI/180)));
    f2.setX((f2.getX() + f2.getY()*sin(deg*PI/180)) / cos(deg*PI/180));

    QGraphicsScene *scene = new QGraphicsScene;
    scene->setSceneRect(-500, -500, 1000, 1000);

    rgb clr = getShapeColor();
    QColor color(clr.getRed(), clr.getGreen(), clr.getBlue());
    QPen pen;
    pen.setColor(color);
    pen.setWidth(3);

    Point cet = getMainCenter();
    scene->addEllipse(cet.getX(), cet.getY(), width, height, pen);

    QGraphicsView *view = new QGraphicsView;
    view->setScene(scene);
    view->rotate(360-deg);
    view->show();
}

void Ellipse::scale(double coeff)
{
    height *= coeff;
    width *= coeff;
    Point centr = getMainCenter();
    double c = sqrt(width>height ? width*width/4 - height*height/4 : height*height/4 - width*width/4);
    f1.setY(height/2);
    f1.setX(centr.getX() - c);
    f2.setY(height/2);
    f2.setX(centr.getX() + c);
    show();
}

std::ostream& Ellipse::printShape(std::ostream &out, Shape &shape)
{
    rgb clr = shape.getShapeColor();
    out << "Ellipse: width = " << width << ", height = " << height << ", focus1(" << f1.getX() << ", " << f1.getY() << "), focus2(" << f2.getX() << ", " << f2.getY() << ")\n";
    out << "         Center of shape: (" << center.getX() << ", " << center.getY() << ")\n";
    out << "         ID: " << shape.getId() << " Color: (" << clr.getRed() << ", " << clr.getGreen() << ", " << clr.getBlue() << ")\n";
    return out;
}

Ellipse::Ellipse(const Ellipse &other) : Ellipse()
{
    height = other.height;
    width = other.width;
    f1 = other.f1;
    f2 = other.f2;
    center = other.center;
    color = other.color;
    id = count;
}

Ellipse Ellipse::operator +(double value)
{
    Ellipse tmp = *this;
    tmp.f1 = this->f1 + value;
    tmp.f2 = this->f2 + value;
    tmp.center = this->center + value;
    return tmp;
}
