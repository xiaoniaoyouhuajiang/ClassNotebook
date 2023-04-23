#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>

#include "Base/base.h"

#include "unit.h"

#include "cell.h"
#include "NeutralObj/neutralObj.h"
#include "Landscape/proxy.h"

using namespace std;

class PlayingField : public Observer
{
public:
    PlayingField(unsigned,  unsigned, unsigned);
    PlayingField(const PlayingField&);
    PlayingField(PlayingField&&);
    PlayingField& operator=(const PlayingField &);
    PlayingField& operator=(PlayingField&&);
    ~PlayingField();

    unsigned getWidth() const;

    unsigned getHeight() const;

    bool moveUnit(Unit*, int, int);

    void setMoveMediator(MoveMediator*);

    unsigned getMaxItems() const;

    bool isCellFreeForUnit(size_t x, size_t y);
    bool addUnit(Unit*, unsigned, unsigned);
    bool deleteUnit(unsigned, unsigned);

    bool addNeutral(NeutralObj*, unsigned, unsigned);
    bool deleteNeutral(unsigned, unsigned);

    std::string getAbout(unsigned x, unsigned y);
    Cell* getCell(unsigned x, unsigned y);
    Cell* findUnit(Unit *unit);

    void update(Subject *);
    void deleteUnit(Subject*);
    void addBase(Base*);


    unsigned getCountOfItems() const;

    void setCreateMediator(CreateMediator *value);

private:
    const unsigned width;
    const unsigned height;
    const unsigned maxItems;
    unsigned countOfItems;
    Cell*** items{};
    MoveMediator* moveMediator;
    CreateMediator* createMediator;
};

class PlayingFieldIterator{
public:
    PlayingFieldIterator(PlayingField*);
    PlayingFieldIterator& operator =(const PlayingFieldIterator&);
    Cell* operator ++();
    Cell* operator ++(int);
    Cell* operator ->();
private:
    unsigned curWidth;
    unsigned curHeight;
    PlayingField* playingField;
};





#endif
