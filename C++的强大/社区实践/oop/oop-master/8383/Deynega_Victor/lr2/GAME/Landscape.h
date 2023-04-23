#pragma once


class Landscape {
public:
	virtual int getType() = 0;
	Landscape();
};

class Mountain : public Landscape {
public:
	int getType();
	Mountain();
};

class Lake : public Landscape {
public:
	int getType();
	Lake();
};

class  Plain : public Landscape {
public:
	int getType();
	Plain();
};