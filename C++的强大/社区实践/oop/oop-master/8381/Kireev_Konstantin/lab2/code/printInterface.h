#ifndef PRINTINTERFACE_H
#define PRINTINTERFACE_H

#include <QString>

class printInterface
{
public:
    virtual QString getClass() = 0; //имя класса
    virtual ~printInterface() = default; //деструктор
};

#endif // PRINTINTERFACE_H
