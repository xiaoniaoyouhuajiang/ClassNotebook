#ifndef REALLANDSCAPE_H
#define REALLANDSCAPE_H
#include "landscape.h"
#include "forest.h"
#include "mountain.h"
#include "river.h"
#include "iostream"
using namespace std;
class Proxy: public Landscape{
private:
    Landscape* natureObj;
    bool checkAccess();
    void logAccess();
public:
    string getLandscapeType();
    LandscapeType getLandscapeTypeEnum();
    bool canStand();
    ~Proxy();
    Proxy(Landscape*);
};


#endif
