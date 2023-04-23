#ifndef ADDBASE_H
#define ADDBASE_H

#include <QDialog>
#include "mainwindow.h"

class MainWindow;

namespace Ui {
class AddBase;
}

class AddBase : public QDialog
{
    friend class MainWindow;
    Q_OBJECT

public:
    explicit AddBase(QWidget *parent = nullptr);
    ~AddBase();
    MainWindow* ptr;
private slots:
    void on_addBase_accepted();

private:
    Ui::AddBase *ui;
};

#endif // ADDBASE_H
