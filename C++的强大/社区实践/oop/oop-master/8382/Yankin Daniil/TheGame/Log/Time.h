#pragma once

#include <ostream>
#include <ctime>


class Time {
public:
    Time();
    void update();

    friend std::ostream& operator<<(std::ostream& stream, Time& time);

private:
    std::tm* calendarTime;
};
