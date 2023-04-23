#pragma once

#include "QGraphicsView"
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QMouseEvent>
#include <QMenu>
#include "QGraphicsSceneMouseEvent"
#include "iostream"

#include "client_handler.h"

class FieldCellWidgetItem : public QGraphicsItem {
private:
    unsigned int row;
    unsigned int column;
    QGraphicsScene* scene;
    StartGameHandler* handler;
    GameFacade* facade;

    QPixmap critArcherPixmap = QPixmap(":/pictures/crit_archer.png");
    QPixmap critCavalryPixmap = QPixmap(":/pictures/crit_cavalry.png");
    QPixmap critInfantryPixmap = QPixmap(":/pictures/crit_infantry.png");
    QPixmap absorbArcherPixmap = QPixmap(":/pictures/abs_archer.png");
    QPixmap absorbCavalryPixmap = QPixmap(":/pictures/abs_cavalry.png");
    QPixmap absorbInfantryPixmap = QPixmap(":/pictures/abs_infantry.png");

    QPixmap bannerPixmap = QPixmap(":/pictures/banner.png");
    QPixmap templePixmap = QPixmap(":/pictures/temple.png");
    QPixmap forgePixmap = QPixmap(":/pictures/forge.png");
    QPixmap towerPixmap = QPixmap(":pictures/tower.png");

    QPixmap basePixmap = QPixmap(":/pictures/base.png");

public:
    FieldCellWidgetItem(QGraphicsScene* scene, StartGameHandler* handler, GameFacade* facade, unsigned int row, unsigned int column)
        : row(row), column(column)
    {
       setFlags(ItemIsSelectable);
       this->scene = scene;
       this->handler = handler;
       this->facade = facade;
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

        if (option->state & QStyle::State_Sunken)//затонувший
        {
            painter->setBrush(QColor(254, 254, 34, 255));
        }
        else if (option->state & QStyle::State_Selected)//выделение вершины
        {
            painter->setBrush(QColor(254, 254, 34, 255));
            painter->setPen(QPen(QColor(255, 160, 100, 255), 3));
        }
        else
        {
            try {
                switch (facade->getLandscapeType(row, column)) {
                    case GROUND:
                        painter->setBrush(QColor(191, 255, 148, 255));
                        break;
                    case WATER:
                        painter->setBrush(QColor(161, 183, 255, 255));
                        break;
                    case MOUNTAINS:
                        painter->setBrush(QColor(136, 136, 136, 255));
                        break;
                }
            } catch (...) {}
        }
        painter->drawRect(0,0, 60, 60);



        try {
            QRectF rect1(0, 0, 60, 60);
            switch (facade->getNeutralObjectType(row, column)) {
                case FORGE:
                    painter->drawPixmap(rect1, forgePixmap, rect1);
                    break;
                case TEMPLE:
                    painter->drawPixmap(rect1, templePixmap, rect1);
                    break;
                case BANNER:
                    painter->drawPixmap(rect1, bannerPixmap, rect1);
                    break;
                case TOWER:
                    painter->drawPixmap(rect1, towerPixmap, rect1);
                    break;
            }
        } catch (...) { }

        try {
            if(facade->getCreatureType(row, column) == BASE)
            {
                QRectF rect(0,0,60,60);
                painter->drawPixmap(rect, basePixmap, rect);
            }
            else if (facade->getCreatureType(row, column) == UNIT){
                QRectF rect(0, 0, 60, 60);

                switch (facade->getUnitType(row, column)) {
                    case CRIT_ARCHER:
                        painter->drawPixmap(rect, critArcherPixmap, rect);
                        break;
                    case CRIT_CAVALRY:
                        painter->drawPixmap(rect, critCavalryPixmap, rect);
                        break;
                    case CRIT_INFANTRY:
                        painter->drawPixmap(rect, critInfantryPixmap, rect);
                        break;
                    case ABSORB_ARCHER:
                        painter->drawPixmap(rect, absorbArcherPixmap, rect);
                        break;
                    case ABSORB_CAVALRY:
                        painter->drawPixmap(rect, absorbCavalryPixmap, rect);
                        break;
                    case ABSORB_INFANTRY:
                        painter->drawPixmap(rect, absorbInfantryPixmap, rect);
                        break;
                }
            }
        } catch (...) { }
    }

    QRectF boundingRect() const {
        return QRectF(0, 0, 60, 60);
    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event){
        if(event->button() == Qt::LeftButton)
        {
            for(auto i : scene->selectedItems()) i->setSelected(false);
            setSelected(true);
        }
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event)  { }

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
    {
        if(scene->selectedItems().isEmpty() == false && this->isSelected() == false)
        {
            unsigned int rowFrom = dynamic_cast<FieldCellWidgetItem*>(scene->selectedItems().at(0))->row;
            unsigned int columnFrom = dynamic_cast<FieldCellWidgetItem*>(scene->selectedItems().at(0))->column;

            setSelected(true);
            QMenu menu;
            QAction *attackAction = menu.addAction("Attack");
            QAction *moveAction = menu.addAction("Move");
            QAction *selectedAction = menu.exec(event->screenPos());

            if(selectedAction == attackAction){
                try {
                    AttackClientData* data = new AttackClientData(rowFrom, columnFrom, row, column);
                    handler->handle(data);

                } catch (...) {
                }
            } else if (selectedAction == moveAction){
                try {
                    MoveClientData* data = new MoveClientData(rowFrom, columnFrom, row, column);

                    handler->handle(data);

                } catch (...) {

                }{}
            }


            for(auto i : scene->selectedItems()) i->setSelected(false);
        }
    }


};


class FieldWidget : public QGraphicsView
{
    Q_OBJECT
private:
    QGraphicsScene* scene;
    StartGameHandler* handler;
    GameFacade* facade;
    unsigned int rowsAmount;
    unsigned int columnsAmount;
public:
    explicit FieldWidget(QWidget *parent = 0) :
        QGraphicsView(parent)
    {
        scene = new QGraphicsScene(this);
        setScene(scene);
    }

    void setComponents(StartGameHandler* handler, GameFacade* facade){
        this->handler = handler;
        this->facade = facade;
    }

    void updateFieldPicture(unsigned int rowsAmount, unsigned int columnsAmount)
    {
        clear();
        scene->update();
        this->rowsAmount = rowsAmount;
        this->columnsAmount = columnsAmount;
        for(int i = 0; i < rowsAmount; i++)
        {
            for(int j = 0; j < columnsAmount; j++)
            {
                FieldCellWidgetItem* rect = new FieldCellWidgetItem(scene, handler, facade, i, j);
                rect->setPos(QPointF(60 * j, 60 * i));
                scene->addItem(rect);
            }
        }
    }

    void updateFieldPicture()
    {
        scene->update();
    }

    void clear()
    {
        scene->clear();
    }

    bool isAnythingSelected() { return scene->selectedItems().isEmpty()? false: true; }
};
