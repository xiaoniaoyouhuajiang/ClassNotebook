#include "Lab5.h"
#include "StepVector.h"
#include <locale>

//алгоритмы пришлось вынести в отдельные функции
void my_all_of(stepik::vector< stepik::shared_ptr<Shape> > bad_vector) {
	std::cout << "Немодифицирующий" << std:: endl;
	if (std::all_of(bad_vector.begin(), bad_vector.end(), predicate)) {
		std::cout << "Все элементы данного контейнера имеют общую сторону" << std::endl;
	}
	else {
		std::cout << "Не все элементы данного контейнера имеют общую сторону" << std::endl;
	}

}
stepik::vector< stepik::shared_ptr<Shape> > my_replace_if (stepik::vector< stepik::shared_ptr<Shape> > bad_vector){
	//Заменим все элементы, поподающие под предикат, на квадрат. 
	std::vector<Dot> my_square = { Dot(1, 1), Dot(1, 3), Dot(3, 3), Dot(3, 1) }; // Тот самый квадрат
	for (int i = 0; i < bad_vector.size(); i++) {
		std::cout << *bad_vector[i];
	}
	stepik::vector< stepik::shared_ptr<Shape> > new_vector = bad_vector;
std::replace_copy_if(bad_vector.begin(), bad_vector.end(), new_vector.begin(),
	predicate, my_square);
	for (int i = 0; i < new_vector.size(); i++) {
		std::cout<<*new_vector[i];
	}
}
int main() {
	setlocale(LC_ALL, "");
	//Алгоритмы из моего задания имеются в <algorithm>

//******* Проверка что все элементы диапазона удовлетворяют определенному критерию. ********

	//Генерируем случайные фигуры в количестве 1000 шт.
	stepik::vector< stepik::shared_ptr<Shape> > shapes = generate_container(1000);

	//Проверяем, выполним ли предикат для всех элементов контейнера. 
	if (std::all_of(shapes.begin(), shapes.end(), predicate)) {
		std::cout << "Все элементы данного контейнера имеют общую сторону" <<std::endl;
	}
	else {
		std::cout << "Не все элементы данного контейнера имеют общую сторону" << std::endl;
	}

//******* Заменить элементы, соответствующие критерию, копируя весь диапазон. *******


	stepik::vector< stepik::shared_ptr<Shape> > new_shapes(1000);// новый контейнер куда скопируется


	//ручные тесты

	Shape *sq1 = new Square({ Dot(1, 1), Dot(1, 3), Dot(3, 3), Dot(3, 1) }, Color());
	Shape *sq2 = new Square({ Dot(3, 1), Dot(3, 3), Dot(5,3), Dot(5, 1) }, Color());

	Shape *tr1 = new Trapezium({ Dot(0, 0), Dot(2, 2), Dot(5, 2), Dot(7, 0) }, Color());
	Shape *tr2 = new Trapezium({ Dot(-3, 0), Dot(-1, 3), Dot(1, 3), Dot(3, 0) }, Color());

	Shape *rh1 = new Rhombus({ Dot(1, 1), Dot(2, 1 + sqrt(3)), Dot(4, 1 + sqrt(3)), Dot(3, 1) }, Color());
	Shape *rh2 = new Rhombus({ Dot(3, 1), Dot(4, 1 + sqrt(3)), Dot(6, 1 + sqrt(3)), Dot(5, 1) }, Color());

	
	stepik::vector< stepik::shared_ptr<Shape> > bad_vector;
	bad_vector.push_back(stepik::shared_ptr<Shape>(sq1));
	bad_vector.push_back(stepik::shared_ptr<Shape>(sq2));
	bad_vector.push_back(stepik::shared_ptr<Shape>(tr1));
	bad_vector.push_back(stepik::shared_ptr<Shape>(tr2));
	bad_vector.push_back(stepik::shared_ptr<Shape>(rh1));
	bad_vector.push_back(stepik::shared_ptr<Shape>(rh2));

	my_all_of(bad_vector);
	my_replace_if(bad_vector);

	Shape *sq1 = new Square({ Dot(0, 0), Dot(0, 5), Dot(5, 5), Dot(5, 0) }, Color());
	Shape *tr1 = new Trapezium({ Dot(0, 5), Dot(2, 3), Dot(3, 3), Dot(5, 5) }, Color());
	Shape *tr2 = new Trapezium({ Dot(0, 5), Dot(2, 7), Dot(3, 7), Dot(5, 5) }, Color());

	stepik::vector< stepik::shared_ptr<Shape> > good_vector;
	bad_vector.push_back(stepik::shared_ptr<Shape>(sq1));
	bad_vector.push_back(stepik::shared_ptr<Shape>(tr1));
	bad_vector.push_back(stepik::shared_ptr<Shape>(tr2));

	my_all_of(good_vector);
	my_replace_if(good_vector);

	system("pause");
	return 0;
}