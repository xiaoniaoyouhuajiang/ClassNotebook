#include <iostream>
#include "function.h"

bool test1()//Точно есть элемент
{
	stepik::vector<stepik::shared_ptr<Shapes>> shapes;
	
	unsigned size = 50;
	
	for (int n=0; n<100; n++)
	{
		stepik::shared_ptr<Shapes> x;
		for (unsigned i = 0; i < size; i++)
		{
			int k = rand() % 3 + 1;
			switch (k)
			{
			case 1:
				x = GenerationPentagram(0);
				break;
			case 2:
				x = GenerationRectangle(0);
				break;
			case 3:
				x = GenerationPentagon(0);
				break;
			}
			shapes.push_back(x);
		}
		if(range_check(0, 50, 11, shapes)!=0) {std::cout<<"Найден элемент, которого нет изначально.\n"; return false;}
		
		x = GenerationPentagram(11);
		shapes.push_back(x);
		if(range_check(0, 51, 11, shapes)!=1) {std::cout<<"Не найдена фигура пентограмма.\n"; return false;}
		shapes.erase(shapes.end()-1);	
		
		x = GenerationRectangle(11);
		shapes.push_back(x);
		if(range_check(0, 51, 11, shapes)!=1) {std::cout<<"Не найдена фигура прямоугольник.\n"; return false;}
		shapes.erase(shapes.end()-1);	
		
		x = GenerationPentagon(11);
		shapes.push_back(x);
		if(range_check(0, 51, 11, shapes)!=1) {std::cout<<"Не найдена фигура пятиугольник.\n"; return false;}
	}

	return true;
}

bool test2()
{
	stepik::vector<stepik::shared_ptr<Shapes>> shapes;
	unsigned size = 30;
		stepik::vector<stepik::shared_ptr<Shapes>> copy_shapes;
		stepik::shared_ptr<Shapes> x;
		for (unsigned i = 0; i < size; i++)
		{
			int k = rand() % 3 + 1;
			switch (k)
			{
			case 1:
				x = GenerationPentagram(1);
				break;
			case 2:
				x = GenerationRectangle(1);
				break;
			case 3:
				x = GenerationPentagon(1);
				break;
			}
			shapes.push_back(x);
		}
		x = GenerationPentagram(5);
		shapes.push_back(x);
		copy_shapes = copy(5, shapes);
		if (copy_shapes.size() != shapes.size()) {std::cout<<"Найдено больше 2-x элементов, удовлетворяющих условию, хотя он 1.\n"; return false;}
	return true;
}

bool test3()
{
	stepik::vector<stepik::shared_ptr<Shapes>> shapes;
	stepik::vector<stepik::shared_ptr<Shapes>> copy_shapes;
	
	unsigned size = 20;
	
	for (int n=0; n<100; n++)
	{
		for (unsigned i = 0; i < size; i++)
		{
			stepik::shared_ptr<Shapes> x;
			int k = rand() % 3 + 1;
			switch (k)
			{
			case 1:
				x = GenerationPentagram(5);
				break;
			case 2:
				x = GenerationRectangle(5);
				break;
			case 3:
				x = GenerationPentagon(5);
				break;
			}
			shapes.push_back(x);
		}
		copy_shapes = copy(5, shapes);
		if (copy_shapes.size() != 1) {std::cout<<"Есть элементы не удовлетворяющие условию, хотя их не должно быть.\n"; return false;}
	}
	return true;
}

bool test4()
{
	stepik::vector<stepik::shared_ptr<Shapes>> shapes;
	stepik::vector<stepik::shared_ptr<Shapes>> copy_shapes;
	
	unsigned size = 20;
	
	for (int n=0; n<100; n++)
	{
		for (unsigned i = 0; i < size; i++)
		{
			stepik::shared_ptr<Shapes> x;
			int k = rand() % 3 + 1;
			switch (k)
			{
			case 1:
				x = GenerationPentagram(1);
				break;
			case 2:
				x = GenerationRectangle(1);
				break;
			case 3:
				x = GenerationPentagon(1);
				break;
			}
			shapes.push_back(x);
		}
		copy_shapes = copy(5, shapes);
		if (copy_shapes.size() < shapes.size()) {std::cout<<"Есть элементы удовлетворяющие условию, хотя дне олжны быть.\n"; return false;}
	}
	return true;
}


void test5()
{
	stepik::vector<stepik::shared_ptr<Shapes>> shapes;
	stepik::vector<stepik::shared_ptr<Shapes>> copy_shapes;
	
	unsigned size = 10;
	
	for (unsigned i = 0; i < size; i++)
		{
			stepik::shared_ptr<Shapes> x;
			int k = rand() % 3 + 1;
			switch (k)
			{
			case 1:
				x = GenerationPentagram(0);
				break;
			case 2:
				x = GenerationRectangle(0);
				break;
			case 3:
				x = GenerationPentagon(0);
				break;
			}
			shapes.push_back(x);
		}
	
	for (int i = 0; i < shapes.size(); i++)
	{
		std::cout << "i="<< i+1 << "\n";
		shapes[i]->Print();		
		std::cout << "\n";			
	}
	 
	std::cout<<range_check(0, 10, 5, shapes)<< "\n";	
	
	copy_shapes = copy(5, shapes);
	
	std::cout << "Скопированные:\n";
	
	for (int i = 0; i < copy_shapes.size(); i++)
	{
		std::cout << "i="<< i+1 << "\n";
		copy_shapes[i]->Print();		
		std::cout << "\n";			
	}
}