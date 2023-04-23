#ifndef TRANSPORT_H
#define TRANSPORT_H

#include "production.h"
#include <vector>
#include <QString>

class Visitor;

class Transport
{
public:
    virtual ~Transport();

    //bool load_product(QString product_name, int weight, int cost);
    //std::vector<Production *> & get_products();

    //interface
    virtual QString accept(Visitor *v) = 0;
    virtual int get_cost() const = 0;
    virtual std::vector<QString> & get_transported_type() = 0;
    virtual bool get_passenger_type_available() const = 0;
    virtual QString get_name() const = 0;
    virtual QString get_transport_type() const = 0;
    virtual int get_capacity() const = 0;
private:
    //std::vector<Production *> products;
};

class Air : public Transport
{
public:
    QString get_transport_type() const override;
};

class Aircraft : public Air
{
public:
    Aircraft(std::vector<QString> transported_type, int cost_per_distance, int capacity,
              bool passenger_transport_available);
    int get_cost() const override;
    std::vector<QString> & get_transported_type() override;
    bool get_passenger_type_available() const override;
    QString get_name() const override;
    int get_capacity() const override;
    QString accept(Visitor *v) override;
private:
   std::vector<QString> transported_type;
   int cost_per_distance;
   int capacity;
   bool passenger_transport_available;
};

class Helicopter : public Air
{
public:
    Helicopter(std::vector<QString> transported_type, int cost_per_distance, int capacity,
              bool passenger_transport_available);
    int get_cost() const override;
    std::vector<QString> & get_transported_type() override;
    bool get_passenger_type_available() const override;
    QString get_name() const override;
    int get_capacity() const override;
    QString accept(Visitor *v) override;
private:
   std::vector<QString> transported_type;
   int cost_per_distance;
   int capacity;
   bool passenger_transport_available;
};

class Water : public Transport
{
public:
    QString get_transport_type() const override;
};

class Ship : public Water
{
public:
    Ship(std::vector<QString> transported_type, int cost_per_distance, int capacity,
              bool passenger_transport_available);
    int get_cost() const override;
    std::vector<QString> & get_transported_type() override;
    bool get_passenger_type_available() const override;
    QString get_name() const override;
    int get_capacity() const override;
    QString accept(Visitor *v) override;
private:
   std::vector<QString> transported_type;
   int cost_per_distance;
   int capacity;
   bool passenger_transport_available;
};

class Submarine : public Water
{
public:
    Submarine(std::vector<QString> transported_type, int cost_per_distance, int capacity,
              bool passenger_transport_available);
    int get_cost() const override;
    std::vector<QString> & get_transported_type() override;
    bool get_passenger_type_available() const override;
    QString get_name() const override;
    int get_capacity() const override;
    QString accept(Visitor *v) override;
private:
   std::vector<QString> transported_type;
   int cost_per_distance;
   int capacity;
   bool passenger_transport_available;
};


class Land : public Transport
{
public:
    QString get_transport_type() const override;
};

class Car : public Land
{
public:
    Car(std::vector<QString> transported_type, int cost_per_distance, int capacity,
              bool passenger_transport_available);
    int get_cost() const override;
    std::vector<QString> & get_transported_type() override;
    bool get_passenger_type_available() const override;
    QString get_name() const override;
    int get_capacity() const override;
    QString accept(Visitor *v) override;
private:
   std::vector<QString> transported_type;
   int cost_per_distance;
   int capacity;
   bool passenger_transport_available;
};

class Train : public Land
{
public:
    Train(std::vector<QString> transported_type, int cost_per_distance, int capacity,
              bool passenger_transport_available);
    int get_cost() const override;
    std::vector<QString> & get_transported_type() override;
    bool get_passenger_type_available() const override;
    QString get_name() const override;
    int get_capacity() const override;
    QString accept(Visitor *v) override;
private:
   std::vector<QString> transported_type;
   int cost_per_distance;
   int capacity;
   bool passenger_transport_available;
};

#endif // TRANSPORT_H
