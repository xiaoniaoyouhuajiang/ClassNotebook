#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

 class Node;

 class Edge : public QGraphicsItem
 {
 public:
     Edge(Node *sourceNode, Node *destNode);

     Node *sourceNode() const;
     Node *destNode() const;

     void adjust();

     enum { Type = UserType + 2 };
     int type() const { return Type; }

 protected:
     QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

 private:
     Node *source, *dest;

     QPointF sourcePoint;
     QPointF destPoint;
     qreal arrowSize;
 };

 #endif

//#endif // EDGE_H
