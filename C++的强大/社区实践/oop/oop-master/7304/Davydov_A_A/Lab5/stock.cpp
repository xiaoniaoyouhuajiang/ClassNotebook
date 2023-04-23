#include "stock.h"
#include "visitor.h"

Stock::Stock(QString p_type, int capacity) : capacity(capacity)
{
    storage_type = "Unknown";

    for(QString type : p_types)
        if(p_type.toLower() == type.toLower())
            storage_type = type;
}

bool Stock::add_product(QString p_type, QString name, int weight, int cost)
{
    if(p_type.toLower() == storage_type.toLower() && weight <= capacity)
    {
        /* add Fe */
        if(name.toLower() == QString("fe"))
        {
            capacity -= weight;
            storage_product.push_back(new Fe(cost, weight, name));
            return true;
        }

        /* add Cu */
        if(name.toLower() == QString("cu"))
        {
            capacity -= weight;
            storage_product.push_back(new Cu(cost, weight, name));
            return true;
        }

        /* add Brick */
        if(name.toLower() == QString("brick"))
        {
            capacity -= weight;
            storage_product.push_back(new Brick(cost, weight, name));
            return true;
        }

        /* add Wood */
        if(name.toLower() == QString("wood"))
        {
            capacity -= weight;
            storage_product.push_back(new Wood(cost, weight, name));
            return true;
        }

        /* add Aniline */
        if(name.toLower() == QString("aniline"))
        {
            capacity -= weight;
            storage_product.push_back(new Aniline(cost, weight, name));
            return true;
        }

        /* add Antifreeze */
        if(name.toLower() == QString("antifreeze"))
        {
            capacity -= weight;
            storage_product.push_back(new Antifreeze(cost, weight, name));
            return true;
        }

        /* add Petroleum */
        if(name.toLower() == QString("petroleum"))
        {
            capacity -= weight;
            storage_product.push_back(new Petroleum(cost, weight, name));
            return true;
        }

        /* add Kerosene */
        if(name.toLower() == QString("kerosene"))
        {
            capacity -= weight;
            storage_product.push_back(new Kerosene(cost, weight, name));
            return true;
        }

        /* add H2 */
        if(name.toLower() == QString("h2"))
        {
            capacity -= weight;
            storage_product.push_back(new H2(cost, weight, name));
            return true;
        }

        /* add C3H8 */
        if(name.toLower() == QString("c3h8"))
        {
            capacity -= weight;
            storage_product.push_back(new C3H8(cost, weight, name));
            return true;
        }

        /* add WaterGas */
        if(name.toLower() == QString("water-gas"))
        {
            capacity -= weight;
            storage_product.push_back(new WaterGas(cost, weight, name));
            return true;
        }

        /* add CokeOvenGas */
        if(name.toLower() == QString("coke-oven-gas"))
        {
            capacity -= weight;
            storage_product.push_back(new CokeOvenGas(cost, weight, name));
            return true;
        }
    }

    return false;
}

QString Stock::get_storage_type() const {return storage_type;}

int Stock::get_capacity() const {return capacity;}

std::vector<Production *> & Stock::get_storage_product() {return storage_product;}

QString Stock::accept(Visitor *v)
{
    return v->visit_stock(*this);
}
