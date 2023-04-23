#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include "twoplayersgame.h"
#include <QPainter>
#include <sstream>
#include "gamemode.h"
#include "SingleGame.h"

class PaintWidget : public QWidget
{
    Q_OBJECT
private:
    GameMode mode;
    Game<TwoPlayersRule>* game;
    Game<SingleGameRule>* soloGame;

public:
    explicit PaintWidget(QWidget *parent = nullptr);
    void setGame(Game<TwoPlayersRule>* game);
    QSize sizeHint() const;
    void  setMode(GameMode mode);
    void setSoloGame(Game<SingleGameRule>* game);

protected:
    void paintEvent(QPaintEvent *event);


public slots:
    void paintItPlease();
};

#endif // PAINTWIDGET_H
