#pragma once

#include <QWidget>

namespace Ui {
class PlayerWidget;
}

class PlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerWidget(QWidget *parent = nullptr);
    ~PlayerWidget();
    void setPlayer(uint16_t playerId);

private:
    Ui::PlayerWidget *ui;
};
