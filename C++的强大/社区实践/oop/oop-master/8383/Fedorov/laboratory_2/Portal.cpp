#include "Portal.h"


Portal::Portal(GameField* field, int x, int y)
   : nextPlace(nullptr)
{
    character = PORTAL_CHARACTER;
    setPosition(field, x, y);
}





void Portal::updateState(){
     /* ... */
}


void Portal::addPlace(int x, int y){
   if (nextPlace == nullptr)
       nextPlace = new NextPlace;
   nextPlace->newX = x;
   nextPlace->newY = y;
}


Portal::~Portal()
{
     if (nextPlace)
         delete nextPlace;
}
