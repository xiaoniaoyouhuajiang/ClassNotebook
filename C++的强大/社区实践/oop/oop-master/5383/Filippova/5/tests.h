#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <algorithm>
#include <vector>
#include "5.h"

using namespace testing;


TEST(Test5, ModifyingAlgorithm)
{
    std::vector< stepik::shared_ptr<Shape> > src = {
        stepik::shared_ptr<Shape> (new Rectangle(Point(100, 100), 5, 1, 0)), // true
        stepik::shared_ptr<Shape> (new Ellipse(Point(500, 250), 3, 4, M_PI/4)), // true
        stepik::shared_ptr<Shape> (new Square(Point(10, 10), 5, 0)), // false
        stepik::shared_ptr<Shape> (new Ellipse(Point(100, 100), 5, 2, 0)), // true
        stepik::shared_ptr<Shape> (new Rectangle(Point(-200, -100), 10, 5, M_PI/4)), // true
        stepik::shared_ptr<Shape> (new Square(Point(1000, -1000), 1, M_PI/8)), // true
        stepik::shared_ptr<Shape> (new Ellipse(Point(0, 0), 1, 1, 0)), // false
    };

    stepik::list< stepik::shared_ptr<Shape> > in, exp;

    for (auto elem : src)
        in.push_back(elem);

    exp.push_back(src[0]);
    exp.push_back(src[1]);
    exp.push_back(src[3]);
    exp.push_back(src[4]);
    exp.push_back(src[5]);

    auto res = stepik::copy_if(in, stepik::predicate);

    EXPECT_EQ(res, exp);
}

TEST(Test5, UnmodifyingAlgorithm)
{
    std::vector< stepik::shared_ptr<Shape> > src = {
        stepik::shared_ptr<Shape> (new Rectangle(Point(100, 100), 5, 1, 0)), // true
        stepik::shared_ptr<Shape> (new Ellipse(Point(500, 250), 3, 4, M_PI/4)), // true
        stepik::shared_ptr<Shape> (new Square(Point(10, 10), 5, 0)), // false
        stepik::shared_ptr<Shape> (new Ellipse(Point(100, 100), 5, 2, 0)), // true
        stepik::shared_ptr<Shape> (new Rectangle(Point(-200, -100), 10, 5, M_PI/4)), // true
        stepik::shared_ptr<Shape> (new Square(Point(1000, -1000), 1, M_PI/8)), // true
        stepik::shared_ptr<Shape> (new Ellipse(Point(0, 0), 1, 1, 0)), // false

    };

    stepik::list< stepik::shared_ptr<Shape> > l;
    for (auto elem : src)
        l.push_back(elem);

    auto res = l.begin();
    res = stepik::search_n(l, 4, stepik::predicate);
    auto expected = l.begin();
    /*int count = 0;
    while(count <= 3)
    {
        expected++;
        count++;
    }*/
    EXPECT_EQ(res, expected);
}

TEST(Test5, UnmodifyingAlgorithmNone)
{
    std::vector< stepik::shared_ptr<Shape> > src = {
        stepik::shared_ptr<Shape> (new Rectangle(Point(100, 100), 5, 1, 0)), // true
        stepik::shared_ptr<Shape> (new Ellipse(Point(500, 250), 3, 4, M_PI/4)), // true
        stepik::shared_ptr<Shape> (new Square(Point(10, 10), 5, 0)), // false
        stepik::shared_ptr<Shape> (new Ellipse(Point(100, 100), 5, 2, 0)), // true
        stepik::shared_ptr<Shape> (new Ellipse(Point(0, 0), 1, 1, 0)), // false
        stepik::shared_ptr<Shape> (new Rectangle(Point(-200, -100), 10, 5, M_PI/4)), // true
        stepik::shared_ptr<Shape> (new Square(Point(1000, -1000), 1, M_PI/8)), // true
    };

    stepik::list< stepik::shared_ptr<Shape> > l;

    for (auto elem : src)
        l.push_back(elem);

    auto res = l.begin();
    res = stepik::search_n(l, 6, stepik::predicate);

    auto expected = l.begin();
    EXPECT_EQ(res, expected);
}

TEST(Test5, ModifyingAlgorithm1)
{
    std::vector< stepik::shared_ptr<Shape> > src = {
        stepik::shared_ptr<Shape> (new Rectangle(Point(0, 1), 5, 1, 0)), // false
        stepik::shared_ptr<Shape> (new Ellipse(Point(1, 1), 3, 4, M_PI/4)), // false
        stepik::shared_ptr<Shape> (new Square(Point(10, 10), 5, 0)), // false
        stepik::shared_ptr<Shape> (new Ellipse(Point(0, 3), 5, 2, 0)), // false
        stepik::shared_ptr<Shape> (new Rectangle(Point(7, 15), 10, 5, M_PI/4)), // false
        stepik::shared_ptr<Shape> (new Square(Point(1, -1), 1, M_PI/8)), // false
        stepik::shared_ptr<Shape> (new Ellipse(Point(0, 0), 1, 1, 0)), // false
    };

    stepik::list< stepik::shared_ptr<Shape> > in, exp;

    for (auto elem : src)
        in.push_back(elem);

    auto res = stepik::copy_if(in, stepik::predicate);

    EXPECT_EQ(res, exp);
}

