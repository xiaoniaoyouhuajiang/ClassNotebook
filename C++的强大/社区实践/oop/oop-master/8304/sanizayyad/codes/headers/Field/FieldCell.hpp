#ifndef FieldCell_hpp
#define FieldCell_hpp

#include "unit.hpp"
#include "neutralobject.hpp"
#include "landscape.hpp"
#include "proxylandscape.hpp"
#include "noobject.hpp"

#include <stdio.h>
#include <memory>


class FieldCell
{
public:
    explicit FieldCell();

    FieldCell(const FieldCell& cell);
    FieldCell(FieldCell&& cell);
    FieldCell& operator=(const FieldCell& cell);
    FieldCell& operator=(FieldCell&& cell);

    void addUnit(std::shared_ptr<unit::Unit> unit);
    void deleteUnit();
    std::shared_ptr<unit::Unit> getUnit();
    bool isEmpty() const;
//    getAbout
    
    void setNeutralObject(std::shared_ptr<NeutralObject> neutralObject);
    std::shared_ptr<NeutralObject> getNeutralObject() const;
    void deleteNeutralObject();

    void setLandscape(std::shared_ptr<Landscape> landscape);
    std::shared_ptr<Landscape> getLandscape() const;
    
    
private:
    void copy(const FieldCell& fieldCell);
    void move(FieldCell& fieldCell);


private:
    std::shared_ptr<unit::Unit> unit;
    std::shared_ptr<NeutralObject> neutralObject;
    std::shared_ptr<Landscape> landscape;
    bool empty;
    
};


#endif /* FieldCell_hpp */
