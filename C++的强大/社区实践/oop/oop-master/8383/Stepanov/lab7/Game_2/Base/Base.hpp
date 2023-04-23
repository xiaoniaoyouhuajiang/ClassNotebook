//
//  Base.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 20.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef Base_hpp
#define Base_hpp

#include <vector>

#include "Field.hpp"
#include "IObserver.hpp"
#include "Unit.hpp"
#include "ConcreteUnitRunner.hpp"
#include "ConcreteUnitShooter.hpp"
#include "ConcreteUnitSmoker.hpp"
#include "FlyweightUnitFactory.hpp"
#include "ConcreteHealthPound.hpp"
#include "ConcreteBoxWithArmor.hpp"
#include "ConcretePowerChemical.hpp"
#include "ConcreteWorkbenchForWeapons.hpp"
#include "ProxyLog.hpp"
#include "Adapter.hpp"

#include "BaseSnapshot.hpp"

#include "ErrorSpawn.hpp"

class Field;


class Base : public IObserver {
    
    Unit * units[9] = {nullptr};
    
    std::vector <Unit *> toDelet;
    FlyweightUnitFactory flyFactory;
    
    int numberUnit = 0;
    int countUnit = 0;
    int x = 0;
    int y = 0;
    int concretCountUnit[3] = {0, 0, 0};
    Field *field;
    std::string name;
    
    ProxyLog *log;
    Adapter adapter;
    
    bool isProtect = true;
    
    IObserver *game;
    

    Unit* createUnit(int whatUnit, int uniqNum);   // функция создает юнита

public:
    
    ~Base ();
    Base(IObserver *game);
    
    void Update(Unit *unit) override;               // оповещание о том, что юнит умер


    std::string getName ();                              // возвращает имя базы
    
    Base (int i, int x, int y, Field *field, ProxyLog *log, bool isProtect, IObserver *game);
    bool setFirstUnits (Field *field);              // ставит юнитов на поле при старте
    bool setNeutralObjects (Field *field);          // ставит нейтральные объекты на поле при старте

    Unit* getUnit (int i);                          // возвращает юнита с индексом i из массива юнитов

    Unit* findUnit (std::string name);              // ищет юнита в массиве юнитов
    
    bool spawn (char typeOfUnit, bool isProtected); // спавнит нового юнита
    
    BaseSnapshot* saveBase ();
    
    void restore (BaseSnapshot* snap, ProxyLog *log, Field *field);

};


#endif /* Base_hpp */
