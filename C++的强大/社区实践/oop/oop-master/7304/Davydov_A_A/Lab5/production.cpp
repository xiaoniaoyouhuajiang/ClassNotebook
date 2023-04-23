#include "production.h"

std::vector<QString> p_types = {"Solid", "Liquid", "Gaseous"};

Production::~Production(){}

QString Solid::get_product_type() const
{
    return "Solid";
}

QString Metall::get_units() const
{
    return "kg";
}

Fe::Fe(int cost, int weight, QString name) : cost(cost), weight(weight), name(name) {}

QString Fe::get_final_product_name() const
{
    return name;
}

int Fe::get_weight() const
{
    return weight;
}

int Fe::get_cost() const
{
    return cost;
}

void Fe::decrease_weight(int val)
{
    weight -= val;
}

Cu::Cu(int cost, int weight, QString name) : cost(cost), weight(weight), name(name) {}

QString Cu::get_final_product_name() const
{
    return name;
}

int Cu::get_weight() const
{
    return weight;
}

int Cu::get_cost() const
{
    return cost;
}

void Cu::decrease_weight(int val)
{
    weight -= val;
}

QString BuildingMaterial::get_units() const
{
    return "pieces";
}

Brick::Brick(int cost, int weight, QString name) : cost(cost), weight(weight), name(name) {}

QString Brick::get_final_product_name() const
{
    return name;
}

int Brick::get_weight() const
{
    return weight;
}

int Brick::get_cost() const
{
    return cost;
}

void Brick::decrease_weight(int val)
{
    weight -= val;
}

Wood::Wood(int cost, int weight, QString name) : cost(cost), weight(weight), name(name) {}

QString Wood::get_final_product_name() const
{
    return name;
}

int Wood::get_weight() const
{
    return weight;
}

int Wood::get_cost() const
{
    return cost;
}

void Wood::decrease_weight(int val)
{
    weight -= val;
}

QString Liquid::get_product_type() const
{
    return "Luquid";
}

QString Dense::get_units() const
{
    return "liters";
}

Aniline::Aniline(int cost, int weight, QString name) : cost(cost), weight(weight), name(name) {}

QString Aniline::get_final_product_name() const
{
    return name;
}

int Aniline::get_weight() const
{
    return weight;
}

int Aniline::get_cost() const
{
    return cost;
}

void Aniline::decrease_weight(int val)
{
    weight -= val;
}

Antifreeze::Antifreeze(int cost, int weight, QString name) : cost(cost), weight(weight), name(name) {}

QString Antifreeze::get_final_product_name() const
{
    return name;
}

int Antifreeze::get_weight() const
{
    return weight;
}

int Antifreeze::get_cost() const
{
    return cost;
}

void Antifreeze::decrease_weight(int val)
{
    weight -= val;
}

QString Oil::get_units() const
{
    return "barrel";
}

Petroleum::Petroleum(int cost, int weight, QString name) : cost(cost), weight(weight), name(name) {}

QString Petroleum::get_final_product_name() const
{
    return name;
}

int Petroleum::get_weight() const
{
    return weight;
}

int Petroleum::get_cost() const
{
    return cost;
}

void Petroleum::decrease_weight(int val)
{
    weight -= val;
}

Kerosene::Kerosene(int cost, int weight, QString name) : cost(cost), weight(weight), name(name) {}

QString Kerosene::get_final_product_name() const
{
    return name;
}

int Kerosene::get_weight() const
{
    return weight;
}

int Kerosene::get_cost() const
{
    return cost;
}

void Kerosene::decrease_weight(int val)
{
    weight -= val;
}


QString Gaseous::get_product_type() const
{
    return "Gaseous";
}

QString Natural::get_units() const
{
    return "m^3";
}

H2::H2(int cost, int weight, QString name) : cost(cost), weight(weight), name(name) {}

QString H2::get_final_product_name() const
{
    return name;
}

int H2::get_weight() const
{
    return weight;
}

int H2::get_cost() const
{
    return cost;
}

void H2::decrease_weight(int val)
{
    weight -= val;
}

C3H8::C3H8(int cost, int weight, QString name) : cost(cost), weight(weight), name(name) {}

QString C3H8::get_final_product_name() const
{
    return name;
}

int C3H8::get_weight() const
{
    return weight;
}

int C3H8::get_cost() const
{
    return cost;
}

void C3H8::decrease_weight(int val)
{
    weight -= val;
}

QString Artifical::get_units() const
{
    return "m^3";
}

WaterGas::WaterGas(int cost, int weight, QString name) : cost(cost), weight(weight), name(name) {}

QString WaterGas::get_final_product_name() const
{
    return name;
}

int WaterGas::get_weight() const
{
    return weight;
}

int WaterGas::get_cost() const
{
    return cost;
}

void WaterGas::decrease_weight(int val)
{
    weight -= val;
}

CokeOvenGas::CokeOvenGas(int cost, int weight, QString name) : cost(cost), weight(weight), name(name) {}

QString CokeOvenGas::get_final_product_name() const
{
    return name;
}

int CokeOvenGas::get_weight() const
{
    return weight;
}

int CokeOvenGas::get_cost() const
{
    return cost;
}

void CokeOvenGas::decrease_weight(int val)
{
    weight -= val;
}


