#include "Figures.hpp"
#include "vector.cpp"
#include "shared_ptr.cpp"
#include <iostream>
#include <ctime>
#include <stdexcept>

#define OBJ_N 5 // Количество тестируемых объектов
#define X_MAX 1920 // Максимально возможное значение X положения фигуры
#define Y_MAX 1080 // Y
#define R_MAX 100 // Максимальный радиус от цента фигуры до ее вершин

using namespace std;

void generateShapes(stepik::vector<stepik::shared_ptr<Shape>>& SSPVect)
{
	srand(time(NULL));
	for (stepik::shared_ptr<Shape> &i : SSPVect)
	{
		switch (rand()%3)
		{
			case 0: // Круг
				i.reset(new Circle{});
				static_cast<Circle&>(*i).setRadius(
					static_cast<double>(rand()%R_MAX));
				break;
			case 1: // Пятиугольник
				i.reset(new Pentagon{});
				static_cast<Pentagon&>(*i).setDotsRadius({
					static_cast<double>(rand()%R_MAX),
					static_cast<double>(rand()%R_MAX),
					static_cast<double>(rand()%R_MAX),
					static_cast<double>(rand()%R_MAX),
					static_cast<double>(rand()%R_MAX)
				});
				static_cast<Pentagon&>(*i).setDotsAngle({
					static_cast<double>(rand()),
					static_cast<double>(rand()),
					static_cast<double>(rand()),
					static_cast<double>(rand()),
					static_cast<double>(rand())
				});
				break;
			case 2: // Правильный пятиугольник
				i.reset(new RegPentagon{});
				static_cast<RegPentagon&>(*i).setDotsRadius(
					static_cast<double>(rand()%R_MAX));
				break;
		}
		// Устанавливаем поля базового для всех объектов класса
		i->setPos({static_cast<double>(rand()%X_MAX),
			static_cast<double>(rand()%Y_MAX), 0});
		i->setColor({rand()%256, rand()%256, rand()%256});
		i->setAngle(rand());
	}
}

// First argument is container with shapes, second - predicate function
// Returns a shared pointer to a found element
// 	Or empty shared pointer if all elements not matching a predicate
stepik::shared_ptr<Shape> findFirstOccurence(
	const stepik::vector<stepik::shared_ptr<Shape>>& SSPVect,
	bool (*predicate)(const Shape&))
{
	for (const stepik::shared_ptr<Shape> &i : SSPVect)
	{
		if (predicate(*i))
			return i;
	}
	return stepik::shared_ptr<Shape>{nullptr};
}

// Function that sorts container(First elements are not matching predicate)
// First argument is container with shapes, last - predicate function
// Returns first element that matching a predicate.
// If there is no such elements then returns -1
stepik::shared_ptr<Shape> sort(stepik::vector<stepik::shared_ptr<Shape>>& SSPVect,
	unsigned begin, unsigned end, bool (*predicate)(const Shape&))
{
	if ((begin > SSPVect.size()) || (end > SSPVect.size()) || (end < begin))
		throw out_of_range("Bad arguments in sort function");
	// Sorting
	std::sort(SSPVect.begin()+begin, SSPVect.begin()+end,
		[predicate](const stepik::shared_ptr<Shape>& lhs,
			const stepik::shared_ptr<Shape>& rhs) -> bool
		{
			return predicate(*lhs)<predicate(*rhs);
		});
	// Searching first matching element and returning it's index if found
	for (unsigned i = begin; i < end; ++i)
		if (predicate(*SSPVect[i]))
			return SSPVect[i];
	// No matching element
	return stepik::shared_ptr<Shape>{nullptr};
}

int main()
{
	stepik::vector<stepik::shared_ptr<Shape>> SSPVect(OBJ_N);

	generateShapes(SSPVect);

	for (auto &i : SSPVect)
	{
		cout << *i << " ";
	}
	cout << endl;

	//1.  Поиск первого элемента удовлетворяющего определенному критерию.

	{
		stepik::shared_ptr<Shape> found{findFirstOccurence(SSPVect,
			[](const Shape& a)
			{
				if (a.getPos().x<500 && a.getPos().y>500) return true;
				return false;
			})};
		if (found)
			cout << "First element with x<500 and y>500 is " << found.get() << ": "
				<< endl << *found;
		else
		{
			cout << "Couldn't find element with x<500 and y>500." << endl;
		}
	}
	cout << endl;

	// 12. Отсортировать элементы диапазона так, чтобы правильный элемент находился на n-й позиции
   //  (все стоящие перед ним элементы не превосходят его, а все стоящие после - превосходят либо равны).
	// 'True' - figure is in right bottom quarter
	{
		auto tmp = sort(SSPVect, 0, SSPVect.size(),
			[](const Shape& a)
			{
				if (a.getPos().x>(X_MAX/2) && a.getPos().y>(Y_MAX/2)) return true;
				return false;
			});
		cout << "Sorting container: predicate - figure's position in the left bottom quarter." << endl;
		cout << "Sorted container: " << endl;
		for (auto &i : SSPVect)
		{
			cout << *i << " ";
		}
		cout << endl;
		if (tmp)
			cout << "First element matching predicate: " << tmp.get()
				<< endl << *(tmp);
		else
			cout << "No elements matching a predicate." << endl;
	}

	return 0;
}
