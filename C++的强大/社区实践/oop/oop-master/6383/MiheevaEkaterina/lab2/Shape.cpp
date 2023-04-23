//
// Created by katier on 12.03.18.
//
#include "Shape.h"
unsigned  long long Shape::counter=0;
Shape::Shape(Colour colour):colour(colour){
    id=counter++;
};
Colour Shape::getColour(){
    return this->colour;
}
void Shape:: setColour(Colour colour){
    this->colour=colour;
}
unsigned long long int Shape:: getId(){
    return id;
}
