#ifndef OOP_HEALTH_H
#define OOP_HEALTH_H

#include <iostream>

class Health {

public:
    Health();
    ~Health() = default;
    explicit Health(int h);
    int getHealth();
    void setHealth(int h);
    void actDamaged(int dmg);
    void actHealed(int heal);

private:
    int health;
};
#endif //OOP_HEALTH_H
