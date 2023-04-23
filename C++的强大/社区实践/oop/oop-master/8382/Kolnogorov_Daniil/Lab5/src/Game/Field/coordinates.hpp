#pragma once

#include "../../Logging/logger_proxy.hpp"
#include <ostream>
#include <sstream>

class Coordinates {
public:
    int x, y;

    Coordinates() : x(0), y(0) {}
    Coordinates(int x, int y) : x(x), y(y) {}
    Coordinates(string str) {
        istringstream iss(str);
        char c;
        iss >> c >> x >> c >> y >> c;
    };

    bool operator==(const struct Coordinates& other) {
        return x == other.x && y == other.y;
    };

    bool operator!=(const struct Coordinates& other) {
        return x != other.x || y != other.y;
    };

    friend LoggerProxy& operator<<(LoggerProxy& logger,
                                   const Coordinates& coors) {
        logger << "(" << coors.x << "," << coors.y << ")";
        return logger;
    };

    friend ostream& operator<<(ostream& out, const Coordinates& coors){
        out << "(" << coors.x << "," << coors.y << ")";
        return out;
    };

    static unsigned distance_manh(Coordinates first, Coordinates second) {
        return abs((int)first.x - (int)second.x) +
               abs((int)first.y - (int)second.y);
    }

    static unsigned distance_manh(int x1, int y1, int x2, int y2) {
        return abs(x1 - x2) + (y1 - y2);
    }
};
