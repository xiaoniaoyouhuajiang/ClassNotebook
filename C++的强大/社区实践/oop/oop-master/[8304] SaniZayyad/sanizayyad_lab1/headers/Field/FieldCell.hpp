#ifndef FieldCell_hpp
#define FieldCell_hpp

#include "unit.hpp"

#include <stdio.h>
#include <memory>


class FieldCell
{
public:
    explicit FieldCell();
    ~FieldCell() = default;

    FieldCell(const FieldCell& cell);
    FieldCell(FieldCell&& cell);
    FieldCell& operator=(const FieldCell& cell);
    FieldCell& operator=(FieldCell&& cell);

    void addUnit(std::shared_ptr<Unit> unit);
    void deleteUnit();
    std::shared_ptr<Unit> getUnit();
    bool isEmpty() const;
//    getAbout

private:
    std::shared_ptr<Unit> unit;
    bool empty;
};


#endif /* FieldCell_hpp */
