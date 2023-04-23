



#ifndef NEW_LR1_ARMOR_H
#define NEW_LR1_ARMOR_H


#include <cstdio>

class Armor
{
public:
    Armor() = default;
    ~Armor() = default;

    void set(int armor, bool exist);
    int get();
    void actDamaged(size_t damage);
private:
    int armor_;
    bool isExist;
};


#endif //NEW_LR1_ARMOR_H
