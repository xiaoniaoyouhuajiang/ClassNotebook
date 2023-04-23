#include "landinfo.h"
#include "ui_landinfo.h"

LandInfo::LandInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LandInfo)
{
    ui->setupUi(this);
}

LandInfo::~LandInfo()
{
    delete ui;
}

void LandInfo::on_landInfoButton_clicked()
{
    ui->landInfoWindow->clear();
    ui->landInfoWindow->append(QString::fromStdString(ptr->facade->getLandscapeInfo(ui->posForInfoX->value(), ui->posForInfoY->value())));
}
