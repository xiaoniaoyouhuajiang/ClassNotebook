#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Limit_Exception : public exception
{
private:
    string whatStr;
    int limit;
public:
    Limit_Exception(string &&what, int limit) noexcept :  whatStr(what), limit(limit)
    {}
    const char* what() const noexcept {
        return whatStr.c_str();
    }
    int info() const noexcept {
        return limit;
    }
};

class Coord_Error : public exception
{
private:
    string whatStr;
    int x;
    int y;
public:
    Coord_Error(string &&what, int x, int y) noexcept :  whatStr(what), x(x), y(y)
    {}
    const char* what() const noexcept {
        return whatStr.c_str();
    }
    vector<int> info() const noexcept {
        vector<int> output = {x,y};
        return output;
    }
};
