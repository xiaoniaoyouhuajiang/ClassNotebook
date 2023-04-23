#include "MyTrapeze.hpp"

MyTrapeze::MyTrapeze(sf::RenderWindow *w, float x, float y) : MyShape(w) {
    maxLenght = 80;
    setOrigin(0, 0);
    setPointCount(4);
    setPoint(0, sf::Vector2f(-60, -40));
    setPoint(1, sf::Vector2f(60, -40));
    setPoint(2, sf::Vector2f(40, 40));
    setPoint(3, sf::Vector2f(-40, 40));
    setFillColor(sf::Color::Red);
    setRotation(180);
    scale(2.0, 2.0);
    setPosition(x,y);     
};

void MyTrapeze::ChangePosition(float new_x, float new_y) {
    MyShape::ChangePosition(new_x, new_y);
    std::cout << "Position of MyTrapeze has been changed. " << getObjectID();
}

void MyTrapeze::ChangeAngle(int angle) {
    MyShape::ChangeAngle(angle);
    std::cout << "Angle of MyTrapeze has been changed. " << getObjectID();
}

void MyTrapeze::ChangeColor(int r, int g, int b) {
    MyShape::ChangeColor(r,g,b);
    std::cout << "Color of MyTrapeze has been changed. " << getObjectID();
}    

void MyTrapeze::ChangeScale(float kf) {
    MyShape::ChangeScale(kf);
    std::cout << "Scale of MyTrapeze has been changed. " << getObjectID();
}

void MyTrapeze::Draw() {
    MyShape::Draw();
    std::cout << "MyTrapeze has been drawn. " << getObjectID();
}