#pragma once
#include <iostream>
#include <ctime>

class Attribute {
protected:
	int value;

public:
	virtual void setValue(int view) = 0;
	void newSetValue(int newValue);
	int getValue();
};

class Damage : public Attribute {
public:
	Damage();

	void setValue(int view) override {
		srand(time(NULL));
		if (view == 1 || view == 3) {
			this->value = rand() % 300 + 200;  //200-500
		}
		if (view == 2 || view == 4) {
			this->value = rand() % 200 + 400;  //400-600
		}
		if (view == 5) {
			this->value = rand() % 100 + 200;  //200-300
		}
		if (view == 6) {
			this->value = 0;
		}
	}

};

class Armor : public Attribute {
public:
	Armor();

	void setValue(int view) override {
		srand(time(NULL));
		if (view == 1 || view == 3) {
			this->value = rand() % 100 + 300;  //300-400
		}
		if (view == 2 || view == 4) {
			this->value = rand() % 200 + 300;  //300-500
		}
		if (view == 5) {
			this->value = 150;
		}
		if (view == 6) {
			this->value = 50;
		}
	}

};

class Health : public Attribute {
public:
	Health();

	void setValue(int view) override {
		srand(time(NULL));
		if (view == 1 || view == 2) {
			this->value = 1000;
		}
		if (view == 3 || view == 4) {
			this->value = 900;
		}
		if (view == 5 || view == 6) {
			this->value = 200;
		}
	}

};