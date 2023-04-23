#ifndef LAB2_ATTACK_H
#define LAB2_ATTACK_H


class Attack {
    int attack = 100;
public:
    Attack() = default;
    explicit Attack(int);
    void change(int);
    void set(int);
    int get_attack() const;
};


#endif
