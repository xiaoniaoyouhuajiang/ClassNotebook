#pragma once

#include <QWidget>


namespace Ui {
class BaseWidget;
}

class BaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BaseWidget(QWidget *parent);
    ~BaseWidget();

private slots:
    void on_swordsmanButton_clicked();
    void on_pikemanButton_clicked();
    void on_shockCavalryButton_clicked();
    void on_archerButton_clicked();
    void on_crossbowmanButton_clicked();
    void on_scoutCavalryButton_clicked();
    void on_catapultButton_clicked();
    void on_ramButton_clicked();

private:
    Ui::BaseWidget *ui;
};
