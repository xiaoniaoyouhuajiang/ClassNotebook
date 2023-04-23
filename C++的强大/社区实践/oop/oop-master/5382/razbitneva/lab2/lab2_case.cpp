#include "gtest\gtest.h"
#include "shapes.h"

TEST(lab2, triangle){
	Triangle t(50, 0);
	EXPECT_EQ(t.get_angle(), 50);
}

TEST(lab2, rhombus){
	Rhombus r(50, 90);
	EXPECT_EQ(r.get_leng(), 50);
	EXPECT_EQ(r.get_agnle(), 90);
}

TEST(lab2, parallelogram){
	Parallelogram p(300, 100);
	EXPECT_EQ(p.get_width(), 300);
	EXPECT_EQ(p.get_heigth(), 100);
}

TEST(lab2, vertex){
	Triangle t(40, 8);
	Rhombus r(10, 30);
	Parallelogram p(90, 150);

	EXPECT_FALSE(Shape::hasCommonVertex(t, p));
	EXPECT_FALSE(Shape::hasCommonVertex(t, r));
	EXPECT_FALSE(Shape::hasCommonVertex(p, r));
}