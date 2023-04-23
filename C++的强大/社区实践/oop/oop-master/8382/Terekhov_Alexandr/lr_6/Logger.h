#ifndef OOP_LOGGER_H
#define OOP_LOGGER_H

#include <fstream>
#include <iostream>
#include <chrono>

// интерфейс с рабочей функцией возврата времени
class CurrentTime{
public:
    std::string show();
};

// адаптер для вывода времени в консоль
class CurrentTimeCon{    // Есть класс CurrentTime и нам нужно чтоб
    CurrentTime ct;      // он реализовывал еще вывод времени для
public:                  // консоли, но менять его нельзя.
    std::string showC(); // Молчит.
    std::string show();
};

// класс реализующий вывод логов без вывода логов
class LazyLogger{
public:
    LazyLogger(){};
    LazyLogger& operator<< (const std::string){return *this;};
    ~LazyLogger(){};
};

// класс для вывода логов в файл
// заместитель ленивого логгера
class LoggerF {
    LazyLogger lg; // храним того кого замещаем, несмотря на то что он ничего не делает
    std::ofstream file;
    CurrentTime time; // использование интерфейса времени
public:
    LoggerF();
    LoggerF& operator<< (const std::string);
    ~LoggerF();
};

// класс заместитель для вывода логов в консоль
class LoggerC {
    LazyLogger lg;      // храним того кого замещаем
    CurrentTimeCon time;// использование переходника для времени
public:
    LoggerC();
    LoggerC& operator<< (const std::string);
};



#endif
