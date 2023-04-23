#ifndef LAB2_HEALTHPOINTS_H
#define LAB2_HEALTHPOINTS_H


class HealthPoints {
    int health = 100;

public:
    HealthPoints() = default;
    HealthPoints(int);
    void change(int);
    int get_health() const;
};


#endif
