#include <list>
#include "gtest/gtest.h"
#include "figures/Shape.h"
#include "pointer/shared_ptr.h"
#include "list/list.h"
#include "figures/Circle.h"
#include "extra/Solver.h"

using namespace stepik;
Point *center = new Point(10, 10);
Color *color = new Color(1, 0, 2);
Solver solver;

shared_ptr<Shape> shared_shape1(new Circle(10, *center, *color));
shared_ptr<Shape> shared_shape2(new Circle(15, *center, *color));
shared_ptr<Shape> shared_shape3(new Circle(13, *center, *color));
shared_ptr<Shape> shared_shape4(new Circle(11, *center, *color));
shared_ptr<Shape> shared_shape5(new Circle(12, *center, *color));

bool pred(const shared_ptr<Shape> &sh) {
    return (*sh).isUnionOf((*shared_shape1), (*shared_shape2));
}

TEST(test_for_lab5, test1) {

    list<shared_ptr<Shape>> l;
    l.push_back(shared_ptr<Shape>(shared_shape1));
    l.push_back(shared_ptr<Shape>(shared_shape2));
    l.push_back(shared_ptr<Shape>(shared_shape3));
    l.push_back(shared_ptr<Shape>(shared_shape4));
    l.push_back(shared_ptr<Shape>(shared_shape5));

    shared_ptr<Shape> first = solver.findFirstElement(l, shared_shape1, shared_shape2);
    ASSERT_EQ(first, shared_shape2);
    solver.replaceAllElements(l, shared_shape1, shared_shape2, shared_shape3);
    ASSERT_EQ(l.size(), 5);
    list_iterator<shared_ptr<Shape>> iterator = l.begin();
    iterator++;
    ASSERT_EQ(*iterator, shared_shape3);
    l.clear();
}

TEST(test_for_lab5, test2) {
    list<shared_ptr<Shape>> l;
    l.push_back(shared_ptr<Shape>(shared_shape1));
    l.push_back(shared_ptr<Shape>(shared_shape2));
    l.push_back(shared_ptr<Shape>(shared_shape3));
    l.push_back(shared_ptr<Shape>(shared_shape4));
    l.push_back(shared_ptr<Shape>(shared_shape5));
    shared_ptr<Shape> first = solver.findFirstElement(l, shared_shape1, shared_shape2);

    std::list<shared_ptr<Shape>> listStandard;
    listStandard.push_back(shared_ptr<Shape>(shared_shape1));
    listStandard.push_back(shared_ptr<Shape>(shared_shape2));
    listStandard.push_back(shared_ptr<Shape>(shared_shape3));
    listStandard.push_back(shared_ptr<Shape>(shared_shape4));
    listStandard.push_back(shared_ptr<Shape>(shared_shape5));
    shared_ptr<Shape> firstStandard = *(std::find_if(listStandard.begin(), listStandard.end(), pred));
    ASSERT_EQ(first, firstStandard);
    l.clear();
    listStandard.clear();
}


TEST(test_for_lab5, test3) {
    list<shared_ptr<Shape>> l;
    l.push_back(shared_ptr<Shape>(shared_shape1));
    l.push_back(shared_ptr<Shape>(shared_shape2));
    l.push_back(shared_ptr<Shape>(shared_shape3));
    l.push_back(shared_ptr<Shape>(shared_shape4));
    l.push_back(shared_ptr<Shape>(shared_shape5));

    std::list<shared_ptr<Shape>> listStandard;
    listStandard.push_back(shared_ptr<Shape>(shared_shape1));
    listStandard.push_back(shared_ptr<Shape>(shared_shape2));
    listStandard.push_back(shared_ptr<Shape>(shared_shape3));
    listStandard.push_back(shared_ptr<Shape>(shared_shape4));
    listStandard.push_back(shared_ptr<Shape>(shared_shape5));

    solver.replaceAllElements(l, shared_shape1, shared_shape2, shared_shape3);
    std::replace_if(listStandard.begin(), listStandard.end(), pred, shared_shape3);

    ASSERT_TRUE(std::equal(l.begin(), l.end(), listStandard.begin()));
    l.clear();
    listStandard.clear();



}


