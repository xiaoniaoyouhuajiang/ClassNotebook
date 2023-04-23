#pragma once

#include <QWidget>

class Object;


namespace Ui {
class AttributeWidget;
}

class AttributeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AttributeWidget(QWidget *parent = 0);
    ~AttributeWidget();

    void setValues(Object* object);

private:
    Ui::AttributeWidget *ui;
};
