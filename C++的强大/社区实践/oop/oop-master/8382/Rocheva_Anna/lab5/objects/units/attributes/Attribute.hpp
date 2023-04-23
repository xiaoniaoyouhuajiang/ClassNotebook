#ifndef LABOOP_ATTRIBUTE_HPP
#define LABOOP_ATTRIBUTE_HPP

class Attribute{
protected:
    explicit Attribute(int val) : value(val) {};
public:
    int getValue() {return value;};
    void changeValue(int val) {value += val;};
private:
    int value;
};


#endif //LABOOP_ATTRIBUTE_HPP
