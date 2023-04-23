#include "Buildings.h"
#include <cstdlib>

Dacha::Dacha(){
    setWorkmans(rand() % 4 + 1);
    setStudents(rand() % 3);
    setKids(rand() % 3);
    setSaldo(getPopulation()*3);
    setEnergy(-(getPopulation()*5));
    setWater(-(getPopulation()*4));
    setEat(-(getPopulation()*2));
}

TypeOfBuild Dacha::typeOfBuild() {
    return DACHA;
}

Hrushchovka::Hrushchovka(){
    setWorkmans(rand() % 50 + 50);
    setStudents(rand() % 30 + 10);
    setKids(rand() % 10 + 5);
    setSaldo(getPopulation()*3);
    setEnergy(-(getPopulation()*5));
    setWater(-(getPopulation()*4));
    setEat(-(getPopulation()*3));
}

TypeOfBuild Hrushchovka::typeOfBuild() {
    return HRUSHCHOVKA;
}

Ferma::Ferma(){
    setSaldo(100);
    setVacancy(rand() % 15 + 5);
    setEat(getVacancy()*2);
    setEnergy(-(getVacancy()*3));
    setWater(-(getVacancy()*4));
}

TypeOfBuild Ferma::typeOfBuild() {
    return FERMA;
}

Office::Office(){
    setSaldo(1000);
    setVacancy(rand() % 70 + 30);
    setEat(-(getVacancy()*2));
    setEnergy(-(getVacancy()*3));
    setWater(-(getVacancy()*4));
}

TypeOfBuild Office::typeOfBuild() {
    return OFFICE;
}

Vodokanal::Vodokanal(){
    setSaldo(-50);
    setEat(0);
    setWater(rand() % 1300 + 200);
    setEnergy(0);
}

TypeOfBuild Vodokanal::typeOfBuild() {
    return VODOKANAL;
}

School::School() {
    setSaldo(-200);
    setEat(-100);
    setWater(-1000);
    setEnergy(-100);
}

TypeOfBuild School::typeOfBuild() {
    return SCHOOL;
}

Powerhouse::Powerhouse() {
    setSaldo(-50);
    setEat(0);
    setWater(0);
    setEnergy(rand() % 1300 + 200);
}

TypeOfBuild Powerhouse::typeOfBuild() {
    return POWERHOUSE;
}
