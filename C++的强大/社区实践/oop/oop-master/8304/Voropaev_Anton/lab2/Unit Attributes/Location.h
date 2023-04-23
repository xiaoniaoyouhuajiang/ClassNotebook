#ifndef OOP_LOCATION_H
#define OOP_LOCATION_H

#include <iostream>

class Location {
public:

    Location(int x, int y);
    explicit Location(std::pair<int, int> pos);
    Location() = default;
    ~Location() = default;
    void setPosition(int x, int y);
    void setPosition(std::pair<int, int> pos);
    std::pair<int, int> getPosition() const;

private:
    std::pair<int, int> position;

};


#endif //OOP_LOCATION_H
