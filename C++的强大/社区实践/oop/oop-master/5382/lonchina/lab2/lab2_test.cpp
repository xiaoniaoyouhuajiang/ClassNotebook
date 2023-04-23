#include "gtest\gtest.h"
#include "shapes.h"
 

vector<Shape*> v;
 

RectangleFactory* rectangle_factory = new RectangleFactory;
CircleFactory*  circle_factory = new CircleFactory;
TrapeziumFactory*  trapezium_factory = new TrapeziumFactory;
 

TEST(lab2, Rectangle){
    v.push_back(rectangle_factory->createShape());
    v[0]->setColor("red");
    EXPECT_EQ(v[0]->getColor(), "red");
}
 
TEST(lab2, Circle){
    v.push_back(circle_factory->createShape());
    v[1]->setColor("yellow");
    EXPECT_EQ(v[1]->getColor(), "yellow");
}
 
TEST(lab2, Trapezium){
    v.push_back(trapezium_factory->createShape());
    v[2]->setColor("green");
    EXPECT_EQ(v[2]->getColor(), "green");
}
 
TEST(lab2, compare_test){//Сравнение площадей
    Rectangle rectangle({
        {0.0, 0.0},
        {0.0, 8.0},
        {6.0, 8.0},
        {6.0, 0.0}},
    {3.0, 4.0});
 
    Circle circle({
        {-3.0, 0.0},
        {3.0, 0.0}},
    {0.0, 0.0});
 
    EXPECT_EQ(48, rectangle.getArea());
    EXPECT_EQ(28, circle.getArea());
    EXPECT_TRUE(rectangle > circle);
    EXPECT_FALSE(rectangle < circle);
}
 
TEST(lab2, compare_test){
    Rectangle rectangle({
        {0.0, 0.0},
        {0.0, 8.0},
        {6.0, 8.0},
        {6.0, 0.0}},
    {3.0, 4.0});
 
    Trapezium({
        {0.0, 0.0},
        {4.0, 3.0},
        {7.0, 3.0},
        {11.0, 0.0}},
    {5.5, 1.5});
 
    EXPECT_EQ(48, rectangle.getArea());
    EXPECT_EQ(21, trapezium.getArea());
    EXPECT_TRUE(trapezium < rectangle);
    EXPECT_FALSE(trapezium > rectangle);
}
 
 
TEST(lab2, compare_test){
    Circle circle({
        {-3.0, 0.0},
        {3.0, 0.0}},
    {0.0, 0.0});
 
    Trapezium({
        {0.0, 0.0},
        {4.0, 3.0},
        {7.0, 3.0},
        {11.0, 0.0}},
    {5.5, 1.5});
 
    EXPECT_EQ(28, circle.getArea());
    EXPECT_EQ(21, trapezium.getArea());
    EXPECT_TRUE(trapezium < circle);
    EXPECT_FALSE(trapezium > circle);
}