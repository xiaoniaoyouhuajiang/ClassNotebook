#include "Landscape.h"

int Landscape::getColor() {
	return color;
}

int Landscape::getType() {
	return type;
}

Grass::Grass(int view) {
	this->type = 1;
	this->view = view;
	if(view == 1) this->color = 111;	//цвет ландшафта по умолчанию
	else this->color = 47;
}

int Grass::getView() {
	return view;
}

Lake::Lake() {
	this->type = 2;
	this->color = 191;
}

ritualCircle::ritualCircle() {
	this->type = 3;
	this->color = 79;
}

Pit::Pit() {
	this->type = 4;
	this->color = 15;
}