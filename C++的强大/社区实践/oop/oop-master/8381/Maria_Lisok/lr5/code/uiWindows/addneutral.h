#ifndef ADDNEUTRAL_H
#define ADDNEUTRAL_H

#include <QDialog>
#include "mainwindow.h"

class MainWindow;
namespace Ui {
class AddNeutral;
}

class AddNeutral : public QDialog
{
    friend class MainWindow;
    Q_OBJECT 
public:
    explicit AddNeutral(QWidget *parent = nullptr);
    ~AddNeutral();
    MainWindow* ptr;
private slots:

    void on_addNeutral_accepted();

    void on_addNeutral_rejected();

private:
    Ui::AddNeutral *ui;
};

#endif // ADDNEUTRAL_H
