

#ifndef WeaponBehavior_h
#define WeaponBehavior_h

class WeaponBehavior{
public:
    virtual void useWeapon() {};
};


class Sword: public WeaponBehavior{
public:
    void useWeapon() override{
        //Someday there will be a realization ... but not today
    };
};


class Lance: public WeaponBehavior{
public:
    void useWeapon() override{
        //Someday there will be a realization ... but not today
    }
};


class Dagger: public WeaponBehavior{
public:
    void useWeapon() override{
        //Someday there will be a realization ... but not today
    }
};


class Bow: public WeaponBehavior{
public:
//    Bow(){
//        std::cout<<"Bow"<<std::endl;
//    }
    void useWeapon() override{
        //Someday there will be a realization ... but not today
    }
};


class Staff: public WeaponBehavior{
public:
    void useWeapon() override{
        //Someday there will be a realization ... but not today
    }
};


class Hands: public WeaponBehavior{
public:
    void useWeapon() override{
        //Someday there will be a realization ... but not today
    }
};

#endif /* WeaponBehavior_h */
