#ifndef UNITGRAPHICS_H
#define UNITGRAPHICS_H
class ArrowGraphics;
class MainWindow;
#include <QGraphicsItem>
//#include "mainwindow.h"
class UnitGraphics: public QGraphicsItem
{
public:

    std::size_t id;
    MainWindow *parent;

    UnitGraphics(std::size_t id, int x, int y, MainWindow *parent);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void addEdge(ArrowGraphics *edge);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    QList<ArrowGraphics *> edgeList;
};

#endif // UNITGRAPHICS_H
