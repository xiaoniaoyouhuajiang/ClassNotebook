#include "unitgraphics.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

#include "arrowgraphics.h"
#include "mainwindow.h"
//! [8]
UnitGraphics::UnitGraphics(std::size_t id, int x, int y, MainWindow *parent): id(id), parent(parent){
    this->setX(x);
    this->setY(y);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}
QRectF UnitGraphics::boundingRect() const
{
    return QRectF( -30, -30, 60, 60);
}
//! [8]

//! [9]
QPainterPath UnitGraphics::shape() const
{
    QPainterPath path;
    path.addEllipse(-30, -30, 60, 60);
    return path;
}
//! [9]

void UnitGraphics::addEdge(ArrowGraphics *edge){
    this->edgeList.push_back(edge);
}
void UnitGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::green);

    painter->drawEllipse(-30, -30, 60, 60);

    painter->setPen(QPen(Qt::black, 0));

    QFont font = painter->font();
    font.setPixelSize(20);
    painter->setFont(font);

    painter->drawText(-10,-10,QString::number(this->id));

//    QRadialGradient gradient(-3, -3, 10);
//    if (option->state & QStyle::State_Sunken) {
//        gradient.setCenter(3, 3);
//        gradient.setFocalPoint(3, 3);
//        gradient.setColorAt(1, QColor(Qt::yellow).light(120));
//        gradient.setColorAt(0, QColor(Qt::darkYellow).light(120));
//    } else {
//        gradient.setColorAt(0, Qt::yellow);
//        gradient.setColorAt(1, Qt::darkYellow);
//    }
//    painter->setBrush(gradient);

//    painter->setPen(QPen(Qt::black, 0));
//    painter->drawEllipse(-10, -10, 20, 20);
}


QVariant UnitGraphics::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (ArrowGraphics *edge, edgeList)
            edge->adjust();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}
void UnitGraphics::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void UnitGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    parent->focusItem(this->id);
    QGraphicsItem::mouseReleaseEvent(event);

}
//! [12]
