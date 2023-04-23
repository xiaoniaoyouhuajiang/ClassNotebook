#include "MySquare.hpp"

MySquare::MySquare(sf::RenderWindow *w, float x, float y) : MyShape(w) {
    maxLenght = 100;
    setOrigin(0, 0);
    setPointCount(4);
    setPoint(0, sf::Vector2f(-50, -50));
    setPoint(1, sf::Vector2f(50, -50));
    setPoint(2, sf::Vector2f(50, 50));
    setPoint(3, sf::Vector2f(-50, 50));
    setFillColor(sf::Color::Red);
    scale(2.0, 2.0);    
    setPosition(x,y);     
};

void MySquare::ChangePosition(float new_x, float new_y) {
    MyShape::ChangePosition(new_x, new_y);
    std::cout << "Position of MySquare has been changed. " << getObjectID();
}

void MySquare::ChangeAngle(int angle) {
    MyShape::ChangeAngle(angle);
    std::cout << "Angle of MySquare has been changed. " << getObjectID();
}

void MySquare::ChangeColor(int r, int g, int b) {
    MyShape::ChangeColor(r,g,b);
    std::cout << "Color of MySquare has been changed. " << getObjectID();
}    

void MySquare::ChangeScale(float kf) {
    MyShape::ChangeScale(kf);
    std::cout << "Scale of MySquare has been changed. " << getObjectID();
}

void MySquare::Draw() {
    MyShape::Draw();
    std::cout << "MySquare has been drawn. " << getObjectID();
}