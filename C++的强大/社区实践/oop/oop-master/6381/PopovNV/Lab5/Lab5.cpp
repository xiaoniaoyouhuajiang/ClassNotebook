#include "Square.h"
#include "Isosceles_triangle.h"
#include "Right_triangle.h"
#include "Shared_ptr.cpp"
#include "Vector.cpp"
#include <iostream>
#include <ctime>

typedef stepik2::vector<stepik::shared_ptr<Shape>> VecSharedPtr;

using namespace std;

void fillingShapeVector(VecSharedPtr &shape_vector){
    srand(time(0));
	for(int i = 0; i < shape_vector.size(); i++){
		switch(rand() % 3){
			case(0):{
				shape_vector[i] = stepik::shared_ptr<Square>(new Square(rand() % 100, rand() % 100, rand() % 100));
				break;
			}
			case(1):{
				shape_vector[i] = stepik::shared_ptr<Right_triangle>(new Right_triangle(rand() % 100, rand() % 100, rand() % 100, rand() % 100));
				break;
			}
			case(2):{
				shape_vector[i] = stepik::shared_ptr<Isosceles_triangle>(new Isosceles_triangle(rand() % 100, rand() % 100, rand() % 100, rand() % 180));
			}
		}
		switch(rand() % 5){
			case(0):
				(*shape_vector[i]).setColour("Black");
				break;
			case(1):
				(*shape_vector[i]).setColour("Red");
				break;
			case(2):
				(*shape_vector[i]).setColour("Blue");
				break;
			case(3):
				(*shape_vector[i]).setColour("Yellow");
				break;
			case(4):
				(*shape_vector[i]).setColour("Green");
		}
	}
}

//Поиск первого из нескольких возможных элементов по заданному критерию.
void findElem(VecSharedPtr shape_vector, double square_from, double square_to){
	for(stepik::shared_ptr <Shape>curr: shape_vector){
		if(square_from <= (*curr).square() && square_to >= (*curr).square()){
			cout << *curr;
			return;
		}
	}
	cout << "Figure with square from " << square_from << " to " << square_to << " doesn't exist\n";
}

//Скопировать элементы, удовлетворяющие критерию.
VecSharedPtr copyElems(VecSharedPtr shape_vector, double square_from, double square_to){
	VecSharedPtr copy_vector;
	for(stepik::shared_ptr <Shape>curr: shape_vector)
		if(square_from <= (*curr).square() && square_to >= (*curr).square())
			copy_vector.push_back(curr);
	return copy_vector;
}

int main(){
	VecSharedPtr shape_vector;
	// shape_vector.resize(1000);
	shape_vector.resize(10);
	cout << "-------------------------Test 1-------------------------\n";
	fillingShapeVector(shape_vector);
	double from = 500, to = 2000;
	cout << "Search first element in shape_vector with square from " << from << " to " << to << ":\n";
	findElem(shape_vector, from, to);
	VecSharedPtr copy_vector1 = copyElems(shape_vector, from, to);
	cout << "List of the Shapes:\n";
	for(auto i: shape_vector)
		cout << *i;
	cout << "List of the copy Shapes:\n";
	for(auto i: copy_vector1)
		cout << *i;
	
	cout << "-------------------------Test 2-------------------------\n";
	from = 800;
	to = 1800;
	cout << "Search first element in copy_vector with square from " << from << " to " << to << ":\n";
	findElem(copy_vector1, from, to);
	VecSharedPtr copy_vector2 = copyElems(copy_vector1, from, to);
	cout << "List of the Shapes from copy_vector:\n";
	for(auto i: copy_vector1)
		cout << *i;
	cout << "List of the copy Shapes from copy_vector:\n";
	for(auto i: copy_vector2)
		cout << *i;	
	
	cout << "-------------------------Test 3-------------------------\n";
	from = 0;
	to = 1;
	cout << "Search first element with square from " << from << " to " << to << ":\n";
	findElem(shape_vector, from, to);
	VecSharedPtr copy_vector3 = copyElems(shape_vector, from, to);
	cout << "List of the Shapes:\n";
	for(auto i: shape_vector)
		cout << *i;
	cout << "List of the copy Shapes:\n";
	for(auto i: copy_vector3)
		cout << *i;	
	return 0;
}