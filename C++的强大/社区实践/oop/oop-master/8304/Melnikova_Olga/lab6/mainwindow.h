#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <QMainWindow>
#include "creategamewindow.h"
#include "field/field.h"
#include "field/cell.h"
#include "objects/object.h"
#include "objects/units/archer.h"
#include "objects/units/crossbowman.h"
#include "objects/units/heavyrider.h"
#include "objects/units/lightrider.h"
#include "objects/units/knight.h"
#include "objects/units/spearman.h"
#include "fabrics/objectFabric.h"
#include "game.h"
#include "facade.h"
#include "caretaker.h"
#include "rules.h"
#include "rule1.h"
#include "rule2.h"



/*class Game{ //?????????????????????????????????????????????????????????????????????
public:
    Game(int h, int w);
};*/

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void show_table(Field& field);
    void show_table();
    void del_table();
    void process(int h,int w);
    Ui::MainWindow *ui;
    CreateGameWindow *window;
public slots:
    void slotSetTableHW(int, int, bool, bool, bool);
private slots:
    void Cliked(int, int);

    void on_actionCreate_new_triggered();

    void on_pushButton_clicked();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

private:
    bool isUnitSelected = false;
    bool logToFile = false;
    bool logToTerminal = false;
    bool withoutLog = false;
    Object* selectedUnit;
    Game<Rules>* game = new Game<Rules>();

};
#endif // MAINWINDOW_H
