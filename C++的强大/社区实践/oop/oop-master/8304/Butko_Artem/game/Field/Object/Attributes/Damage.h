



#ifndef NEW_LR1_DAMAGE_H
#define NEW_LR1_DAMAGE_H

#include <utility>

class Damage
{
public:
    Damage() = default;
    ~Damage() = default;

    void set(size_t damage, size_t range);
    std::pair<size_t, size_t> get();
    size_t getDamage();
    size_t getRange();
private:
    std::pair<size_t, size_t> damage_;
};


#endif //NEW_LR1_DAMAGE_H
