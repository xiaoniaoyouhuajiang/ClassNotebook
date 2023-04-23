#include "Trapezium.h"

Trapezium::Trapezium(std::vector<Point> &coord, Point &center) {
    for (int i = 0; coord.size() && i < coord.size(); ++i) {
        this->coord.push_back(coord[i]);
    }
    this->center.x = center.x;
    this->center.y = center.y;

    this->calculateArea();
}

void Trapezium::draw() {
    std::cout << "Info about trapezium: " << std::endl;
    for (int i = 0; i < this->coord.size(); ++i) {
        std::cout << this->coord[i].x << " : " << this->coord[i].y << std::endl;
    }
    std::cout << "center x: " << this->center.x << ", y: " << this->center.y << std::endl;
    std::cout << "area of trapezium: " << this->area << std::endl;
}

void Trapezium::moveTo() {
    this->coord.clear();
    Point temp;
    std::cout << "Input 4 coords of rectangle (x, y): " << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cin >> temp.x;
        std::cin >> temp.y;
        this->coord.push_back(temp);
    }
    std::cin >> this->center.x;
    std::cin >> this->center.y;
}

void Trapezium::rotateOn(double angle) {
    double x_help = this->center.x;
    double y_help = this->center.y;
    this->center.x = (x_help * cos(angle)) - (y_help * sin(angle));
    this->center.y = (x_help * sin(angle)) + (y_help * cos(angle));
    for (int i = 0; i < this->coord.size(); ++i) {
        x_help = this->coord[i].x;
        y_help = this->coord[i].y;
        this->coord[i].x = (x_help * cos(angle)) - (y_help * sin(angle));
        this->coord[i].y = (x_help * sin(angle)) + (y_help * cos(angle));
    }
}

void Trapezium::scaleOn(double coef) {
    for (int i = 0; i < this->coord.size(); ++i) {
        this->coord[i].x *= coef;
        this->coord[i].y *= coef;
    }
    this->center.x *= coef;
    this->center.y *= coef;
}

void Trapezium::calculateArea() {
    std::vector<double> sides;
    double semiPerimetr = 0;
    std::vector<double> x;
    std::vector<double> y;
    double a = 0, b = 0, c = 0, d = 0;

    // нахождение всех сторон
    sides.push_back(sqrt(pow(this->coord[0].x - this->coord[1].x, 2.0) +
                    pow(this->coord[0].y - this->coord[1].y, 2.0)));
    sides.push_back(sqrt(pow(this->coord[0].x - this->coord[2].x, 2.0) +
                    pow(this->coord[0].y - this->coord[2].y, 2.0)));
    sides.push_back(sqrt(pow(this->coord[0].x - this->coord[3].x, 2.0) +
                    pow(this->coord[0].y - this->coord[3].y, 2.0)));

    sides.push_back(sqrt(pow(this->coord[1].x - this->coord[2].x, 2.0) +
                    pow(this->coord[1].y - this->coord[2].y, 2.0)));
    sides.push_back(sqrt(pow(this->coord[1].x - this->coord[3].x, 2.0) +
                    pow(this->coord[1].y - this->coord[3].y, 2.0)));

    sides.push_back(sqrt(pow(this->coord[2].x - this->coord[3].x, 2.0) +
                    pow(this->coord[2].y - this->coord[3].y, 2.0)));

    // находим разность иксов для каждой стороны
    x.push_back(abs(this->coord[0].x - this->coord[1].x));
    x.push_back(abs(this->coord[0].x - this->coord[2].x));
    x.push_back(abs(this->coord[0].x - this->coord[3].x));

    x.push_back(abs(this->coord[1].x - this->coord[2].x));
    x.push_back(abs(this->coord[1].x - this->coord[3].x));

    x.push_back(abs(this->coord[2].x - this->coord[3].x));

    // находим разность игриков для каждой стороны
    y.push_back(abs(this->coord[0].y - this->coord[1].y));
    y.push_back(abs(this->coord[0].y - this->coord[2].y));
    y.push_back(abs(this->coord[0].y - this->coord[3].y));

    y.push_back(abs(this->coord[1].y - this->coord[2].y));
    y.push_back(abs(this->coord[1].y - this->coord[3].y));

    y.push_back(abs(this->coord[2].y - this->coord[3].y));

    // находим основания
    // (у них у соответствующих точек друг другу разности в одной точке одинаковы)
    for (int i = 0; i < sides.size(); ++i) {
        for (int j = 0; j < sides.size(); ++j) {
            if (i != j && (x[i] == x[j] || y[i] == y[j])) {
                a = std::max(sides[i], sides[j]);
                b = std::min(sides[i], sides[j]);
            }
        }
    }

    // сортируем
    std::sort(sides.begin(), sides.end(), [] (double &a, double &b) {
        return a < b;
    });

    // удаляем диагонали
    sides.erase(sides.end() - 2, sides.end());

    // удаляем основания
    sides.erase(std::remove_if(
            sides.begin(), sides.end(), [&](double side) {
        return side != a && side != b;
    }));

    // вытаскиваем боковые стороны
    c = sides[0];
    d = sides[1];

    semiPerimetr = (a + b + c + d) / 2;

    std::cout << a << ", " << b << ", " << c << ", " << d << std::endl;
    std::cout << semiPerimetr << " = semiPer" << std::endl;

    this->area = (a + b) * sqrt( (semiPerimetr - a)
                                 * (semiPerimetr - b)
                                 * (semiPerimetr - a - c)
                                 * (semiPerimetr - a - d) )
            / abs(a - b);
}