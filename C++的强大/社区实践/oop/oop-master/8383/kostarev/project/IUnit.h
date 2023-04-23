#ifndef OOP1_IUNIT_H
#define OOP1_IUNIT_H

#include "Naming.h"

class IUnit{
public:
    virtual TypeOfBuild typeOfBuild() = 0;
};

class Building: public IUnit{
private:
    int saldo;
    int energy;
    int water;
    int eat;
public:
    int getSaldo();
    int getEnergy();
    int getWater();
    int getEat();
    void setSaldo(int n);
    void setEnergy(int n);
    void setWater(int n);
    void setEat(int n);
};

class Apartment: public Building{
private:
    int workmans;
    int students;
    int kids;
public:
    int getPopulation();
    int getWorkmans();
    int getKids();
    int getStudents();
    void setWorkmans(int n);
    void setKids(int n);
    void setStudents(int n);
};

class Production: public Building{
private:
    int vacancy;
public:
    int getVacancy();
    void setVacancy(int n);
};

class Services: public Building{
};

#endif //OOP1_IUNIT_H
