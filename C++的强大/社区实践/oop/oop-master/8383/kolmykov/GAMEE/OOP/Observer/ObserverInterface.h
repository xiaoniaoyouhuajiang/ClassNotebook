#pragma once

class ObserverInterface
{
protected:
	int xCoord;
	int yCoord;
public:
	ObserverInterface();
	~ObserverInterface();
    virtual void update();
	virtual void updateKill();
	int getX();
	int getY();
};

