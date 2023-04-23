#pragma once
#include "Unit.h"
#include "Iterator.h"

class Field {

public:

	int h;
	int w;
	int cur;
	int qmax;
	Unit*** field;

	Field();
	Field(int max, int _h, int  _w);
	Field(const Field& f);
	Field(Field&& f);
	Field& operator =  (const Field& f);
	Field& operator =  (const Field&& f);
	void AddObj(Unit* a, int x, int y);
	void RemObj(Unit *a, int x, int y);
	void Moving(Unit* a, int posx, int posy, int dx, int dy) ;
	Field* CopyField(Field* a) ;
	void SetUnit(Unit* a, int b, int c) ;
	void PrintField();
	Iterator* getIterator() const;
	~Field();
	
};
