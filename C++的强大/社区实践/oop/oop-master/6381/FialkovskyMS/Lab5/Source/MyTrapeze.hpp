#ifndef _MyTrapeze
#define _MyTrapeze

#include "MyShape.hpp"

class MyTrapeze final : public MyShape {
public:
    MyTrapeze(sf::RenderWindow *w, float x, float y);

    virtual void ChangePosition(float new_x, float new_y) override ;
    virtual void ChangeAngle(int angle) override;
    virtual void ChangeColor(int r, int g, int b) override;
    virtual void ChangeScale(float kf) override;
    virtual void Draw() override;
    virtual double getArea() override;
};

#endif