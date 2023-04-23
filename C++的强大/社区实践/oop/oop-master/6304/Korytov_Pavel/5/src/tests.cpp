#include "color.h"

#include "point.h"
#include "shape.hpp"
#include "circle.hpp"
#include "pentagon.hpp"
#include "regular_pentagon.hpp"

#include "vector.hpp"
#include "shared_ptr.hpp"

#include "alg.hpp"

#include "gtest/gtest.h"

TEST(PointTest, PointTest1){
    Point p1(1,2);
    ASSERT_EQ(p1.GetX(), 1);
    ASSERT_EQ(p1.GetY(), 2);
    Point p2 = p1; Point p3(p2);
    ASSERT_TRUE((p1 == p2) && (p1 == p3) && (p2 == p3));
    p1 = p1 * 2;
    ASSERT_TRUE(p1 == Point(2, 4));
    p1 = p1 + Point (2,2);
    ASSERT_TRUE(p1 == Point(4,6));
    p1 = p1 / 2;
    ASSERT_TRUE(p1 == Point(2,3));
    p1.SetR(p1.GetR());
    p1.SetPhi(p1.GetPhi());
    ASSERT_TRUE(p1 == Point(2,3));
}

TEST(ShapeTest, ShapeTest1){
    Shape* ptr = new Shape();
    ASSERT_TRUE(ptr->getCenter() == Point(0,0));
    ASSERT_EQ(ptr->square(), 0);
    ptr->move(Point(20, 20));
    ASSERT_TRUE(ptr->getCenter() == Point(20, 20));
    ASSERT_TRUE(ptr->getColor() ==  Black);
    delete ptr;
}

TEST(CircleTest, CircleTest1){
    Circle* circ = new Circle(Pzero, 20);
    ASSERT_EQ(circ->getRadius(), 20);
    ASSERT_TRUE(circ->onCircle(Point(20, 0)));
    ASSERT_TRUE(circ->onCircle(Point(20*sqrt(2)/2, 20*sqrt(2)/2)));
    circ->setRadius(50.5);
    ASSERT_EQ(circ->getRadius(), 50.5);
    ASSERT_EQ(circ->square(), M_PI * 50.5 * 50.5);
    delete circ;
}

TEST(CircleTest, CirclePolymorphTest){
    Shape* shp = new Circle(Pzero, 10);
    ASSERT_EQ(shp->square(), M_PI * 10 * 10);
    shp->resize(2);
    ASSERT_EQ(shp->square(), M_PI * 20 * 20);
    delete shp;
}

TEST(PentagonTest, PentagonTest1){
    vector<Point> pvec = {Point(0,0), Point(2,2), Point(4,2), Point(6,0), Point(3, -4)};
    Pentagon* pnt = new Pentagon(pvec);
    ASSERT_TRUE(pnt->getCenter() == Point(3,0));
    ASSERT_EQ(pnt->square(), 20);
    vector<Point> pts = pnt->points();
    ASSERT_EQ(pts, pvec);
    pnt->resize(2);
    ASSERT_EQ(pnt->square(), 80);
    pnt->square();
    delete pnt;
}

TEST(RegularPentagonTest, RegularPentagonTest1){
    RegularPentagon* rpnt = new RegularPentagon(Pzero, 20);
    ASSERT_EQ(rpnt->square(), 951.0565162951535);
    Shape* shp = rpnt;
    ASSERT_EQ(rpnt->square(), 951.0565162951535);
    delete rpnt;
}

TEST(AlgTest, AlgTest1){
    vect_type vect;
    vect.push_back(stepik::shared_ptr<Shape>(new Circle(Pzero, 3)));
    vect.push_back(stepik::shared_ptr<Shape>(new RegularPentagon(Pzero, 9)));
    vect.push_back(stepik::shared_ptr<Shape>(new Circle(Pzero, 6)));
    vect.push_back(stepik::shared_ptr<Shape>(new RegularPentagon(Pzero, 10)));
    vect.push_back(stepik::shared_ptr<Shape>(new Circle(Pzero, 10)));
    ASSERT_EQ(getMaxSq(vect), 4);
}

TEST (AlgTest, AlgTest2){
    vect_type vect;
    vect.push_back(stepik::shared_ptr<Shape>(new Circle(Pzero, 20)));
    vect.push_back(stepik::shared_ptr<Shape>(new RegularPentagon(Pzero, 20)));
    vect.push_back(stepik::shared_ptr<Shape>(new Circle(Pzero, 4)));
    vect.push_back(stepik::shared_ptr<Shape>(new RegularPentagon(Pzero, 7)));
    vect.push_back(stepik::shared_ptr<Shape>(new Circle(Pzero, 6)));
    replaceSq(vect, stepik::shared_ptr<Shape>(new Circle(Pzero, 1)), 100);
    ASSERT_EQ(getMaxSq(vect), 2);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}