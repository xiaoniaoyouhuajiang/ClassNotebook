#ifndef BattleField_hpp
#define BattleField_hpp

#include "FieldCell.hpp"
#include "healthobject.hpp"
#include "poisonobject.hpp"
#include "armorobject.hpp"
#include "noobject.hpp"

#include <stdio.h>
#include <iostream>
#include <memory>
#include <vector>


class BattleFieldIterator;

class BattleField
{
    friend BattleFieldIterator;
public:
    explicit BattleField(int height, int width);

    BattleField(const BattleField& BattleField);
    BattleField& operator=(const BattleField& BattleField);
    BattleField(BattleField&& BattleField);
    BattleField& operator=(BattleField&& BattleField);

    int getWidth() const;
    int getHeight() const;

    bool addUnit(std::shared_ptr<unit::Unit> unit);
    void deleteUnit(std::shared_ptr<unit::Unit> unit);
    void deleteUnitCord(Position2D position);
    
    std::shared_ptr<BattleFieldIterator> getIterator() const;

    std::shared_ptr<FieldCell> getFieldCell(const Position2D& position);
    void getFieldCellInfo(const Position2D &position);

    
private:
    void copy(const BattleField& battleField);
    void move(BattleField& battleField);
    
private:
    int height;
    int width;
    std::vector<std::vector<std::shared_ptr<FieldCell>>> battleFieldArray;

};

#endif /* BattleField_hpp */
