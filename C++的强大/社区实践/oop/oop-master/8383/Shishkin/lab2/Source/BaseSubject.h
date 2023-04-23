//#pragma once
#ifndef BASESUBJECT_H
#define BASESUBJECT_H

#include "BaseIObserver.h"

using namespace std;

class Subject {
public:
	void addObserver(IObserver*);
	void removeObserver(IObserver*);
	void notify();

protected:
	vector<IObserver*> observers;
};

#endif