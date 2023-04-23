#include "color.h"

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

Color& Color::operator= (const Color & c){
    r = c.R(); g = c.G(); b = c.B();
}

ostream & operator<<(ostream& os, Color& col)
{
	os << "R: " << col.R() << "; G: " << col.G() << "; B:" << col.B();
	return os;
}

bool operator==(const Color & a, const Color & b){
    return ((a.R()==b.R()) && (a.G()==b.G()) && (a.B()==b.B()));
}