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
    void test(Field& field);
    Ui::MainWindow *ui;
    CreateGameWindow *window;
public slots:
    void slotSetTableHW(int, int);
private slots:

    void on_actionCreate_new_triggered();

private:

};
#endif // MAINWINDOW_H
