#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "vector.hpp"
#include "shared_ptr.hpp"
#include "Shape.hpp"
#include "Ellipse.hpp"
#include "Circle.hpp"
#include "Curve.hpp"
#include <cstdlib>  //rand,srand
#include <ctime>
#include <cmath>
 

double random(double min, double max);

std::string getColour(int m);

//Разделение на диапазона на две группы
void Partition(const my_space::vector<my_space::shared_ptr<Shape>>& vector,
			   my_space::vector<my_space::shared_ptr<Shape>>& first_group,
			   my_space::vector<my_space::shared_ptr<Shape>>& second_group,
			   size_t pos1, size_t pos2);

//Печать 2 групп
void PrintGroups(const my_space::vector<my_space::shared_ptr<Shape>>& first_group,
			     const my_space::vector<my_space::shared_ptr<Shape>>& second_group);

bool Unmodified(const my_space::vector<my_space::shared_ptr<Shape>>& first_group,
			    const my_space::vector<my_space::shared_ptr<Shape>>& second_group);				 

void PrintInfoAbout(const my_space::vector<my_space::shared_ptr<Shape>>& vector,
					my_space::vector<my_space::shared_ptr<Shape>>& first_group,
					my_space::vector<my_space::shared_ptr<Shape>>& second_group,
					size_t pos1, size_t pos2);
				
void PrintVectorOfShapes(const my_space::vector<my_space::shared_ptr<Shape>>& vector);

my_space::vector<my_space::shared_ptr<Shape>> FillContainerWithRandShapes(size_t size);

my_space::vector<my_space::shared_ptr<Shape>> Modified(my_space::vector<my_space::shared_ptr<Shape>>& vector,
													   const my_space::vector<my_space::shared_ptr<Shape>>& first_group);

//Проверка двух неупорядоченных диапазонов на равенство по определенному критерию.
/*bool Unmodified(const my_space::vector<my_space::shared_ptr<Shape>>& vec,
        size_t pos1_1, size_t pos1_2, size_t pos2_1, size_t pos2_2);

void PrintInfoAboutEq(const my_space::vector<my_space::shared_ptr<Shape>>& vec,
        size_t pos1_1, size_t pos1_2, size_t pos2_1, size_t pos2_2);

//Проверка разделен ли диапазон на две группы по заданному критерию.

//Заменить элементы, соответствующие критерию, копируя весь диапазон.

//Удалить элементы, удовлетворяющие заданному критерию.
void Modified(my_space::vector<my_space::shared_ptr<Shape>>& vec);*/

#endif