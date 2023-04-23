#ifndef VISITOR_H
#define VISITOR_H

#include <QString>

class City;
class Stock;
class Transport;

class Visitor
{
public:
    virtual ~Visitor();

    //interface
    virtual QString visit_stock(Stock & s) = 0;
    virtual QString visit_transport(Transport * t) = 0;
    virtual QString visit_city(City &c) = 0;
};

class CityStatusMaker : public Visitor
{
public:
    QString visit_stock(Stock & s) override;
    QString visit_transport(Transport * t) override;
    QString visit_city(City &c) override;
};

#endif // VISITOR_H
