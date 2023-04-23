#include "NullPointerMediatorInTower.h"

NullPointerMediatorInTowerException::NullPointerMediatorInTowerException(int x, int y) : x(x), y(y)
{

}


std::ostream& operator<< (std::ostream &out, const NullPointerMediatorInTowerException exeption) {
    out << "NullPointerMediatorInTower! In tower with coords " << exeption.x << " " << exeption.y;
    return out;
}
