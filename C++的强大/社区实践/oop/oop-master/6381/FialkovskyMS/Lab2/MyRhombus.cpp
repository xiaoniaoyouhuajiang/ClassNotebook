#include "MyRhombus.hpp"

MyRhombus::MyRhombus(sf::RenderWindow *w, float x, float y) : MyShape(w) {
    maxLenght = 60;
    setOrigin(0, 0);
    setPointCount(4);
    setPoint(0, sf::Vector2f(0, -60));
    setPoint(1, sf::Vector2f(40, 0));
    setPoint(2, sf::Vector2f(0, 60));
    setPoint(3, sf::Vector2f(-40, 0));
    setFillColor(sf::Color::Red);
    scale(2.0, 2.0);
    setPosition(x,y);     
};

void MyRhombus::ChangePosition(float new_x, float new_y) {
    MyShape::ChangePosition(new_x, new_y);
    std::cout << "Position of MyRhombus has been changed. " << getObjectID();
}

void MyRhombus::ChangeAngle(int angle) {
    MyShape::ChangeAngle(angle);
    std::cout << "Angle of MyRhombus has been changed. " << getObjectID();
}

void MyRhombus::ChangeColor(int r, int g, int b) {
    MyShape::ChangeColor(r,g,b);
    std::cout << "Color of MyRhombus has been changed. " << getObjectID();
}    

void MyRhombus::ChangeScale(float kf) {
    MyShape::ChangeScale(kf);
    std::cout << "Scale of MyRhombus has been changed. " << getObjectID();
}

void MyRhombus::Draw() {
    MyShape::Draw();
    std::cout << "MyRhombus has been drawn. " << getObjectID();
}