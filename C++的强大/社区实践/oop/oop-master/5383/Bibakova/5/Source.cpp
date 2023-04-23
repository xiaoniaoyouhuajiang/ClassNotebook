#include <iostream>
#include <functional>

#include "vector.h"
#include "sharedptr.hpp"
#include "shape.hpp"
#include "Circle.hpp"
#include "Pentagon.hpp"
#include "RegularPentagon.hpp"
#include "CreatorRand.h"
#include "CompFunctions.hpp"

using namespace std;

int main()
{
	const int SHAPECOUNT = 6;

	srand(time(NULL));

	rabid::vector < rabid::shared_ptr< Shape > > ofShapes = rabid::generateRandomShapes(SHAPECOUNT);

	cout << "SOURCE VECTOR: " << endl;
	for (auto& i : ofShapes)
	{
		cout << *i;
	}

	rabid::shared_ptr< Shape > shapeToInsert;
	rabid::shared_ptr< Shape > shapeToFind;

	shapeToFind = ofShapes[3]; //ãàğàíòèğîâàííî íàéäåò 
	shapeToInsert = (rabid::shared_ptr< Shape >)new Circle({ 0, 0 }, 30, "I AM A REPLACEMENT");
	
	const auto lamda = [shapeToFind](const Shape& s) { return shapeToFind.get()->equalÎxProjectionLength(s); };

	cout << endl << "FIRST FOUND SHAPE: " << endl << *findShape(ofShapes, lamda);

	change(ofShapes, shapeToInsert, lamda);

	cout << "VECTOR AFTER REPLACEMENT: " << endl;
	for (auto& i : ofShapes)
	{
		cout << *i;
	}

	return 0;
};



