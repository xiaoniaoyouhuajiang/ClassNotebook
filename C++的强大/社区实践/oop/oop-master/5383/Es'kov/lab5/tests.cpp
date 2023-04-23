#include "gtest\gtest.h"
#include "lab5.h"

/*HDC _hdc = NULL;
stepik::vector< stepik::shared_ptr<shape> > res;

stepik::vector< stepik::shared_ptr<shape> > kappa1 =
{
	stepik::shared_ptr<shape>(new circle(50, paint_area_info(500, 500, 250, 250, _hdc, rgb_color(255, 0, 0)))),
	stepik::shared_ptr<shape>(new ellipse(100, 200, paint_area_info(500, 500, 750, 250, _hdc, rgb_color(0, 255, 0)))),
	stepik::shared_ptr<shape>(new arc(40, 0, 270, paint_area_info(500, 500, 1250, 250, _hdc, rgb_color(0, 0, 255))))
};

stepik::vector< stepik::shared_ptr<shape> > kappa2 =
{
	stepik::shared_ptr<shape>(new arc(40, 0, 270, paint_area_info(500, 500, 1250, 250, _hdc, rgb_color(0, 0, 255)))),
	stepik::shared_ptr<shape>(new ellipse(100, 200, paint_area_info(500, 500, 750, 250, _hdc, rgb_color(0, 255, 0)))),
	stepik::shared_ptr<shape>(new circle(50, paint_area_info(500, 500, 250, 250, _hdc, rgb_color(255, 0, 0))))
};

stepik::vector< stepik::shared_ptr<shape> > kappa3 =
{
	stepik::shared_ptr<shape>(new ellipse(100, 220, paint_area_info(500, 500, 750, 250, _hdc, rgb_color(0, 255, 0)))),
	stepik::shared_ptr<shape>(new ellipse(120, 230, paint_area_info(500, 500, 750, 250, _hdc, rgb_color(0, 255, 0)))),
	stepik::shared_ptr<shape>(new ellipse(130, 240, paint_area_info(500, 500, 750, 250, _hdc, rgb_color(0, 255, 0))))
};

stepik::vector< stepik::shared_ptr<shape> > kappa4 =
{
	stepik::shared_ptr<shape>(new circle(50, paint_area_info(500, 500, 250, 250, _hdc, rgb_color(255, 0, 0)))),
	stepik::shared_ptr<shape>(new circle(100, paint_area_info(500, 500, 250, 250, _hdc, rgb_color(255, 0, 0)))),
	stepik::shared_ptr<shape>(new circle(150, paint_area_info(500, 500, 250, 250, _hdc, rgb_color(255, 0, 0))))
};

TEST(lab5_test, my_func1){
	EXPECT_EQ(same_search(kappa1, kappa2), 1);
	EXPECT_EQ(same_search(kappa3, kappa4), INT_MIN);
}

TEST(lab5_test, my_func2){
	res = intersection(kappa1, kappa2);
	EXPECT_EQ(res.size(), 1);
	EXPECT_EQ(res[0]->shape_type(), "ellipse");

	res = intersection(kappa3, kappa4);
	EXPECT_EQ(res.size(), 0);
}*/

void main(){
	setlocale(LC_ALL, "rus");

	//Генерируем
	stepik::vector< stepik::shared_ptr<shape> > shapes1 = generateshapes(1337);
	stepik::vector< stepik::shared_ptr<shape> > shapes2 = generateshapes(1337);

	//Ищем пересечения и сортируем
	stepik::vector< stepik::shared_ptr<shape> > result = intersection(shapes1, shapes2);

	for (unsigned int i = 0; i < result.size(); i++)
		cout << result[i]->shape_type() << ", perimeter: " << result[i]->perimetr() << endl;
	cout << "\nРазмер вектора пересечений: " << result.size() << ", первое пересечение на позиции " << same_search(shapes1, shapes2) << endl;

	system("pause");
}