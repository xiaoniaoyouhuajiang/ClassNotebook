#include "algorithms.hpp"

//печать вектора
void PrintVectorOfShapes(const my_space::vector<my_space::shared_ptr<Shape>>& vector) {
        for(const auto& item : vector)
            std::cout << *item;
}

// Функция, генерирующая случайное действительное число от min до max
double random(double min, double max)
{
    return (double)(rand())/RAND_MAX*(max - min) + min;
}

std::string getColour(int m){
	if (m == 1)			return "Red";
	else if (m == 2)	return "Black";
	else if (m == 3)	return "Yellow";
	else if (m == 4)	return "Blue";
	else if (m == 5)	return "Green";
}

//заполнение вектора
my_space::vector<my_space::shared_ptr<Shape>> FillContainerWithRandShapes(size_t size) {
    my_space::vector<my_space::shared_ptr<Shape>> my_container(size);
    srand(time(nullptr));
    int k, m;
    for(auto& item : my_container) {
        k = rand()%3 + 1;
		m = rand()%5 + 1;
		double x0 = random(-50, 50);
		double y0 = random(-50, 50);//координаты центра
		double Angle = random(0, 360);//угол поворота в градусах
		double R1 = random(1,10);//длина первого радиуса для эллипса
		double R2 = random(1,10);//длина второго радиуса для эллипса
		double Angle1 = random(0, 360); //угол между первой стороной дуги и осью ОХ для дуги
		double Angle2 = random(0, 360); //угол между второй стороной дуги и осью ОХ для дуги
		double R = random(1,10); //длина радиуса для круга и дуги
        if(k == 1)
			item = my_space::shared_ptr<Shape>
            (new Ellipse (x0, y0, R1, R2, getColour(m)));
        else if(k == 2)
            item = my_space::shared_ptr<Shape>
            (new Circle (x0, y0, R, getColour(m)));
        else if(k == 3)
            item = my_space::shared_ptr<Shape>
            (new Curve (x0, y0, R, Angle1, Angle2, getColour(m)));
    }
    return my_container;
}


//Разделение на диапазона на две группы
//Критерий: расположение ниже оси х
void Partition(const my_space::vector<my_space::shared_ptr<Shape>>& vector,
			   my_space::vector<my_space::shared_ptr<Shape>>& first_group,
			   my_space::vector<my_space::shared_ptr<Shape>>& second_group,
			   size_t pos1, size_t pos2){
	for(int i = pos1; i <= pos2; ++i){
        if ((*vector[i]).Y0 < 0)	first_group.push_back(vector[i]);
        else second_group.push_back(vector[i]);
    }
}

//печать первой и второй группы
void PrintGroups(const my_space::vector<my_space::shared_ptr<Shape>>& first_group,
			     const my_space::vector<my_space::shared_ptr<Shape>>& second_group) {
        std::cout << "First group: " << std::endl;
		for(const auto& item : first_group)
            std::cout << *item;
		std::cout << "Second group: " << std::endl;
		for(const auto& item : second_group)
            std::cout << *item;
}

//Проверка разделен ли диапазон на две группы по заданному критерию.
//критерий: расположение ниже оси Х
bool Unmodified(const my_space::vector<my_space::shared_ptr<Shape>>& first_group,
			    const my_space::vector<my_space::shared_ptr<Shape>>& second_group) {
	//std:: cout << "Size first group: " << first_group.size() << std::endl;
	//std:: cout << "Size second group: " << second_group.size() << std::endl;
	for(int i = 0; i < first_group.size(); ++i){
		if ((*first_group[i]).Y0 > 0)	return false;
	}
	for(int i = 0; i < second_group.size(); ++i){
		if ((*second_group[i]).Y0 < 0)	return false;
	}
	return true;
}

void PrintInfoAbout(const my_space::vector<my_space::shared_ptr<Shape>>& vector,
					my_space::vector<my_space::shared_ptr<Shape>>& first_group,
					my_space::vector<my_space::shared_ptr<Shape>>& second_group,
					size_t pos1, size_t pos2) {
	Partition(vector, first_group, second_group, pos1, pos2);
	PrintGroups(first_group, second_group);
	if(Unmodified(first_group, second_group)){
		std::cout << "Range : [" << pos1 << ", " << pos2 << 
		"] check passed " << std::endl;
	}
    else {
        std::cout << "Range : [" << pos1 << ", " << pos2 <<
        "] check failed " << std::endl;
	}
}

//Заменить элементы, соответствующие критерию, копируя весь диапазон.
//критерий: центр фигуры находится в центре осей [-5,5]
//заменяем на фигуры которые расположены ниже оси Х
my_space::vector<my_space::shared_ptr<Shape>> Modified(my_space::vector<my_space::shared_ptr<Shape>>& vector,
													   const my_space::vector<my_space::shared_ptr<Shape>>& first_group){
	my_space::vector<my_space::shared_ptr<Shape>> copy_container = vector;
	for(int i = 0; i < vector.size(); ++i) {
		double X = (*vector[i]).X0;
		double Y = (*vector[i]).Y0;
        if((fabs(X) <= 10) || (fabs(Y) <= 10)) {
			std::cout << "Figure NUMBER = " << (*vector[i]).NUMBER <<
			" delete, because the center in the range [-5, 5]" << std::endl;
            vector.erase(vector.begin() + i);
            i--;
        }
    }
	for(const auto& item : first_group)
		vector.push_back(item);
	return copy_container;
}
