#ifndef ARROWGRAPHICS_H
#define ARROWGRAPHICS_H

#include <QGraphicsItem>
#include "unitgraphics.h"
class ArrowGraphics : public QGraphicsItem
{
public:
    ArrowGraphics(UnitGraphics *source, UnitGraphics *dest);
    void adjust();
protected:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

private:
    UnitGraphics *source, *dest;
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize = 10;
};

#endif // ARROWGRAPHICS_H
