#include "ui_mainwindow.h"
#include <base.h>

class Facade {
protected:
    Ui::MainWindow *ui;
    Field *field;

public:
    Facade(Ui::MainWindow *ui, Field *field) : ui(ui), field(field){

    }
};
