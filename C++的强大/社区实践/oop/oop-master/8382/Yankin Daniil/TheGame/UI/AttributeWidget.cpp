#include "AttributeWidget.h"
#include "ui_AttributeWidget.h"
#include "Unit/UnitHeader.h"
#include "Base/Base.h"
#include <QString>

AttributeWidget::AttributeWidget(QWidget *parent) : QWidget(parent), ui(new Ui::AttributeWidget) {
    ui->setupUi(this);
}

AttributeWidget::~AttributeWidget() {
    delete ui;
}

void AttributeWidget::setValues(Object* object) {
    if (object == nullptr) return;

    Unit* unit;
    Base* base;
    QString str1, str2;
    switch (object->getGroupType()) {
    case UNIT:
        unit = static_cast <Unit*> (object);

        str1.setNum(static_cast <int> (unit->getHealth()));
        str1.append('/');
        str2.setNum(static_cast <int> (unit->getMaxHealth()));
        str1.append(str2);
        ui->str1Value->setText(str1);

        str1.setNum(static_cast <int> (unit->getAttack()));
        ui->str2Value->setText(str1);

        str1.setNum(static_cast <int> (unit->getArmor()));
        ui->str3Value->setText(str1);

        str1.setNum(static_cast <int> (unit->getMovePoints()));
        str1.append('/');
        str2.setNum(static_cast <int> (unit->getMaxMovePoints()));
        str1.append(str2);
        ui->str4Value->setText(str1);

        break;

    case BASE:
        base = static_cast <Base*> (object);

        str1.setNum(static_cast <int> (base->getHealth()));
        str1.append('/');
        str2.setNum(static_cast <int> (base->getMaxHealth()));
        str1.append(str2);
        ui->str1Value->setText(str1);

        str1.setNum(static_cast <int> (base->getAttack()));
        ui->str2Value->setText(str1);

        str1.setNum(static_cast <int> (base->getArmor()));
        ui->str3Value->setText(str1);

        ui->str4->setText("Unit Count");
        str1.setNum(static_cast <int> (base->getUnitCount()));
        str1.append('/');
        str2.setNum(static_cast <int> (base->getMaxUnitCount()));
        str1.append(str2);
        ui->str4Value->setText(str1);

        break;
    }
}
