#ifndef CONVERTFROMENUM_H
#define CONVERTFROMENUM_H
#include "enums.h"
#include <iostream>
using namespace std;
string convertFromEnumToLand(LandscapeType type);

string convertFromEnumToNeutral(NeutralType type);

string convertFromEnumToUnit(UnitsType type);

int convertFromNeutralToEnum(string type);

int convertFromUnitToEnum(string type);

#endif // CONVERTFROMENUM_H
