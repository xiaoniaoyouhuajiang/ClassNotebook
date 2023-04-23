// OOP 2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "string"
#include "Pentagon.h"
#include "Pentagram.h"
#include "Rectangle.h"
#include "iostream"
#include "gtest/gtest.h"

using namespace std;
using namespace ::testing;

TEST(myTestFixture1, rectangle) {
	Rectangle B(0, 0, 5.656, 5.656, 1, 45, "Green");
	Rectangle C(3.999, 3.999, 5.656, 5.656, 1, 45, "Green");
	Rectangle D(0, 0, 4, 4, 1, 0, "Green");
	Rectangle F(0, -4, 4, 4, 1, 0, "Green");
	Pentagram K(15, 9, 10, 1, 0, "Elow");
	Pentagon Z(5, 4, 3, 2, 0, "Elow");
	Pentagram M(15, 9, 10, 1, 0, "Elow");
	Rectangle E(19.625, 9, 10, 6, 1, 0, "Black");
	Pentagon Q(23.507, 9, 10, 1, 0, "Blue");
	//прямоугольник и остольные
	ASSERT_TRUE(B.hasCommonSide(C)); 
	ASSERT_FALSE(D.hasCommonSide(C)); 
	ASSERT_TRUE(D.hasCommonSide(F));
	ASSERT_FALSE(D.hasCommonSide(K));
	ASSERT_FALSE(D.hasCommonSide(Z));
	ASSERT_TRUE(E.hasCommonSide(M));
}
TEST(myTestFixture1, pentagram) {
	//пентограмма со всеми
	Rectangle F(0, -4, 4, 4, 1, 0, "Green");
	Pentagon Z(5, 4, 3, 2, 0, "Elow");
	Pentagram M(15, 9, 10, 1, 0, "Elow");
	Pentagram A(45, 6, 7, 8, 45, "Elow");
	Rectangle E(19.625, 9, 10, 6, 1, 0, "Black");
	Pentagon Q(23.507, 9, 10, 1, 0, "Blue");
	ASSERT_FALSE(A.hasCommonSide(F));
	ASSERT_TRUE(M.hasCommonSide(E));
	ASSERT_FALSE(M.hasCommonSide(Z));
	ASSERT_TRUE(M.hasCommonSide(Q));
}
TEST(myTestFixture1, pentagon) {
	Pentagon Q(23.507, 9, 10, 1, 0, "Blue");
	Pentagram M(15, 9, 10, 1, 0, "Elow");
	Pentagon Z(5, 4, 3, 2, 0, "Elow");
	Rectangle D(0, 0, 4, 4, 1, 0, "Green");
	Rectangle P(13.625, 9, 10, 6, 1, 0, "Green");
	ASSERT_FALSE(Q.hasCommonSide(Z));
	ASSERT_TRUE(Q.hasCommonSide(M));
	ASSERT_FALSE(Q.hasCommonSide(D));
	ASSERT_TRUE(Q.hasCommonSide(P));

}
int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("PAUSE");
	return 0;
}

