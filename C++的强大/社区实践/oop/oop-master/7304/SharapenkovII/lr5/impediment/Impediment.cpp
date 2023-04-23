//
// Created by smokfyz on 10.04.19.
//

#include "Impediment.h"

unsigned Impediment::getPermeability() const { return permeability; }

string Impediment::getTypeName() const { return type_name; }

float Impediment::getProbability() const { return probability; }

vector<shared_ptr<Cell>> const& Impediment::getFilled() const { return filled; }

void Impediment::fillCell(shared_ptr<Cell> cell) { filled.push_back(cell); }

void Impediment::refillCell(shared_ptr<Cell> cell) {
    filled.erase(remove(filled.begin(), filled.end(), cell), filled.end());
}