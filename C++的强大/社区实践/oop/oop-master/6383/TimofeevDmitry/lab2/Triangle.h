#ifndef LAB2_TRIANGLE_H
#define LAB2_TRIANGLE_H

#include <vector>
#include "Shape.h"

class Triangle: public Shape{
private:
    std::vector<Point> pts;
    double ab;
    double ac;
    double bc;
protected:
    void onTransformed() override ;
public:
    Triangle(std::string color,const Point& a,const Point& b, const Point& c);
    void applyForAnyPoint(std::function<void(Point&)> const & f) override;
    std::string toString() const override ;
    double getAB();
    double getAC();
    double getBC();
};
#endif //LAB2_TRIANGLE_H
