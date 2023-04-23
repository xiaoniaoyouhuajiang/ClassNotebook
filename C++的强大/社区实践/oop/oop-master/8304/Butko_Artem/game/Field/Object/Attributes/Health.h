



#ifndef NEW_LR1_HEALTH_H
#define NEW_LR1_HEALTH_H


#include <cstdio>

class Health
{
public:
    Health() = default;
    ~Health() = default;

    void set(int health);
    int get();
    void actDamaged(size_t damage);
    void actHealed(size_t heal);
private:
    size_t maxHealth_;
    int health_;
    bool isDead;
};


#endif //NEW_LR1_HEALTH_H
