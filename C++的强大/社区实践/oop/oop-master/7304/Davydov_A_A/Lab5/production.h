#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <QString>

extern std::vector<QString> p_types;

/*
 *
 * Product ---> Solid ---> Metall ---> Fe
 *
*/

//base abstract class of production
class Production
{
public:
    virtual ~Production();

    //interface
    virtual QString get_final_product_name() const = 0;
    virtual int get_weight() const = 0;
    virtual void decrease_weight(int val) = 0;
    virtual int get_cost() const = 0;
    virtual  QString get_units() const = 0;
    virtual QString get_product_type() const = 0;
};

class Solid : public Production
{
public:
    QString get_product_type() const override;
};

class Metall : public Solid
{
public:
    QString get_units() const override;
};

class Fe : public Metall
{
public:
    Fe(int cost, int weight, QString name);

    QString get_final_product_name() const override;
    int get_weight() const override;
    int get_cost() const override;
    void decrease_weight(int val) override;
private:
    int cost;
    int weight;
    QString name;
};

class Cu : public Metall
{
public:
    Cu(int cost, int weight, QString name);

    QString get_final_product_name() const override;
    int get_weight() const override;
    int get_cost() const override;
    void decrease_weight(int val) override;
private:
    int cost;
    int weight;
    QString name;
};

class BuildingMaterial : public Solid
{
public:
    QString get_units() const override;
};

class Brick : public BuildingMaterial
{
public:
    Brick(int cost, int weight, QString name);

    QString get_final_product_name() const override;
    int get_weight() const override;
    int get_cost() const override;
    void decrease_weight(int val) override;
private:
    int cost;
    int weight;
    QString name;
};

class Wood : public BuildingMaterial
{
public:
    Wood(int cost, int weight, QString name);

    QString get_final_product_name() const override;
    int get_weight() const override;
    int get_cost() const override;
    void decrease_weight(int val) override;
private:
    int cost;
    int weight;
    QString name;
};


class Liquid : public Production
{
public:
    QString get_product_type() const override;
};

class Dense : public Liquid
{
public:
    QString get_units() const override;
};

class Aniline : public Dense
{
public:
    Aniline(int cost, int weight, QString name);

    QString get_final_product_name() const override;
    int get_weight() const override;
    int get_cost() const override;
    void decrease_weight(int val) override;
private:
    int cost;
    int weight;
    QString name;
};

class Antifreeze : public Dense
{
public:
    Antifreeze(int cost, int weight, QString name);

    QString get_final_product_name() const override;
    int get_weight() const override;
    int get_cost() const override;
    void decrease_weight(int val) override;
private:
    int cost;
    int weight;
    QString name;
};

class Oil : public  Liquid
{
public:
    QString get_units() const override;
};

class Petroleum : public Oil
{
public:
    Petroleum(int cost, int weight, QString name);

    QString get_final_product_name() const override;
    int get_weight() const override;
    int get_cost() const override;
    void decrease_weight(int val) override;
private:
    int cost;
    int weight;
    QString name;
};

class Kerosene : public Oil
{
public:
    Kerosene(int cost, int weight, QString name);

    QString get_final_product_name() const override;
    int get_weight() const override;
    int get_cost() const override;
    void decrease_weight(int val) override;
private:
    int cost;
    int weight;
    QString name;
};


class Gaseous : public Production
{
public:
    QString get_product_type() const override;
};

class Natural : public Gaseous
{
public:
    QString get_units() const override;
};

class H2 : public Natural
{
public:
    H2(int cost, int weight, QString name);

    QString get_final_product_name() const override;
    int get_weight() const override;
    int get_cost() const override;
    void decrease_weight(int val) override;
private:
    int cost;
    int weight;
    QString name;
};

class C3H8 : public Natural
{
public:
    C3H8(int cost, int weight, QString name);

    QString get_final_product_name() const override;
    int get_weight() const override;
    int get_cost() const override;
    void decrease_weight(int val) override;
private:
    int cost;
    int weight;
    QString name;
};

class Artifical : public Gaseous
{
public:
    QString get_units() const override;
};

class WaterGas : public Artifical
{
public:
    WaterGas(int cost, int weight, QString name);

    QString get_final_product_name() const override;
    int get_weight() const override;
    int get_cost() const override;
    void decrease_weight(int val) override;
private:
    int cost;
    int weight;
    QString name;
};

class CokeOvenGas : public Artifical
{
public:
    CokeOvenGas(int cost, int weight, QString name);

    QString get_final_product_name() const override;
    int get_weight() const override;
    int get_cost() const override;
    void decrease_weight(int val) override;
private:
    int cost;
    int weight;
    QString name;
};

#endif // PRODUCTION_H
