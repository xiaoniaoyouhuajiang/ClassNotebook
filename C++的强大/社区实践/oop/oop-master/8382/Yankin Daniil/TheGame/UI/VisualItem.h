#pragma once

#include <QObject>
#include <QGraphicsPixmapItem>

class Object;


class VisualItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    VisualItem(Object *object, QGraphicsItem *parent = 0);
    ~VisualItem() = default;

private slots:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Object *object;
};
