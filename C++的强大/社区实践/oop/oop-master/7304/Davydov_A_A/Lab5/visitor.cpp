#include "visitor.h"
#include "city.h"
#include "transport.h"
#include "stock.h"

Visitor::~Visitor() {}

QString CityStatusMaker::visit_stock(Stock & s)
{
    QString info = "Stock: " + s.get_storage_type() + "/" + QString::number(s.get_capacity()) + "\n";

    for(auto & p : s.get_storage_product())
        info += "Product: " + p->get_product_type() + "/" + p->get_final_product_name() +
                QString::number(p->get_weight()) + p->get_units() + "/" + QString::number(p->get_cost()) + "$\n";

    return info;
}

QString CityStatusMaker::visit_transport(Transport * t)
{
    QString transported_type = "[";
    QString carry_passengers = t->get_passenger_type_available() ? "Carry passengers" : "Doesn't carry passengers";

    for(auto & type : t->get_transported_type())
        transported_type += type + "/";

    transported_type += "]";

    QString info = "Transport: " + t->get_transport_type() + "/" + t->get_name() + "/" + transported_type +
            QString::number(t->get_cost()) + "l per km" + "/" + QString::number(t->get_capacity()) +
            carry_passengers + "\n";

    return info;
}

QString CityStatusMaker::visit_city(City &c)
{
    QString info = "City: " + c.get_name() + "\n";

    for(auto & s : c.get_stocks())
        info += s.accept(this);

    for(auto & t : c.get_transports())
        info += t->accept(this);

    return info;
}
