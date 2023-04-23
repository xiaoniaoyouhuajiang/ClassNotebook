#include <iostream>
#include <algorithm>
#include "vector.h"
#include "Shared_ptr.h"
#include "Shape.h"
#include "round.h"
#include "RegPentagon.h"
#include "Pentagon.h"
#include <functional>

using namespace std;
using namespace stepik;

const int diapason = 15;

int random(int fMin = -diapason, int fMax = diapason)
 {
	int f = (int)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
	}

std::vector< shared_ptr<Shape>> generator() {
	std::vector<shared_ptr<Shape>> array1;
	for (int i = 0; i < 1000; ++i) {
	int x;
		x = rand() % 3;
	
			switch (x) {
			
				case 0: {
				array1.push_back(shared_ptr<Shape>
					(new Round(random(0), Point(random(), random()), Color(rand() % 250, rand() % 250, rand() % 250))));
				break;
			}
			
				case 1: {
				array1.push_back(shared_ptr<Shape>
					(new Pentagon(Point(random(), random()), Point(random(), random()), Point(random(), random()), Point(random(), random()), Point(random(), random()), Color(rand() % 250, rand() % 250, rand() % 250))));
				break;
				}
			
				case 2: {
				array1.push_back(shared_ptr<Shape>
					(new RegPentagon(Point(random(), random()), Point(random(), random()), Color(rand() % 250, rand() % 250, rand() % 250))));
				break;
				}
		}
	}
	return array1;
}

bool predicate(const stepik::shared_ptr<Shape> &b) {     //предикат
	Shape* a = new Round(10, Point(1, 1), Color(1, 0, 2));
	bool r = (*b).isInsideOfAnother(*a);
	delete a;
	return r;
}

void printVector(std::vector< shared_ptr<Shape> > &vector_)       //фугкция печати вектора
 {
	for (auto re = vector_.begin(); re != vector_.end(); re++)
		 {
		(*re)->print(std::cout);
		}
 }

int main() {
	
		setlocale(0, "Rus");

		shared_ptr<Shape> shared_shape1(new Round(10, Point(1, 1), Color(1, 0, 2)));
		shared_ptr<Shape> shared_shape2(new Round(15, Point(11, 1), Color(1, 0, 2)));
	    shared_ptr<Shape> shared_shape3(new Round(13, Point(10, 20), Color(1, 1, 2)));
		shared_ptr<Shape> shared_shape4(new Round(11, Point(50, 10), Color(1, 4, 2)));
		shared_ptr<Shape> shared_shape5(new Round(12, Point(10, 10), Color(2, 0, 2)));

		std::vector<shared_ptr<Shape>> vec;
		vec.push_back(shared_ptr<Shape>(shared_shape1));
		vec.push_back(shared_ptr<Shape>(shared_shape2));
		vec.push_back(shared_ptr<Shape>(shared_shape3));
		vec.push_back(shared_ptr<Shape>(shared_shape4));
		vec.push_back(shared_ptr<Shape>(shared_shape5));


	//Поиск первого элемента удовлетворяющего определенному критерию (Немодифициующий алгоритм)
		std::cout << std::endl << "1) Unmodify Algorithm: " << std::endl;
		auto p = find_if(vec.begin(), vec.end(), predicate);

		if (p == vec.end()) {
			cout << "Item not found." << endl << endl;
		}
		else {
		   cout << "Item found. "<< endl ;
		}

		std::vector<shared_ptr<Shape>> array_ = generator();

		std::cout << std::endl << "2) Unmodify Algorithm: " << std::endl;    //для сгенерированного вектора
		auto it = find_if(array_.begin(), array_.end(), predicate);

		if (it == array_.end()) {
			cout <<  "Item not found." << endl << endl;
		}
		else {
		    cout << "Item found. "<< endl ;
		}

		cout << "------------------------------------------------ " << endl << endl;
		
	//Заменить элементы, соответствующие критерию другим значеием
		cout << "Modify Algorithm: " << endl;
		cout << endl << "The original vector is: " << endl;
		printVector(vec);
		std::replace_if(vec.begin(), vec.end(), predicate, shared_shape3);
		cout << endl << "The vector with a value 'shared_shape3' replacing those: " << endl ;
		printVector(vec);

	system("pause");
	return 0;
	
}
