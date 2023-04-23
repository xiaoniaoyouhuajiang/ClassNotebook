#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controller.h"
#include <QListWidget>
#include "unitgraphics.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    std::map<std::size_t,UnitGraphics*> unitGraphics;
    ~MainWindow();
    void focusItem(std::size_t id);
private:
    Ui::MainWindow *ui;
    QListWidget *lstHandlers;
    Controller controller;
    QGraphicsScene *scene;
    std::map<std::size_t,UnitGraphics*> units;
    std::map<std::size_t,std::size_t> map_row_id;
    void drawBg();
    void loadInfo();

private slots:
    void btnReplace_clicked();
    void btnHandle_clicked();
    void actionSave_triggered();
    void actionLoad_triggered();
    void btnUndo_clicked();

    void btnAdd_clicked();
    void btnDelete_clicked();
    void btnConnect_clicked();
    void btnSetInp_clicked();
    void btnSetOut_clicked();

    void cdAddType_currentIndexChanged(int index);

};

#endif // MAINWINDOW_H
