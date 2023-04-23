#pragma once

#include <vector>

class UnitNum {
public:
	void setUnitNum(int i);
	int getUnitNum();
	
private:
	int unitNum;
};

class FlyweightUnitFactory {
public:
	UnitNum* getUnitNum(int num);

private:
	std::vector<UnitNum*> units;

};