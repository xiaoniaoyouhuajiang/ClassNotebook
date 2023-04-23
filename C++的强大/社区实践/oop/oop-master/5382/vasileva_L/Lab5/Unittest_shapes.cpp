#include "gtest/gtest.h"
#include "oop_lr5.h"

TEST(test_sort_from_diapazones, diapazones_from_first_vector)
{
	srand(time(0));
	unsigned size = 1000;
	stepik::vector<stepik::shared_ptr<Shape>> shapes = GenerationVector(size);	
	stepik::vector<stepik::shared_ptr<Shape>> shapes2 = UniontwoDiapazons(shapes, 2, 100, 50, 900);	
	for (int i = 0; i < shapes2.size() - 2; i++)
	{
		ASSERT_LE(shapes2[i]->Perimeter(), shapes2[i+1]->Perimeter());
	}

	shapes2 = UniontwoDiapazons(shapes, 0, 700, 200, 1000);	
	for (int i = 0; i < shapes2.size() - 2; i++)
	{
		ASSERT_LE(shapes2[i]->Perimeter(), shapes2[i+1]->Perimeter());
	}

	ASSERT_THROW(UniontwoDiapazons(shapes, 0, 700, 200, 2000), std::invalid_argument);
	ASSERT_THROW(UniontwoDiapazons(shapes, -100, 700, 200, 300), std::invalid_argument);
	ASSERT_THROW(UniontwoDiapazons(shapes, 100, -50, 200, 300), std::invalid_argument);
	ASSERT_THROW(UniontwoDiapazons(shapes, 100, 100, 200, 199), std::invalid_argument);
}

TEST(test_sort_from_diapazones, diapazones_from_two_diapazones)
{
	srand(time(0));
	unsigned size1 = 500, size2 = 700;
	stepik::vector<stepik::shared_ptr<Shape>> dip1 = GenerationVector(size1);	
	stepik::vector<stepik::shared_ptr<Shape>> dip2 = GenerationVector(size2);	
	stepik::vector<stepik::shared_ptr<Shape>> shapes2 = UniontwoDiapazons(dip1, dip2);	
	for (int i = 0; i < shapes2.size() - 2; i++)
	{
		ASSERT_LE(shapes2[i]->Perimeter(), shapes2[i+1]->Perimeter());
	}

	size1 = 0, size2 = 300;
	dip1 = GenerationVector(size1);	
	dip2 = GenerationVector(size2);	
	shapes2 = UniontwoDiapazons(dip1, dip2);	
	for (int i = 0; i < shapes2.size() - 2; i++)
	{
		ASSERT_LE(shapes2[i]->Perimeter(), shapes2[i+1]->Perimeter());
	}

}

TEST(test_find_equals_in_color, false_test)
{
	srand(time(0));
	unsigned size = 1000;
	stepik::vector<stepik::shared_ptr<Shape>> shapes1 = GenerationVector(size);
	int j = 0;
	for (int i = 0; i < shapes1.size(); i++)
	{
		if (j == 6)
			j = 0;
		else j++;	
		shapes1[i]->setColor(j);
	}
	stepik::shared_ptr<Shape> foundEqual;	
	ASSERT_FALSE(SearchforEqualinColor(shapes1, foundEqual));
	ASSERT_EQ(foundEqual, shapes1[shapes1.size()-1]);

	stepik::vector<stepik::shared_ptr<Shape>> shapes2 = GenerationVector(10);	
	shapes2[0]->setColor(0);
	shapes2[1]->setColor(5);
	shapes2[2]->setColor(4);
	shapes2[3]->setColor(5);
	shapes2[4]->setColor(1);
	shapes2[5]->setColor(0);
	shapes2[6]->setColor(3);
	shapes2[7]->setColor(0);
	shapes2[8]->setColor(3);
	shapes2[9]->setColor(1);
	ASSERT_FALSE(SearchforEqualinColor(shapes2, foundEqual));
	ASSERT_EQ(foundEqual -> getColor(), 1);	
}


TEST(test_find_equals_in_color, true_test)
{
	srand(time(0));
	unsigned size = 1000;
	stepik::vector<stepik::shared_ptr<Shape>> shapes1 = GenerationVector(size);
	int j = 0;
	for (int i = 0; i < shapes1.size(); i++)
	{
		if (j == 6)
			j = 0;
		else j++;	
		shapes1[i]->setColor(j);
	}
	int n = 24, m = 300;
	shapes1[n]->setColor(shapes1[n - 1] -> getColor());
	shapes1[m]->setColor(shapes1[m - 1] -> getColor());
	shapes1[m + 1]->setColor(shapes1[m - 1] -> getColor());
	stepik::shared_ptr<Shape> foundEqual;	
	ASSERT_TRUE(SearchforEqualinColor(shapes1, foundEqual));
	ASSERT_EQ(foundEqual, shapes1[n - 1]);

	stepik::vector<stepik::shared_ptr<Shape>> shapes2 = GenerationVector(10);	
	shapes2[0]->setColor(0);
	shapes2[1]->setColor(5);
	shapes2[2]->setColor(4);
	shapes2[3]->setColor(5);
	shapes2[4]->setColor(1);
	shapes2[5]->setColor(0);
	shapes2[6]->setColor(3);
	shapes2[7]->setColor(1);
	shapes2[8]->setColor(1);
	shapes2[9]->setColor(1);
	ASSERT_TRUE(SearchforEqualinColor(shapes2, foundEqual));
	ASSERT_EQ(foundEqual, shapes2[7]);	
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
