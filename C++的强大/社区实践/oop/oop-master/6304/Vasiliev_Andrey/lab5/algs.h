#ifndef ALGS_H
#define ALGS_H

#include "vector.h"
#include "shape.h"
#include "shared.h"

namespace stepik {

typedef shared_ptr<Shape> shapePointer;

typedef vector<shapePointer>::const_iterator sh_const_iterator;


//Заполнение вектора size случайными фигурами
void fillRandomly(stepik::vector<shapePointer> & l, size_t size, size_t top_marg = 10)
{
	for(unsigned int i = 0; i < size; i ++)
	{
		int what = rand()%3;

		if(what==0)
			l.push_back(shapePointer(new IsosTriangle(rand()%top_marg,rand()%top_marg,
													   rand()%top_marg + 1,rand()%top_marg + 1)));
		else if(what==1)
			l.push_back(shapePointer(new RightTriangle(rand()%top_marg,rand()%top_marg
														,rand()%top_marg + 1,rand()%top_marg + 1)));
		else
			l.push_back(shapePointer(new Square(rand()%top_marg,rand()%top_marg,rand()%top_marg + 1)));

	}
}
//*******************************************************


//печать диапазона из массива
void print(sh_const_iterator first, sh_const_iterator end)
{
		cout <<"number of elements "<< end - first <<'\n';
	while(first != end)
		std::cout << **first++<<"\n";
}

//перегруженная функция - печать всего массива
void print(stepik::vector<shapePointer> & l)
{
	print(l.begin(),l.end());
}
//********************************************************


//печать периметров фигур из заданного диапазона
void printP(sh_const_iterator first, sh_const_iterator end)
{
		cout <<"number of elements "<< end - first <<'\n'
			<<"Perimetrs of figures:\n";
	while(first != end)
		std::cout << ((shapePointer*)first++)->get()->P() <<"\n";
}

//перегруженная функция - печать всего массива
void printP(stepik::vector<shapePointer> & l)
{
	printP(l.begin(),l.end());
}
//*******************************************************


//печать площадей фигур из заданного диапазона
void printS(sh_const_iterator first, sh_const_iterator end)
{
		cout <<"number of elements "<< end - first <<'\n'
			<< "Areas of figures:\n";
	while(first != end)
		std::cout << ((shapePointer*)first++)->get()->S() <<"\n";
}

//перегруженная функция - печать всего массива
void printS(stepik::vector<shapePointer> & l)
{
	printS(l.begin(),l.end());
}
//********************************************************


//Немодифицирующий алгоритм

//Функция для поиска первого элемента в диапазоне [first,end)
//по критерию func.

//func - унарный предикат, который возвращает true для искомого элемента.
//Может являться предикатом, указателем на функцию-компоратор или лямбда-выражением.

//Если элемент найден, то возвращается итератор на него,
//если элемент не найден - возвращается end
template <class iterator_type>
iterator_type findFirst(iterator_type first, iterator_type end, std::function<bool(const void*)> func = [](){return true;})
{
	while(first != end)
	{
		if(func(first))
		{
			cout <<"\tElement is found!\n";
			return first;
		}
		++first;
	}
	cout << "\tElement is not found!\n";
	return end;
}
//****************************************************************


//Модифицирующий алгоритм

//Функция для разделения диапазона [first,end) на две части
//по критерию func. Все элементы, удовлетворяющие критерию,
//будут перемещены в конец данного диапазона.

//func - унарный предикат, который возвращает true для искомого элемента.
//Может являться предикатом, указателем на функцию-компоратор или лямбда-выражением.

//Если в диапазоне нет элементов, удовлетворяющих критерию - возвращается end,
//иначе возвращается итератор на первый элемент из второго диапазона
template <class iterator_type>
iterator_type divide(iterator_type first, iterator_type end,std::function<bool(const void*)> func)
{
	iterator_type save = first;
	iterator_type ret  = end;

	while(first != end-1)
	{	//элемент по критерию, но следующий - нет.
		if(func(first) && !func(first+1) )
		{
			ret = first + 1;
			std::swap(*first,*ret);
			first = save;
			continue;
		}
		++first;
	}
	return ret ;
}

} //namespace stepik


#endif // ALGS_H
