#ifndef IPRINTABLE_H
#define IPRINTABLE_H
#include <QString>
//interface for printing info about classes in console

class IPrintable
{
public:
    virtual QString getClass() = 0;
    virtual ~IPrintable() = default;
};

#endif // IPRINTABLE_H
