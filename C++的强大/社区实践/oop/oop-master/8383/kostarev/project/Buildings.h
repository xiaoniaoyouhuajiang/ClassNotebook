#ifndef OOP1_BUILDINGS_H
#define OOP1_BUILDINGS_H

#include "IUnit.h"
#include "Naming.h"

class Dacha: public Apartment{
public:
    TypeOfBuild typeOfBuild() override;
    Dacha();
};

class Hrushchovka:public Apartment{
public:
    TypeOfBuild typeOfBuild() override;
    Hrushchovka();
};

class Ferma:public Production{
public:
    TypeOfBuild typeOfBuild() override;
    Ferma();
};

class Office:public Production{
public:
    TypeOfBuild typeOfBuild() override;
    Office();
};

class Vodokanal:public Services{
public:
    TypeOfBuild typeOfBuild() override;
    Vodokanal();
};

class School:public Services{
public:
    TypeOfBuild typeOfBuild() override;
    School();
};

class Powerhouse:public Services{
public:
    TypeOfBuild typeOfBuild() override;
    Powerhouse();
};
#endif //OOP1_BUILDINGS_H
