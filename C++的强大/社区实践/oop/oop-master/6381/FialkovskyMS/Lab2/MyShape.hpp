#ifndef _Shape
#define _Shape

#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <iostream>

#include "ObjectID.hpp"

class IShape {
public:
    virtual void ChangePosition(float x, float y) = 0;
    virtual void ChangeAngle(int angle) = 0;
    virtual void ChangeColor(int r, int g, int b) = 0;
    virtual void ChangeScale(float kf) = 0;
    virtual void Draw() = 0;
};

class MyShape : public IShape, protected sf::ConvexShape {
// class MyShape : protected sf::ConvexShape {    
protected:
    sf::RenderWindow *WIN;
    ObjectID id;
    float maxLenght;
    // Для реализации по умолчанию.
public:
    MyShape(sf::RenderWindow* w);

	// Функции из интерфейса
    virtual void ChangePosition(float x, float y) = 0;
    virtual void ChangeAngle(int angle) = 0;
    virtual void ChangeColor(int r, int g, int b) = 0;
    virtual void ChangeScale(float kf) = 0; 
    virtual void Draw() = 0;
    //

    bool checkPressing(sf::Vector2f point) const;
    bool checkBorders(int delta, int direction) const;
    void ChangeOutLineColor(int r, int g, int b);
    void ChangeOutLineThickness(int new_thick);
    ObjectID getObjectID() const ;
};

#endif