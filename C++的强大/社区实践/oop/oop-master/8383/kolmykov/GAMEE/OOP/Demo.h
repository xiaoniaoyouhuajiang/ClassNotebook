#pragma once
#include "Field.h"
#include "Tower.h"
#include "HumanWithSwordFactory.h"
#include "BitingZombyFactory.h"
#include "SmallArmorObject.h"
#include "Mediator.h"
#include "Facade.h"
#include "SpitToEnemyZombyFactory.h"
#include "HumanWithGunFactory.h"
#include "HumanOnBikeFactory.h"
#include "KamikadzeZombyFactory.h"
#include "FileLoger.h"
#include "ConsoleLoger.h"
#include "Saver.h"
#include "Loader.h"
#include <QObject>

class Demo : public QObject
{
    Q_OBJECT
public:
	Demo();
	~Demo();
	void start(bool isLoad);
signals:
    void updateSignal();
};

