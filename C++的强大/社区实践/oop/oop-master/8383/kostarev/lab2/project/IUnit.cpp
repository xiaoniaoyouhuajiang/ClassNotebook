#include "IUnit.h"

int Production::getVacancy() {
	return vacancy;
}

void Production::setVacancy(int n) {
	this->vacancy = n;
}

Builds Production::classOfBuild() {
	return PRODUCTION;
}


int Building::getSaldo() {
	return this->saldo;
}

int Building::getEnergy() {
	return this->energy;
}

int Building::getWater() {
	return this->water;
}

int Building::getEat() {
	return this->eat;
}

void Building::setSaldo(int n) {
	this->saldo = n;
}

void Building::setEnergy(int n) {
	this->energy = n;
}

void Building::setWater(int n) {
	this->water = n;
}

void Building::setEat(int n) {
	this->eat = n;
}

int Apartment::getPopulation() {
	return kids + workmans + students;
}

int Apartment::getWorkmans() {
	return workmans;
}

int Apartment::getKids() {
	return kids;
}

int Apartment::getStudents() {
	return students;
}

void Apartment::setWorkmans(int n) {
	this->workmans = n;
}

void Apartment::setKids(int n) {
	this->kids = n;
}

void Apartment::setStudents(int n) {
	this->students = n;
}

Builds Apartment::classOfBuild(){
	return APARTMENT;
}

Builds Services::classOfBuild() {
	return SERVICES;
}