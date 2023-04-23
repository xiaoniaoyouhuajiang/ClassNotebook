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
				x = GenerationEllipse(0);
				break;
			case 2:
				x = GenerationTrapezium(0);
				break;
			case 3:
				x = GenerationPentagon(0);
				break;
			}
			shapes.push_back(x);
		}
		x = GenerationEllipse(11);
		shapes.push_back(x);
		x = GenerationTrapezium(11);
		shapes.push_back(x);
		x = GenerationPentagon(11);
		shapes.push_back(x);
		
		if(range_check(0, 50, 11, shapes)!=1) {std::cout<<"Найден элепент, которого нет изначально.\n"; return false;}
		if(range_check(0, 51, 11, shapes)!=0) {std::cout<<"Не найдена фигура эллипс.\n"; return false;}
		if(range_check(0, 52, 11, shapes)!=0) {std::cout<<"Не найдена фигура трапеция.\n"; return false;}
		if(range_check(0, 53, 11, shapes)!=0) {std::cout<<"Не найдена фигура пятиугольник.\n"; return false;}
	}

	return true;
}

bool test2()
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
				x = GenerationEllipse(0);
				break;
			case 2:
				x = GenerationTrapezium(0);
				break;
			case 3:
				x = GenerationPentagon(0);
				break;
			}
			shapes.push_back(x);
		}
		copy_shapes = copy(5, shapes);
		if (copy_shapes.size() == 0) {std::cout<<"Все эл-ты удовлетворяют условию, хотя есть и те, которые не удовлетворяют.\n"; return false;}
		if (copy_shapes.size() == shapes.size()) {std::cout<<"Все эл-ты не удовлетворяют условию, хотя есть и те, которые удовлетворяют.\n"; return false;}
	}
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
				x = GenerationEllipse(5);
				break;
			case 2:
				x = GenerationTrapezium(5);
				break;
			case 3:
				x = GenerationPentagon(5);
				break;
			}
			shapes.push_back(x);
		}
		copy_shapes = copy(5, shapes);
		if (copy_shapes.size() > 0 && copy_shapes.size() < shapes.size()) {std::cout<<"Не все эл-ты удовлетворяют условию, хотя должны все удовлетворять.\n"; return false;}
		if (copy_shapes.size() == shapes.size()) {std::cout<<"Все эл-ты не удовлетворяют условию, хотя все должны удовлетворять.\n"; return false;}
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
				x = GenerationEllipse(1);
				break;
			case 2:
				x = GenerationTrapezium(1);
				break;
			case 3:
				x = GenerationPentagon(1);
				break;
			}
			shapes.push_back(x);
		}
		copy_shapes = copy(5, shapes);
		if (copy_shapes.size() > 0 && copy_shapes.size() < shapes.size()) {std::cout<<"Не все эл-ты удовлетворяют условию, хотя должны все не удовлетворять.\n"; return false;}
		if (copy_shapes.size() == 0) {std::cout<<"Все эл-ты удовлетворяют условию, хотя все должны не удовлетворять.\n"; return false;}
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
				x = GenerationEllipse(0);
				break;
			case 2:
				x = GenerationTrapezium(0);
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
	 
	std::cout<<range_check(0, 9, 5, shapes)<< "\n";	
	
	copy_shapes = copy(5, shapes);
	
	std::cout << "Скопированные:\n";
	
	for (int i = 0; i < copy_shapes.size(); i++)
	{
		std::cout << "i="<< i+1 << "\n";
		copy_shapes[i]->Print();		
		std::cout << "\n";			
	}
}
