#ifndef STOCK_H
#define STOCK_H

#include "production.h"
#include <vector>

class Visitor;

class Stock
{
public:
    Stock(QString storage_type, int capacity);

    QString accept(Visitor *v);
    bool add_product(QString p_type, QString name, int weight, int cost);
    QString get_storage_type() const;
    int get_capacity() const;
    std::vector<Production *> &get_storage_product();
    //bool ship_product(QString p_name, int weight);
private:
    QString storage_type;
    std::vector<Production *> storage_product;
    int capacity;
};

#endif // STOCK_H
