#pragma once
#include "stdafx.h"
#include "Color.h"

using namespace std;

Color::Color(int rs, int gs, int bs): r(rs), g(gs), b(bs) { }

void Color::Rand(){
    r = rand() % 255;
    g = rand() % 255;
    b = rand() % 255;
}

void Color::Enter(){
    cout << "Enter R,G,B: ";
    cin >> r >> g >> b;
}

ostream & operator<<(ostream& os, Color& col)
{
	os << "R: " << col.R() << "; G: " << col.G() << "; B:" << col.B();
	return os;
}
