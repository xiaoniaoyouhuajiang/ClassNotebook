#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <facate.h>
//#include <field.h>

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
    void on_add_green_dr_clicked();

    void on_add_red_dr_clicked();

    void on_delete_item_clicked();

    void on_move_unit_clicked();

    void on_add_war_fight_clicked();

    void on_add_war_ronin_clicked();

    void on_add_sen_fire_clicked();

    void on_add_sen_lion_clicked();

    void on_bonus_clicked();

private:
    Ui::MainWindow *ui;
    int flag;
    unsigned int n = 5;
    unsigned int m = 5;
    Field *field;
    string logs = "";
    string print = "";
    ConcreteFactoryDragon concreteFactoryDragon;
    ConcreteFactoryWarrior concreteFactoryWarrior;
    ConcreteFactorySentry concreteFactorySentry;
    Base* base;
    Item* fence;
};

#endif // MAINWINDOW_H
