// Figure.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "IsoscelesTriangle.h"
#include "RightTriangle.h"
#include "Quadrate.h"


int main()
{
	Shape *tri2 = new RightTriangle(-1, 2, -1, 0, 3, 0, Color(155, 24, 40));
	Shape *quad = new Quadrate(-4, -4, -4, 0, 0, 0, 0, -4, Color(155, 24, 40));
	Shape *btri = new RightTriangle(0, 0, 0, 4, 8, 0, Color(155, 24, 40));
	Shape *squad = new Quadrate(1, 1, 1, 2, 2, 2, 2, 1, Color(155, 24, 40));
	Shape *tri = new IsoscelesTriangle(-0.5, 0.5, 0, 1, 0.5, 0.5, Color(155, 24, 40));
	tri2->Scale(0);
	tri2->Move(0, 0);
	cout << *tri2;
	cout << *quad;
	cout << *btri;
	//cout << *tri;*/
	//bool res = tri2->IsInsideOfAnother(*quad);
	/*bool res = squad->IsInsideOfAnother(*btri);
	cout << res << endl;*/
	system("pause");
	return 0;
}

//