#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "city.h"
#include "graph_cities.h"
#include "logs.h"
#include "visitor.h"
#include <vector>
#include <map>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_add_stock_clicked();

    void on_add_city_clicked();

    void on_add_product_clicked();

    void on_add_transport_btn_clicked();

    void on_remove_transport_btn_clicked();

    void on_replace_transport_btn_clicked();

    void on_add_road_clicked();

    void on_transport_production_clicked();

private:
    Ui::MainWindow *ui;
    vector<City> cities;
    map<City, QString> map_cities_status;
    QString cities_actions;
    QString cities_status;
    graph_cities graph_cities;
    FileLog file_log;
    CacheLog cache_log;
    CityStatusMaker *city_status_maker;
};

#endif // MAINWINDOW_H
