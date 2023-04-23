#include <iostream>

bool range_check(int left, int right, int flag_color, stepik::vector<stepik::shared_ptr<Shapes>> shapes)
{
	for (int i = left; i < right; i++)
		if(shapes[i]->getDraw()==flag_color) return false;
	return true;
}

stepik::vector<stepik::shared_ptr<Shapes>> copy(int flag_color, stepik::vector<stepik::shared_ptr<Shapes>> shapes)
{
	stepik::vector<stepik::shared_ptr<Shapes>> copy_shapes;
	for (int i = 0; i < shapes.size(); i++)
		if (shapes[i]->getDraw()!=flag_color) copy_shapes.push_back(shapes[i]);
	return copy_shapes;
}

float GenNum()
{
	float t = rand() % 1000 + 1;
	float r = (t / 1000) + 0.5;
	return r;
}

stepik::shared_ptr<Shapes> GenerationEllipse(int flag)
{
	if(flag == 0) {stepik::shared_ptr<Shapes> x(new Ellipse(rand() % 20 - 10, rand() % 20 - 10, 
											 rand() % 5 + 1, rand() % 5 + 10,
											 rand() % 5 + 1));return x;}
	else {stepik::shared_ptr<Shapes> x(new Ellipse(rand() % 20 - 10, rand() % 20 - 10, 
											 rand() % 5 + 1, rand() % 5 + 10,
											 flag));return x;}
}

stepik::shared_ptr<Shapes> GenerationTrapezium(int flag)
{
	if(flag == 0) {stepik::shared_ptr<Shapes> x(new Trapeze(rand() % 20 - 10, rand() % 20 - 10, 
											   rand() % 5 + 1, rand() % 5 + 10,
											   GenNum(), GenNum(),
											   rand() % 5 + 1)); return x;}
	else {stepik::shared_ptr<Shapes> x(new Trapeze(rand() % 20 - 10, rand() % 20 - 10, 
											   rand() % 5 + 1, rand() % 5 + 10,
											   GenNum(), GenNum(),
											   flag)); return x;}
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
