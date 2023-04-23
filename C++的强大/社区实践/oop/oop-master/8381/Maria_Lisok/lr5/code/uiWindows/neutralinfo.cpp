#include "neutralinfo.h"
#include "ui_neutralinfo.h"

NeutralInfo::NeutralInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NeutralInfo)
{
    ui->setupUi(this);
}

NeutralInfo::~NeutralInfo()
{
    delete ui;
}

void NeutralInfo::on_neutralInfoButton_clicked()
{
    ui->neutralInfoWindow->clear();
    ui->neutralInfoWindow->append(QString::fromStdString(ptr->facade->getNeutralInfo(ui->posForInfoX->value(), ui->posForInfoY->value())));
}
