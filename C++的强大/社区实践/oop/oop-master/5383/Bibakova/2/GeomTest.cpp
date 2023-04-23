// GeomTest.cpp: îïðåäåëÿåò òî÷êó âõîäà äëÿ êîíñîëüíîãî ïðèëîæåíèÿ.
//

//#include "stdafx.h"

#include "gtest/gtest.h"
#include "../Geom/shape.hpp"
#include "../Geom/Circle.hpp"
#include "../Geom/Pentagon.hpp"
#include "../Geom/RegularPentagon.hpp"

class FigTest : public ::testing::Test
{
protected:
	Circle *cir1, *cir2, *cir3;
	Pentagon *pen1, *pen2, *pen3;
	RegularPentagon *rp1, *rp2, *rp3;

	void setUp()
	{
		/*sc = new Circle({ 0, 0 }, 3, "red");
		sp = new Pentagon({ 0, 0 }, { 0, 3 }, { 1, 4 }, { 3, 1 }, { 2, -1 }, "red");
		srp = new RegularPentagon({ 1, 1 }, 2, "red");*/

		cir1 = new Circle({ 0, 0 }, 3, "red");
		cir2 = new Circle({ 1, 1 }, 3, "red");
		cir3 = new Circle({ -4, 0 }, 6, "blue");
		

		pen1 = new Pentagon({ 0, 0 }, { 0, 3 }, { 1, 4 }, { 3, 1 }, { 2, -1 }, "red");

		rp1 = new RegularPentagon({ 1, 1 }, 2, "red");
	}

	void TearDown()
	{

		delete cir1;
		delete cir2;
		delete cir3;

		delete pen1;

		delete rp1;
	}
};

class FiTest : public ::testing::Test
{};

TEST_F(FiTest, CC1)
{
	Circle *cir1 = new Circle({ 0, 0 }, 3, "red");
	EXPECT_TRUE(cir1->equalÎxProjectionLength(*cir1));
	delete cir1;
};

TEST_F(FiTest, PP1)
{
	Pentagon *p1 = new Pentagon({ 0, 0 }, { 1, 1 }, { 3, 2 }, { 5, -1 }, { 2, -3 }, "red");
	EXPECT_TRUE(p1->equalÎxProjectionLength(*p1));
	delete p1;
};

TEST_F(FiTest, RpRp1)
{
	RegularPentagon *p1 = new RegularPentagon({ 0, 0 }, 3, "red");
	EXPECT_TRUE(p1->equalÎxProjectionLength(*p1));
	delete p1;
};

TEST_F(FiTest, SS1)
{
	Shape *s = new Circle({ 0, 0 }, 3, "red");
	EXPECT_TRUE(s->equalÎxProjectionLength(*s));
	delete s;
};

TEST_F(FiTest, SC1)
{
	Shape *s = new Circle({ 0, 0 }, 3, "red");
	Circle *cir1 = new Circle({ 0, 0 }, 3, "red");

	EXPECT_TRUE(s->equalÎxProjectionLength(*cir1));

	delete s;
	delete cir1;
};

TEST_F(FiTest, CC2)
{
	Circle *cir1 = new Circle({ 0, 0 }, 3, "red");
	Circle *cir2 = new Circle({ -2, 4 }, 3, "red");

	EXPECT_TRUE(cir2->equalÎxProjectionLength(*cir1));
	EXPECT_TRUE(cir1->equalÎxProjectionLength(*cir2));

	delete cir2;
	delete cir1;
};

TEST_F(FiTest, PP2)
{
	Pentagon *p1 = new Pentagon({ 0, 0 }, { 1, 1 }, { 3, 2 }, { 5, -1 }, { 2, -3 }, "red");
	Pentagon *p2 = new Pentagon({ 0, 0 }, { 3, 2 }, { 1, 1 }, { 2, -3 }, { 5, -1 }, "red");

	EXPECT_TRUE(p2->equalÎxProjectionLength(*p1));
	EXPECT_TRUE(p1->equalÎxProjectionLength(*p2));

	delete p2;
	delete p1;
};

TEST_F(FiTest, PP3)
{
	Pentagon *p1 = new Pentagon({ 0, 0 }, { 1, 1 }, { 3, 2 }, { 5, -1 }, { 2, -3 }, "red");
	Pentagon *p2 = new Pentagon({ 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, "red");

	EXPECT_EQ(5, p1->oxPrLength());
	EXPECT_EQ(0, p2->oxPrLength());
	EXPECT_FALSE(p2->equalÎxProjectionLength(*p1));
	EXPECT_FALSE(p1->equalÎxProjectionLength(*p2));

	delete p2;
	delete p1;
};

TEST_F(FiTest, CP1)
{
	Pentagon *p1 = new Pentagon({ 0, 0 }, { 1, 1 }, { 3, 2 }, { 5, -1 }, { 2, -3 }, "red");
	Circle *cir2 = new Circle({ -2, 4 }, 3, "red");

	EXPECT_FALSE(cir2->equalÎxProjectionLength(*p1));
	EXPECT_FALSE(p1->equalÎxProjectionLength(*cir2));

	delete p1;
	delete cir2;
};

TEST_F(FiTest, CP2)
{
	Pentagon *p1 = new Pentagon({ 0, 0 }, { 1, 1 }, { 3, 2 }, { 6, -1 }, { 2, -3 }, "red");
	Circle *cir2 = new Circle({ -2, 4 }, 3, "red");

	EXPECT_TRUE(cir2->equalÎxProjectionLength(*p1));
	EXPECT_TRUE(p1->equalÎxProjectionLength(*cir2));

	delete p1;
	delete cir2;
};

TEST_F(FiTest, RpRp2)
{
	RegularPentagon *p1 = new RegularPentagon({ 0, 0 }, 3, "red");
	RegularPentagon *p2 = new RegularPentagon({ -3, 5 }, 3, "red");

	EXPECT_TRUE(p1->equalÎxProjectionLength(*p2));
	EXPECT_TRUE(p2->equalÎxProjectionLength(*p1));

	delete p1;
	delete p2;
};

TEST_F(FiTest, RpRp3)
{
	RegularPentagon *p1 = new RegularPentagon({ 0, 0 }, 3, "red");
	RegularPentagon *p2 = new RegularPentagon({ 0, 0 }, 5, "red");

	EXPECT_FALSE(p1->equalÎxProjectionLength(*p2));
	EXPECT_FALSE(p2->equalÎxProjectionLength(*p1));

	delete p1;
	delete p2;
};


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

