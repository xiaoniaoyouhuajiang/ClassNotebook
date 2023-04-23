#ifndef LANDINFO_H
#define LANDINFO_H

#include <QDialog>
#include "mainwindow.h"

class MainWindow;

namespace Ui {
class LandInfo;
}

class LandInfo : public QDialog
{
    friend class MainWindow;
    Q_OBJECT

public:
    explicit LandInfo(QWidget *parent = nullptr);
    ~LandInfo();
    MainWindow* ptr;
private slots:
    void on_landInfoButton_clicked();

private:
    Ui::LandInfo *ui;
};

#endif // LANDINFO_H
