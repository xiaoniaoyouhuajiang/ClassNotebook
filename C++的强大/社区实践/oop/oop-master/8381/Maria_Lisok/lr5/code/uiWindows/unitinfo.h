#ifndef UNITINFO_H
#define UNITINFO_H

#include <QDialog>
#include "mainwindow.h"

class MainWindow;
namespace Ui {
class UnitInfo;
}

class UnitInfo : public QDialog
{
    friend class MainWindow;
    Q_OBJECT

public:
    explicit UnitInfo(QWidget *parent = nullptr);
    ~UnitInfo();
    MainWindow* ptr;
private slots:
    void on_unitInfoButton_clicked();

private:
    Ui::UnitInfo *ui;
};

#endif // UNITINFO_H
