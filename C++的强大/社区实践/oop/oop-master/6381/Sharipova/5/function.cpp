#include <iostream>
#include <function.h>
bool range_check(int left, int right, int flag_color, stepik::vector<stepik::shared_ptr<Shapes>> shapes)
{
	for (int i = left; i < right; i++)
		if(shapes[i]->getDraw()==flag_color) return true;
	return false;
}

stepik::vector<stepik::shared_ptr<Shapes>> copy(int flag_color, stepik::vector<stepik::shared_ptr<Shapes>> shapes)
{
	stepik::vector<stepik::shared_ptr<Shapes>> copy_shapes;
	bool flag = true;
	for (int i = 0; i < shapes.size(); i++)
	{
		if (shapes[i]->getDraw()!=flag_color) copy_shapes.push_back(shapes[i]);
		else 
		{
			if (flag == true) 
			{
				copy_shapes.push_back(shapes[i]);	
				flag = false;
			}
		}
	}
	return copy_shapes;
}

float GenNum()
{
	float t = rand() % 1000 + 1;
	float r = (t / 1000) + 0.5;
	return r;
}

stepik::shared_ptr<Shapes> GenerationRectangle(int flag)
{
	float coordinates[4][2];
	for (int i = 0; i < 4; i++)
	{
		coordinates[i][0] = rand() % 20 - 10;
		coordinates[i][1] = rand() % 20 - 10;
	}
	if(flag == 0) {stepik::shared_ptr<Shapes> x(new Rectangle(coordinates,
											  rand() % 5 + 1));return x;}
	else {stepik::shared_ptr<Shapes> x(new Rectangle(coordinates,flag));return x;}
}

stepik::shared_ptr<Shapes> GenerationPentagram(int flag)
{
	float coordinates[5][2];
	for (int i = 0; i < 5; i++)
	{
		coordinates[i][0] = rand() % 20 - 10;
		coordinates[i][1] = rand() % 20 - 10;
	}
	if(flag == 0) {stepik::shared_ptr<Shapes> x(new Pentagram(coordinates,
											  rand() % 5 + 1));return x;}
	else {stepik::shared_ptr<Shapes> x(new Pentagram(coordinates,flag));return x;}
}

stepik::shared_ptr<Shapes> GenerationPentagon(int flag)
{
	float coordinates[5][2];
	for (int i = 0; i < 5; i++)
	{
		coordinates[i][0] = rand() % 20 - 10;
		coordinates[i][1] = rand() % 20 - 10;
	}
	if(flag == 0) {stepik::shared_ptr<Shapes> x(new Pentagon(coordinates,
											  rand() % 5 + 1));return x;}
	else {stepik::shared_ptr<Shapes> x(new Pentagon(coordinates,flag));return x;}
}
