#include <iostream>
#include <string>
using namespace std;

class Strategy{
public:
    virtual ~Strategy() {}
    virtual int get_bonus(string type) = 0;
};

class Strategy_dragons : public Strategy{

    int health = 0;
public:
    Strategy_dragons(int health): health(health){}

    int get_bonus(string type){
        return health;
    }
};

class Strategy_warrior : public Strategy{

    int health = 0;
public:
    Strategy_warrior(int health): health(health){}

    int get_bonus(string type){
        return health/2;
    }
};

class Strategy_sentry : public Strategy{

    int health = 0;
public:
    Strategy_sentry(int health): health(health){}

    int get_bonus(string type){
        return health/3;
    }
};

class Strategy_selector : public Strategy{
    int health = 0;
public:
    Strategy_selector(int health): health(health){}

    int get_bonus(string type){
        if (type[0] == 'D'){
            Strategy_dragons dragon(health);
            return dragon.get_bonus(type);
        }
        else if (type[0] == 'W'){
            Strategy_warrior warrior(health);
            return warrior.get_bonus(type);
        }
        else if (type[0] == 'S'){
            Strategy_sentry sentry(health);
            return sentry.get_bonus(type);
        }
        else {
            return 0;
        }
    }
};
