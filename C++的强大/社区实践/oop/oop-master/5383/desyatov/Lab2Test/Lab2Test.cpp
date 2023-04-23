#include "gtest\gtest.h"
#include "..\ЛР2\Shape.h"
#include "..\ЛР2\Ellipse.h"
#include "..\ЛР2\Trapezium.h"
#include "..\ЛР2\EqualTrapezium.h"
#include "..\ЛР2\Figure.h"
#include "Sharedptr.h"
#include "Vector.h"
#include <algorithm>
#include <iostream>

TEST(area_tests, test1)
{
	//Равны
	Ellipse ellipse1(10, 20);
	Ellipse ellipse2(10, 20);
	Trapezium trap1(4, 10, 2);
	Trapezium trap2(4, 10, 2);
	EqualTrapezium etrap1(20, 40, 1);
	EqualTrapezium etrap2(20, 40, 1);

	EXPECT_EQ(3, Shape::compareAreas(ellipse1, ellipse2));
	EXPECT_EQ(3, Shape::compareAreas(trap1, trap2));
	EXPECT_EQ(3, Shape::compareAreas(etrap1, etrap2));
	EXPECT_EQ(3, Shape::compareAreas(trap1, etrap2));

	//Первая > второй
	Ellipse ellipse3(50, 60);
	Ellipse ellipse4(10, 20);
	Trapezium trap3(10, 15, 4);
	Trapezium trap4(5, 10, 2);
	EqualTrapezium etrap3(20, 40, 10);
	EqualTrapezium etrap4(10, 20, 5);
	
	EXPECT_EQ(1, Shape::compareAreas(ellipse3, ellipse4));
	EXPECT_EQ(1, Shape::compareAreas(trap3, trap4));
	EXPECT_EQ(1, Shape::compareAreas(etrap3, etrap4));
	EXPECT_EQ(1, Shape::compareAreas(ellipse1,etrap1));
	
	//Первая < второй
	Ellipse ellipse5(10, 20);
	Ellipse ellipse6(50, 60);
	Trapezium trap5(5, 10, 2);
	Trapezium trap6(10, 15, 4);
	EqualTrapezium etrap5(10, 20, 5);
	EqualTrapezium etrap6(20, 40, 10);
	
	EXPECT_EQ(2, Shape::compareAreas(ellipse5, ellipse6));
	EXPECT_EQ(2, Shape::compareAreas(trap5, trap6));
	EXPECT_EQ(2, Shape::compareAreas(etrap5, etrap6));
	EXPECT_EQ(2, Shape::compareAreas(trap5, ellipse6));
}

bool nonmodifyringPred(const stepik::shared_ptr<Shape>& a, const stepik::shared_ptr<Shape>& b) {
	return Shape::compareAreas(*a, *b) == 3;
}

TEST(laba5, nonmodifying) {
	stepik::shared_ptr<Shape> f0 (new Ellipse(10, 20));
	stepik::shared_ptr<Shape> f1 (new Trapezium(4, 10, 2));
	stepik::shared_ptr<Shape> f2 (new Ellipse(50, 60));
	stepik::shared_ptr<Shape> f3 (new EqualTrapezium(20, 40, 10));
	stepik::shared_ptr<Shape> f4 (new EqualTrapezium(20, 40, 10));
	stepik::shared_ptr<Shape> f5 (new Trapezium(5, 10, 2));
	stepik::shared_ptr<Shape> f6 (new Trapezium(10, 15, 4));
	EXPECT_EQ(true, nonmodifyringPred(f3, f4));
	std::vector<stepik::shared_ptr<Shape>> v({ f0,f1,f2,f3,f4,f5,f6 });
	auto it = std::adjacent_find(v.begin(), v.end(), nonmodifyringPred);
	EXPECT_EQ(v.begin()+3, it);
}


bool modifyingPred(const stepik::shared_ptr<Shape>& a, const stepik::shared_ptr<Shape>& b) {
	return Shape::compareAreas(*a, *b) == 2;
}

TEST(laba5, modifying) {
	stepik::shared_ptr<Shape> f0(new Ellipse(10, 20)); // 628
	stepik::shared_ptr<Shape> f1(new Trapezium(4, 10, 2)); // 30
	stepik::shared_ptr<Shape> f2(new Ellipse(50, 60)); // 9420
	stepik::shared_ptr<Shape> f3(new EqualTrapezium(20, 40, 10)); // 300
	stepik::shared_ptr<Shape> f4(new EqualTrapezium(20, 40, 15)); // 450
	stepik::shared_ptr<Shape> f5(new Trapezium(5, 10, 2)); // 35
	stepik::shared_ptr<Shape> f6(new Trapezium(10, 15, 4)); // 105
	stepik::vector<stepik::shared_ptr<Shape>> v1({ f0,f1,f2,f3 });
	stepik::vector<stepik::shared_ptr<Shape>> v2({ f4,f5,f6 });
	std::sort(v1.begin(), v1.end(), modifyingPred);
	std::sort(v2.begin(), v2.end(), modifyingPred);
	stepik::vector<stepik::shared_ptr<Shape>> v(v1.size() + v2.size());
	std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin(), modifyingPred);
	EXPECT_EQ(v[0].get(), f1.get());
	EXPECT_EQ(v[1].get(), f5.get());
	EXPECT_EQ(v[2].get(), f6.get());
	EXPECT_EQ(v[3].get(), f3.get());
	EXPECT_EQ(v[4].get(), f4.get());
	EXPECT_EQ(v[5].get(), f0.get());
	EXPECT_EQ(v[6].get(), f2.get());
}