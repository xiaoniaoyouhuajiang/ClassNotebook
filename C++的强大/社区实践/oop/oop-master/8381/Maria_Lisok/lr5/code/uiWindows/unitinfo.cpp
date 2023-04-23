#include "unitinfo.h"
#include "ui_unitinfo.h"

UnitInfo::UnitInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UnitInfo)
{
    ui->setupUi(this);
}

UnitInfo::~UnitInfo()
{
    delete ui;
}

void UnitInfo::on_unitInfoButton_clicked()
{
    ui->unitInfoWindow->clear();
    ui->unitInfoWindow->append(QString::fromStdString(ptr->facade->getUnitInfo(ui->posForInfoX->value(), ui->posForInfoY->value())));
}
