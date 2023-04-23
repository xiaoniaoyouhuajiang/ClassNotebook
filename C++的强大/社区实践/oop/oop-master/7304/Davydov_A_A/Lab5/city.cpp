#include "city.h"
#include "myexception.h"
#include "visitor.h"

City::City(QString name) : name(name)
{}

QString City::get_name() const
{
    return name;
}

Stock& City::add_stock(QString storage_type, int capacity)
{
    stock.push_back(Stock(storage_type, capacity));

    if(stock.back().get_storage_type().toLower() == "unknown")
        throw MyException("Add stock error", "Incorrect storage type: " + storage_type);

    return stock.back();
}

vector<Stock>& City::get_stocks()
{
    return stock;
}

vector<Transport *> & City::get_transports()
{
    return transport;
}

Transport * City::add_transport(QString name, vector<QString> &transported_type, int cost, int capacity,
                                bool passenger_available)
{
    /* add Aircraft */
    if(name.toLower() == QString("aircraft"))
        transport.push_back(new Aircraft(transported_type, cost, capacity, passenger_available));
    /* add Helicopter */
    else if(name.toLower() == QString("helicopter"))
        transport.push_back(new Helicopter(transported_type, cost, capacity, passenger_available));
    /* add Ship */
    else if(name.toLower() == QString("ship"))
        transport.push_back(new Ship(transported_type, cost, capacity, passenger_available));
    /* add Submarine */
    else if(name.toLower() == QString("submarine"))
        transport.push_back(new Submarine(transported_type, cost, capacity, passenger_available));
    /* add Car */
    else if(name.toLower() == QString("car"))
        transport.push_back(new Car(transported_type, cost, capacity, passenger_available));
    /* add Train */
    else if(name.toLower() == QString("train"))
        transport.push_back(new Train(transported_type, cost, capacity, passenger_available));
    else
        throw MyException("Add transport error", "Incorrect transport name: " + name);

    return transport.back();
}

QString City::accept(Visitor * v) { v->visit_city(*this); }
