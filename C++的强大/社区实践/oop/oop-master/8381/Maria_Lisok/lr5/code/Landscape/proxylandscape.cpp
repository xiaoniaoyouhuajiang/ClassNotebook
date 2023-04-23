#include "proxylandscape.h"
bool Proxy::checkAccess()
{
    cout << "Proxy: Checking access prior to firing a real request.\n";
    if(natureObj != nullptr)
        return true;
    return false;
}

void Proxy::logAccess()
{
    cout << "Proxy: Logging the time of request." << endl;
}

string Proxy::getLandscapeType()
{
    if(this->checkAccess()){
        this->logAccess();
        return natureObj->getLandscapeType();
    }
    return "there are not such type of landscape";
}

LandscapeType Proxy::getLandscapeTypeEnum()
{
    if(this->checkAccess()){
        this->logAccess();
        return natureObj->getLandscapeTypeEnum();
    }
    throw::invalid_argument("there are not such type of landscape");
}
bool Proxy::canStand()
{
    if(this->checkAccess()){
        this->logAccess();
        return natureObj->canStand();
    }
    return false;
}

Proxy::~Proxy()
{
    delete natureObj;
}

Proxy::Proxy(LandscapeType natObj)
{
    switch (natObj) {
        case FOREST:
            natureObj = new Forest();
            break;
        case RIVER:
            natureObj = new River();
            break;
        case MOUNTAIN:
            natureObj = new Mountain();
            break;
    }
}
Proxy::Proxy(Landscape* natObj): natureObj(natObj)
{
}

