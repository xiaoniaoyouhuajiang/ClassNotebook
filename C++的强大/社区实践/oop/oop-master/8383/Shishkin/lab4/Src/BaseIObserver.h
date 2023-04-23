//#pragma once
#ifndef BASEIOBSERVER_H
#define BASEIOBSERVER_H

#include <iostream>
#include <vector>

class Subject;

class IObserver {
public:
	virtual ~IObserver() = default;
	virtual void updateNotify(Subject*) = 0;
};

#endif