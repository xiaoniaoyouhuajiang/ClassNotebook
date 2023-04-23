#include "Location.h"


Location::Location(int x, int y) {
    this->position.first = x;
    this->position.second = y;
}

Location::Location(std::pair<int, int> pos) {
    this->position = pos;
}

void Location::setPosition(int x, int y) {
    this->position.first = x;
    this->position.second = y;
}

void Location::setPosition(std::pair<int, int> pos) {
    this->position = pos;
}

std::pair<int, int> Location::getPosition() const {
    return position;
}