#include "MyShape.hpp"

class ObjectID;

MyShape::MyShape(sf::RenderWindow* w) : WIN(w), id() {} ;

bool MyShape::checkPressing(sf::Vector2f point) const {
    sf::FloatRect boundingBox = this->getGlobalBounds();
    if (boundingBox.contains(point))
        return true;
    else 
        return false;
}

bool MyShape::checkBorders(int delta, int direction) const { 
    enum dir { horizontal = 0, verticlal } ;
    std::cout << "Center of the shape: " 
                << getPosition().x << " " 
                << getPosition().y << " "
                << "Max Length: "
                << maxLenght << std::endl;

    switch (direction){
        case horizontal:
            if (getPosition().x - maxLenght - 10 + delta < 0)
                return false;
            if (getPosition().x + maxLenght + 10 + delta > 800)
                return false;
            break;

        case verticlal:
            if (getPosition().y - maxLenght - 10 + delta < 0)
                return false;

            if (getPosition().y + maxLenght + 10 + delta > 450)
                return false;          
            break;

        default:
            std::cout << "Incorrect move direction in checkBorders class shape!";
            exit(1);
            break;
    }
    return true;
}

void MyShape::setPos(float x, float y){
    this->setPosition(x,y);
}

void MyShape::ChangeOutLineColor(int r, int g, int b){
    this->setOutlineColor(sf::Color(r,g,b));
}

void MyShape::ChangeOutLineThickness(int new_thick) {
    this->setOutlineThickness(new_thick);
} 

ObjectID MyShape::getObjectID() const {
    return id.getObjectID();
}

void MyShape::ChangePosition(float new_x, float new_y){
    this->move(new_x, new_y);
}

void MyShape::ChangeAngle(int angle){
    this->rotate(angle);
}

void MyShape::ChangeColor(int r, int g, int b){
    this->setFillColor(sf::Color(r,g,b));
}    

void MyShape::ChangeScale(float kf){
    maxLenght *= kf;
    this->scale(kf, kf);
}

void MyShape::Draw() {
    WIN->draw(*this);
}

sf::Color MyShape::getColor() const  {
    return this->getFillColor();
}