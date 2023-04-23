#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "facade.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Game* game = nullptr);
    ~MainWindow();



private slots:
    void on_gameInfoButton_clicked();

    void on_addNeutralButton_clicked();

    void on_addUnitButton_clicked();

    void on_baseInfoButton_clicked();

    void on_addBaseButton_clicked();

    void on_moveButton_clicked();

    void on_attackButton_clicked();

    void on_unitInfoButton_clicked();

    void on_landInfoButton_clicked();

    void on_neutralInfoButton_clicked();

private:
    Ui::MainWindow *ui;
    Facade *facade;
};
#endif // MAINWINDOW_H
