#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myexception.h"

#include <QLabel>
#include <algorithm>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), file_log("lab5_log.txt"), cache_log(file_log), city_status_maker(new CityStatusMaker)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_stock_clicked()
{   
    for(City &city: cities)
        if(city.get_name().toLower() == ui->toward_city->text().toLower())
        {
            try {
                Stock& new_stock = city.add_stock(ui->product_type->text(), ui->stock_capacity->text().toInt());
                graph_cities.update_vertex(city);
                cities_actions += "Toward " + city.get_name() + "was added new stock(" +
                        new_stock.get_storage_type() + "/" + QString::number(new_stock.get_capacity()) +")\n";
                cache_log.log_data("Toward " + city.get_name() + "was added new stock(" +
                                   new_stock.get_storage_type() + "/" + QString::number(new_stock.get_capacity()) +")\n");

                map_cities_status[city] = city_status_maker->visit_city(city);
            } catch (MyException & ex) {
                 QMessageBox::information(this, ex.get_action_error(), ex.get_data_state());
                 return;
            }

            cities_status = "";

            for(auto& status: map_cities_status)
                cities_status += status.second;

            break;
        }

    ui->CitiesActions->setWidget(new QLabel(cities_actions));
    ui->CitiesStatus->setWidget(new QLabel(cities_status));
}

void MainWindow::on_add_city_clicked()
{
    QString name = ui->city_name->text();

    try {
        for(City city: cities)
            if(city.get_name() == name)
                throw MyException("Add city error", "City " + city.get_name() + " already exists!");
    } catch (MyException & ex) {
        QMessageBox::information(this, ex.get_action_error(), ex.get_data_state());
        return;
    }

    cities_status += "City: " + name + ":\n";
    cities_actions += "Was added city: " + name + "\n";
    cities.push_back(City(name));
    //graph_cities.add_vertex(cities.back());
    map_cities_status[cities.back()] = name.toLower() + ":\n";
    QLabel *info = new QLabel(cities_status);
    QFont f("Arial", 20, QFont::Bold);
    info->setFont(f);
    ui->CitiesStatus->setWidget(info);
    ui->CitiesStatus->setWidget(new QLabel(cities_status));
}

void MainWindow::on_add_product_clicked()
{
    bool added = false;

    for(auto& city : cities)
        if(ui->toward_city_2->text().toLower() == city.get_name().toLower())
        {
            for(auto& stock : city.get_stocks())
                if(stock.add_product(ui->product_type_2->text(), ui->product_name->text(),
                                  ui->weight->text().toInt(), ui->cost->text().toInt()))
                {
                    graph_cities.update_vertex(city);
                    Production *p = stock.get_storage_product().back();
                    cities_actions +=  "Toward " + city.get_name() + "was imported new product(" +
                            p->get_final_product_name() + "/" + QString::number(p->get_weight()) +
                            p->get_units() + "/" + QString::number(p->get_cost()) + "$" + ")\n";
                    cache_log.log_data("Toward " + city.get_name() + "was imported new product(" +
                                       p->get_final_product_name() + "/" + QString::number(p->get_weight()) +
                                       p->get_units() + "/" + QString::number(p->get_cost()) + "$" + ")\n");
                    map_cities_status[city] = city_status_maker->visit_city(city);

                    cities_status = "";

                    for(auto& status: map_cities_status)
                        cities_status += status.second;

                    added = true;

                    break;
                }
            break;
        }

    if(!added)
    {
        MyException ex("Add product error", "Doenst exist stock in city " + ui->toward_city_2->text() +
                       " for storage product " + ui->product_name->text());
        QMessageBox::information(this, ex.get_action_error(), ex.get_data_state());
        return;
    }

    ui->CitiesActions->setWidget(new QLabel(cities_actions));
    ui->CitiesStatus->setWidget(new QLabel(cities_status));
}

void MainWindow::on_add_transport_btn_clicked()
{
    for(auto & city : cities)
        if(city.get_name().toLower() == ui->toward_city_3->text().toLower())
        {
            vector<QString> transported_type;
            bool carry_passengers = ui->checkBoxPassengersAvl->isChecked();
            QString carry_passengers_status = carry_passengers ? "(Carry passangers)" : "(Doesnt carry passengers)";

            if(ui->checkBoxSolid->isChecked())
                transported_type.push_back("Solid");
            if(ui->checkBoxLiquid->isChecked())
                transported_type.push_back("Liquid");
            if(ui->checkBoxGaseous->isChecked())
                transported_type.push_back("Gaseous");

            try
            {
                if(Transport *t = city.add_transport(ui->transport_name->text(), transported_type, ui->move_cost->text().toInt(),
                                   ui->transport_capacity->text().toInt(), ui->checkBoxPassengersAvl->isChecked()))
                {
                    graph_cities.update_vertex(city);
                    QString transported_type = "[";

                    for(QString type : t->get_transported_type())
                        transported_type += type + " ";

                    transported_type += "]";
                    cities_actions += "Toward " + ui->city_name->text() + " was appended " + t->get_transport_type() + " transport(" +
                            t->get_name() + "/" + QString::number(t->get_capacity()) + "/" + transported_type + "/" +
                            carry_passengers_status + ")\n";
                    cache_log.log_data("Toward " + ui->city_name->text() + " was appended " + t->get_transport_type() + " transport(" +
                                       t->get_name() + "/" + QString::number(t->get_capacity()) + "/" + transported_type + "/" +
                                       carry_passengers_status + ")\n");
                    map_cities_status[city] = city_status_maker->visit_city(city);
                    cities_status = "";

                    for(auto& status: map_cities_status)
                        cities_status += status.second;
                }
            }
            catch(MyException &ex)
            {
                QMessageBox::information(this, ex.get_action_error(), ex.get_data_state());
                return;
            }

            break;
        }

    ui->CitiesActions->setWidget(new QLabel(cities_actions));
    ui->CitiesStatus->setWidget(new QLabel(cities_status));
}

void MainWindow::on_remove_transport_btn_clicked()
{
    bool removed = false;

    for(auto & city : cities)
    {
        QString c_name = ui->toward_city_4->text().toLower();

        if(city.get_name().toLower() == c_name)
        {
            QString t_name = ui->transport_name_2->text().toLower();
            int capacity = ui->transport_capacity_2->text().toInt();
            bool carry_passengers = ui->checkBoxPassengersAvl_2->isChecked();
            QString carry_passengers_status = carry_passengers ? "(Carry passangers)" : "(Doesnt carry passengers)";
            int idx = 0;

            for(auto & t : city.get_transports())
            {
                if(t->get_name().toLower() == t_name && t->get_capacity() == capacity &&
                        t->get_passenger_type_available() == carry_passengers)
                {
                    city.get_transports().erase(city.get_transports().begin() + idx);
                    graph_cities.update_vertex(city);
                    cities_actions += "From " + c_name + " was removed transport: " + t->get_transport_type() + " transport(" +
                            t->get_name() + "/" + QString::number(t->get_capacity()) + "/" +
                            carry_passengers_status + ")\n";
                    cache_log.log_data("From " + c_name + " was removed transport: " + t->get_transport_type() + " transport(" +
                                       t->get_name() + "/" + QString::number(t->get_capacity()) + "/" +
                                       carry_passengers_status + ")\n");

                    //remake city status
                    map_cities_status[city] = city_status_maker->visit_city(city);
                    cities_status = "";

                    for(auto& status: map_cities_status)
                        cities_status += status.second;

                    removed = true;

                    break;
                }

                ++idx;
            }

            break;
        }
    }

    if(!removed)
    {
        MyException ex("Remove tranport error", "Can't remove transport " + ui->transport_name_2->text()
                       + " from " + ui->toward_city_4->text() + " city");
        QMessageBox::information(this, ex.get_action_error(), ex.get_data_state());
        return;
    }

    ui->CitiesActions->setWidget(new QLabel(cities_actions));
    ui->CitiesStatus->setWidget(new QLabel(cities_status));
}

void MainWindow::on_replace_transport_btn_clicked()
{
    bool has_from = false, has_to = false;
    QString from = ui->toward_city_5->text().toLower(), to = ui->toward_city_6->text().toLower();

    for(auto & city : cities)
        if(city.get_name().toLower() == from)
            has_from = true;
        else if(city.get_name().toLower() == to)
            has_to = true;

    if(!has_to || !has_from)
    {
        MyException ex("Replace transport error", "City " + from + " or " + to + " doesn't exist");
        QMessageBox::information(this, ex.get_action_error(), ex.get_data_state());
        return;
    }

    bool removed = false;
    vector<QString> transported_types;
    QString transport_type;
    int cost;

    for(auto & city : cities)
    {
        QString c_name = ui->toward_city_5->text().toLower();

        if(city.get_name().toLower() == c_name)
        {
            QString t_name = ui->transport_name_3->text().toLower();
            int capacity = ui->transport_capacity_3->text().toInt();
            bool carry_passengers = ui->checkBoxPassengersAvl_3->isChecked();
            QString carry_passengers_status = carry_passengers ? "(Carry passangers)" : "(Doesnt carry passengers)";
            int idx = 0;

            for(auto & t : city.get_transports())
            {
                if(t->get_name().toLower() == t_name && t->get_capacity() == capacity &&
                        t->get_passenger_type_available() == carry_passengers)
                {
                    transported_types = t->get_transported_type();
                    cost = t->get_cost();
                    transport_type = t->get_transport_type();
                    city.get_transports().erase(city.get_transports().begin() + idx);
                    graph_cities.update_vertex(city);
                    cities_actions += "From " + c_name + " was removed transport: " + t->get_transport_type() + " transport(" +
                            t->get_name() + "/" + QString::number(t->get_capacity()) + "/" +
                            carry_passengers_status + ")\n";
                    cache_log.log_data("From " + c_name + " was removed transport: " + t->get_transport_type() + " transport(" +
                                       t->get_name() + "/" + QString::number(t->get_capacity()) + "/" +
                                       carry_passengers_status + ")\n");

                    //remake city status
                    map_cities_status[city] = city_status_maker->visit_city(city);
                    cities_status = "";

                    for(auto& status: map_cities_status)
                        cities_status += status.second;

                    removed = true;

                    break;
                }

                ++idx;
            }

            break;
        }
    }

    try
    {
        if(removed)
        {
            for(auto & city : cities)
            {
                QString to_c_name = ui->toward_city_6->text().toLower();

                if(city.get_name().toLower() == to_c_name)
                {
                    QString t_name = ui->transport_name_3->text().toLower();
                    int capacity = ui->transport_capacity_3->text().toInt();
                    bool carry_passengers = ui->checkBoxPassengersAvl_3->isChecked();
                    QString carry_passengers_status = carry_passengers ? "(Carry passangers)" : "(Doesnt carry passengers)";

                    city.add_transport(t_name, transported_types, cost, ui->transport_capacity_3->text().toInt(),
                                       ui->checkBoxPassengersAvl_3->isChecked());
                    graph_cities.update_vertex(city);
                    cities_actions += "Toward " + to_c_name + " wad added transport " +  transport_type + " transport(" +
                            t_name + "/" + QString::number(capacity) +  "/" +
                            carry_passengers_status + ")\n";
                    cache_log.log_data("Toward " + to_c_name + " wad added transport " +  transport_type + " transport(" +
                                       t_name + "/" + QString::number(capacity) +  "/" +
                                       carry_passengers_status + ")\n");

                    map_cities_status[city] =  city_status_maker->visit_city(city);
                    cities_status = "";

                     for(auto& status: map_cities_status)
                         cities_status += status.second;

                     break;
                }
            }
        }
        else
            throw MyException("Replace transport error", "Can't replace transport " + ui->transport_name_3->text() +
                              " from " + ui->toward_city_5->text() + " to " + ui->toward_city_6->text());
    }
    catch(MyException & ex)
    {
        QMessageBox::information(this, ex.get_action_error(), ex.get_data_state());
        return;
    }

    ui->CitiesActions->setWidget(new QLabel(cities_actions));
    ui->CitiesStatus->setWidget(new QLabel(cities_status));
}

void MainWindow::on_add_road_clicked()
{
    QString city1 = ui->city1->text().toLower();
    QString city2 = ui->city2->text().toLower();
    City c1(""), c2("");
    vector<QString> road_types;
    bool has_city1 = false, has_city2 = false;
    bool added = false;

    for(auto & city : cities)
    {
        if(city.get_name().toLower() == city1)
        {
            has_city1 = true;
            c1 = city;
        }
        else if(city.get_name().toLower() == city2)
        {
            has_city2 = true;
            c2 = city;
        }

        QString type_info;

        if(has_city1 && has_city2)
        {
            if(ui->checkBoxLand->isChecked())
                road_types.push_back("Land");
            if(ui->checkBoxWater->isChecked())
                road_types.push_back("Water");
            if(ui->checkBoxAir->isChecked())
                road_types.push_back("Air");

            for(auto & type : road_types)
                type_info += type + " ";

            try
            {
                graph_cities.add_edge(c1, c2, ui->road_cost->text().toInt(), road_types);
                cities_actions += "Was built road between " + city1 + " and " + city2 + "/" + ui->road_cost->text() + "/" +
                            "[" + type_info + "]" + "\n";
                cache_log.log_data("Was built road between " + city1 + " and " + city2 + "/" + ui->road_cost->text() + "/" +
                            "[" + type_info + "]" + "\n");

                added = true;
            }
            catch(MyException & ex)
            {
                QMessageBox::information(this, ex.get_action_error(), ex.get_data_state());
                return;
            }

            break;
        }
    }

    if(!added)
    {
        MyException ex("Add road error", "City " + city1 + " or " + city2 + " doesn't exist");
        QMessageBox::information(this, ex.get_action_error(), ex.get_data_state());
        return;
    }

    ui->CitiesActions->setWidget(new QLabel(cities_actions));
}

void MainWindow::on_transport_production_clicked()
{
    QString city1 = ui->city1_2->text().toLower(), city2 = ui->city2_2->text().toLower();
    QString product_name = ui->transporting_product_name->text().toLower();
    int weight = ui->weight_2->text().toInt();
    int count_passengers = 0;
    City *from = nullptr, *to = nullptr;
    Production * p = nullptr;
    int cost = 0;

    if(ui->count_passengers->text().length()!= 0)
        count_passengers = ui->count_passengers->text().toInt();

    for(auto & city : cities)
        if(city.get_name().toLower() == city1)
        {
            from = &city;

            for(auto & stock : from->get_stocks())
            {
                for(auto & product : stock.get_storage_product())
                    if(product->get_final_product_name().toLower() == product_name && product->get_weight() >= weight)
                    {
                        p = product;
                        break;
                    }

                if(p)
                    break;
            }
        }
        else if(city.get_name().toLower() == city2)
            to = &city;

    if(from && p && to)
    {
        qDebug() << "Start greedy_algorithm";

        try
        {
            if((cost = greedy_algorith(*from, *to, graph_cities, p, weight, count_passengers)))
            {
                qDebug() << "Success greedy";
                //add product
                for(auto & stock : to->get_stocks())
                    if(stock.get_storage_type().toLower() == p->get_product_type().toLower())
                    {
                        stock.add_product(p->get_product_type(), p->get_final_product_name(), weight, p->get_cost());
                        break;
                    }

                //remove part of product
                if(weight < p->get_weight())
                    p->decrease_weight(weight);
                else
                //remove product
                    for(auto & stock : from->get_stocks())
                    {
                        int idx = 0;
                        bool removed = false;

                        for(auto & product : stock.get_storage_product())
                        {
                            if(product->get_final_product_name().toLower() == p->get_final_product_name().toLower())
                            {
                                stock.get_storage_product().erase(stock.get_storage_product().begin() + idx);
                                removed = true;
                                break;
                            }

                            idx += 1;
                        }

                        if(removed)
                            break;
                    }

                cities_actions += "From: " + from->get_name() + " to: " + to->get_name() + " was transported " +
                        p->get_final_product_name() + "/" + QString::number(weight) + "/" + p->get_units() + " by " +
                        QString::number(cost) + " summary cost of transporting\n";
                cache_log.log_data("From: " + from->get_name() + " to: " + to->get_name() + " was transported " +
                                   p->get_final_product_name() + "/" + QString::number(weight) + "/" + p->get_units() + " by " +
                                   QString::number(cost) + " summary cost of transporting\n");

                map_cities_status[*to] = city_status_maker->visit_city(*to);

                //remake from city status
                map_cities_status[*from] = city_status_maker->visit_city(*from);
                cities_status = "";

                for(auto & status: map_cities_status)
                    cities_status += status.second;
            }
        }
        catch(MyException & ex)
        {
            QMessageBox::information(this, ex.get_action_error(), ex.get_data_state());
            return;
        }

    }
    else {
        MyException ex("Transporting production error", "Cities " + city1 + "/" + city2 + " or " + "product " +
                       product_name + " doesn't exist");
        QMessageBox::information(this, ex.get_action_error(), ex.get_data_state());
        return;
    }

    ui->CitiesActions->setWidget(new QLabel(cities_actions));
    ui->CitiesStatus->setWidget(new QLabel(cities_status));
}
