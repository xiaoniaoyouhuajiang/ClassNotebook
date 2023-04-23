#include "transport.h"
#include "visitor.h"

Transport::~Transport() {}

QString Air::get_transport_type() const { return "Air";}

Aircraft::Aircraft(std::vector<QString> transported_type, int cost_per_distance, int capacity,
                     bool passenger_transport_available) : transported_type(transported_type),
                     cost_per_distance(cost_per_distance), capacity(capacity),
                     passenger_transport_available(passenger_transport_available) {}

int Aircraft::get_cost() const { return cost_per_distance;}

std::vector<QString> & Aircraft::get_transported_type() { return transported_type;}

bool Aircraft::get_passenger_type_available() const { return passenger_transport_available;}

QString Aircraft::get_name() const { return "Aircraft";}

int Aircraft::get_capacity() const { return capacity;}

QString Aircraft::accept(Visitor *v) { return v->visit_transport(this); }


Helicopter::Helicopter(std::vector<QString> transported_type, int cost_per_distance, int capacity,
                     bool passenger_transport_available) : transported_type(transported_type),
                     cost_per_distance(cost_per_distance), capacity(capacity),
                     passenger_transport_available(passenger_transport_available) {}

int Helicopter::get_cost() const { return cost_per_distance;}

std::vector<QString> & Helicopter::get_transported_type() { return transported_type;}

bool Helicopter::get_passenger_type_available() const { return passenger_transport_available;}

QString Helicopter::get_name() const { return "Helicopter";}

int Helicopter::get_capacity() const { return capacity;}

QString Helicopter::accept(Visitor *v) { return v->visit_transport(this); }


QString Water::get_transport_type() const { return "Water";}

Ship::Ship(std::vector<QString> transported_type, int cost_per_distance, int capacity,
                     bool passenger_transport_available) : transported_type(transported_type),
                     cost_per_distance(cost_per_distance), capacity(capacity),
                     passenger_transport_available(passenger_transport_available) {}

int Ship::get_cost() const { return cost_per_distance;}

std::vector<QString> & Ship::get_transported_type() { return transported_type;}

bool Ship::get_passenger_type_available() const { return passenger_transport_available;}

QString Ship::get_name() const { return "Ship";}

int Ship::get_capacity() const { return capacity;}

QString Ship::accept(Visitor *v) { return v->visit_transport(this); }

Submarine::Submarine(std::vector<QString> transported_type, int cost_per_distance, int capacity,
                     bool passenger_transport_available) : transported_type(transported_type),
                     cost_per_distance(cost_per_distance), capacity(capacity),
                     passenger_transport_available(passenger_transport_available) {}

int Submarine::get_cost() const { return cost_per_distance;}

std::vector<QString> & Submarine::get_transported_type() { return transported_type;}

bool Submarine::get_passenger_type_available() const { return passenger_transport_available;}

QString Submarine::get_name() const { return "Submarine";}

int Submarine::get_capacity() const { return capacity;}

QString Submarine::accept(Visitor *v) { return v->visit_transport(this); }

QString Land::get_transport_type() const { return "Land";}

Car::Car(std::vector<QString> transported_type, int cost_per_distance, int capacity,
                     bool passenger_transport_available) : transported_type(transported_type),
                     cost_per_distance(cost_per_distance), capacity(capacity),
                     passenger_transport_available(passenger_transport_available) {}

int Car::get_cost() const { return cost_per_distance;}

std::vector<QString> & Car::get_transported_type() { return transported_type;}

bool Car::get_passenger_type_available() const { return passenger_transport_available;}

QString Car::get_name() const { return "Car";}

int Car::get_capacity() const { return capacity;}

QString Car::accept(Visitor *v) { return v->visit_transport(this); }

Train::Train(std::vector<QString> transported_type, int cost_per_distance, int capacity,
                     bool passenger_transport_available) : transported_type(transported_type),
                     cost_per_distance(cost_per_distance), capacity(capacity),
                     passenger_transport_available(passenger_transport_available) {}

int Train::get_cost() const { return cost_per_distance;}

std::vector<QString> & Train::get_transported_type() { return transported_type;}

bool Train::get_passenger_type_available() const { return passenger_transport_available;}

QString Train::get_name() const { return "Train";}

int Train::get_capacity() const { return capacity;}

QString Train::accept(Visitor *v) { return v->visit_transport(this); }


