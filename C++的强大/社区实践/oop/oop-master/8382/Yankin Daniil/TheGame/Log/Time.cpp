#include "Time.h"


Time::Time() {
    update();
}

void Time::update() {
    time_t timer = time(NULL);
    calendarTime = localtime(&timer);
    calendarTime->tm_year += 1900;
    calendarTime->tm_mon += 1;
}


std::ostream& operator<<(std::ostream& stream, Time& time) {
    return stream << time.calendarTime->tm_mday << "." << time.calendarTime->tm_mon << "." << time.calendarTime->tm_year << " " <<
                     time.calendarTime->tm_hour << ":" << time.calendarTime->tm_min << ":" << time.calendarTime->tm_sec;
}
