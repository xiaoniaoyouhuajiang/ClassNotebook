#ifndef CITY_H
#define CITY_H

#include <QString>
#include <vector>
#include "stock.h"
#include "transport.h"

using namespace std;

class City
{
public:
    City(QString name);

    QString accept(Visitor * v);
    QString get_name() const;
    vector<Stock>& get_stocks();
    vector<Transport *> & get_transports();
    Stock& add_stock(QString storage_type, int capacity);
    Transport * add_transport(QString name, vector<QString> &transported_type, int cost, int capacity,
                              bool passenger_available);

    bool operator < (City const & other) const
    {
        return name < other.get_name() ? true : false;
    }

    bool operator == (City const & other) const
    {
        return name == other.name;
    }
private:
    QString name;
    vector<Stock> stock;
    vector<Transport *> transport;
};

#endif // CITY_H
