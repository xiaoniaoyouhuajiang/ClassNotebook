#include "vector.h"
#include "shared_ptr.h"
#include "figure.h"
#include "lab_fun.h"
#include <iostream>
#include <gtest/gtest.h>
#include <functional>

using namespace stepik;

TEST(testSort, generateTest) {
  shapeVec a;
  generateShapes(a, 10);
  sortShapeVec(a);
  for (size_t i = 0; i < a.size()-1;i++) {
    ASSERT_TRUE((a[i])->area() <= (a[i+1])->area());
  }

  a = shapeVec();
  generateShapes(a, 100);
  sortShapeVec(a);
  for (size_t i = 0; i < a.size()-1;i++) {
    ASSERT_TRUE((a[i])->area() <= (a[i+1])->area());
  }
}

TEST(testAlg1, test) {
  shapeVec a;
  stepik::shared_ptr<Shape> q;
  auto lambda = [](stepik::shared_ptr<Shape> a) {
    return shapePredicate(*a);};

  auto is_partitioned_p_rev = std::bind([] (shapeVec a, auto lambda) {
      bool p = std::is_partitioned(a.begin(), a.end(), lambda);
      std::reverse(a.begin(), a.end());
      return (p || std::is_partitioned(a.begin(), a.end(), lambda));},
    std::cref(a), lambda);
      
  q.reset(new Triangle(3, Point(3, 3)));
  a.push_back(q);

  ASSERT_TRUE(isPartitioned(a));

  q.reset(new Triangle(3, Point(3, 3), Point(5, 5)));
  a.push_back(q);
  ASSERT_TRUE(isPartitioned(a));
  ASSERT_EQ(isPartitioned(a),
            (is_partitioned_p_rev()));

  q.reset(new Rhombus(1, 3.14159/3));
  a.insert(a.begin(), q);
  ASSERT_TRUE(isPartitioned(a));
  ASSERT_EQ(isPartitioned(a),
            (is_partitioned_p_rev()));

  q->scale(500);
  ASSERT_TRUE(isPartitioned(a));
  ASSERT_EQ(isPartitioned(a),
            (is_partitioned_p_rev()));

  q.reset(new Parallelogram(1, 1, Point(-10, 10)));
  a.push_back(q);

  ASSERT_TRUE(isPartitioned(a, Parallelogram(1000, 1000, Point(-5, -5))));

  a.insert(a.begin(), q);
  a.insert(a.end(), q);
  ASSERT_FALSE(isPartitioned(a, Parallelogram(1000, 1000, Point(-5, -5))));

  a = shapeVec();
  generateShapes(a, 10);
  ASSERT_EQ(isPartitioned(a),
            (is_partitioned_p_rev()));

  a = shapeVec();
  generateShapes(a, 1000);
  ASSERT_EQ(isPartitioned(a),
            (is_partitioned_p_rev()));
}

TEST(testAlg2, test) {
  shapeVec a;
  shapeVec b;
  shapeVec temp;
  stepik::shared_ptr<Shape> q;

  q.reset(new Triangle(3, Point(3, 3)));
  a.push_back(q);
  q.reset(new Triangle(3, Point(3, 3), Point(5, 5)));
  a.push_back(q);
  temp = intersection(a, b);
  ASSERT_TRUE(temp.size() == 0);


  b.push_back(q);
  temp = intersection(a, b);
  ASSERT_TRUE(temp.size() == 1);
  ASSERT_EQ(*temp[0], *q);
  q.reset(new Parallelogram(3, 90, Point(5, 5)));
  a.push_back(q);
  b.push_back(q);
  temp = intersection(a, b);
  ASSERT_TRUE(temp.size() == 2);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
