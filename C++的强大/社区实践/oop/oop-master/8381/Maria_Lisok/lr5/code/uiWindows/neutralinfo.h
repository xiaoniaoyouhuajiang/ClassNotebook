#ifndef NEUTRALINFO_H
#define NEUTRALINFO_H

#include <QDialog>
#include "mainwindow.h"

class MainWindow;

namespace Ui {
class NeutralInfo;
}

class NeutralInfo : public QDialog
{
    friend class MainWindow;
    Q_OBJECT

public:
    explicit NeutralInfo(QWidget *parent = nullptr);
    ~NeutralInfo();
    MainWindow* ptr;
private slots:
    void on_neutralInfoButton_clicked();

private:
    Ui::NeutralInfo *ui;
};

#endif // NEUTRALINFO_H
