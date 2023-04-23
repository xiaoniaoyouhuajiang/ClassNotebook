#pragma once

#include "QGraphicsView"
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QMouseEvent>
#include <QMenu>
#include <QPalette>
#include "QGraphicsSceneMouseEvent"
#include "iostream"

#include "clientHandler.h"

class FieldCellWidgetItem : public QGraphicsItem
{
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

    QPixmap bannerPixmap = QPixmap(":/pictures/banner.png"); //armorHouse
    QPixmap templePixmap = QPixmap(":/pictures/temple.png"); //village
    QPixmap forgePixmap = QPixmap(":/pictures/forge.png"); //GunSmith
    QPixmap towerPixmap = QPixmap(":/pictures/tower.png"); //boostTower

    QPixmap basePixmap = QPixmap(":/pictures/base.png");


    QPixmap waterPixmap = QPixmap(":/pictures/water.png");
    QPixmap groundPixmap = QPixmap(":/pictures/ground.jpg");
    QPixmap mountainPixmap = QPixmap(":/pictures/mnt.jpg");
    QPixmap cursorPixmap = QPixmap(":/pictures/red.jfif");


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

        int flag;
        QImage img;

        QRectF rect122(0, 0, 100, 100);

        if (option->state & QStyle::State_Sunken)//затонувший
        {
            //painter->setBrush(QColor(254, 254, 34, 255));
            painter->drawPixmap(rect122, cursorPixmap, rect122);
        }
        else if (option->state & QStyle::State_Selected)//выделение вершины
        {
            flag = 1;
            //painter->setBrush(QColor(254, 254, 34, 255));
            //painter->setPen(QPen(QColor(255, 160, 100, 255), 3));
            //img.load("D:\\Qtprojects/code/pictures/water.png");
            painter->drawPixmap(rect122, cursorPixmap, rect122);
        }
        else
        {
            flag = 0;
            try {
                switch (facade->getLandscapeType(row, column)) {
                    case GROUND:
                        painter->setBrush(QColor(191, 255, 148, 255));
                        //img.load("D:\\Qtprojects/code/pictures/ground.png");
                        painter->drawPixmap(rect122, groundPixmap, rect122);

                        break;
                    case WATER:
                        painter->setBrush(QColor(161, 183, 255, 255));
                        //img.load("D:\\Qtprojects/code/pictures/water.png");
                        painter->drawPixmap(rect122, waterPixmap, rect122);

                        break;
                    case MOUNTAINS:
                        painter->setBrush(QColor(136, 136, 136, 255));
                        //img.load("D:\\Qtprojects/code/pictures/mountain.png");
                        painter->drawPixmap(rect122, mountainPixmap, rect122);

                        break;
                }
            } catch (...) {}
        }

        //if(flag == 1)
           // painter->drawPixmap(rect122, cursorPixmap, rect122);
        //else if(flag == 0)
          //  painter->drawPixmap(rect122, forgePixmap, rect122);



        try {
            QRectF rect1(0, 0, 100, 100);
            switch (facade->getNeutralObjectType(row, column)) {
                case GUNSMITH:
                    painter->drawPixmap(rect1, forgePixmap, rect1);
                    break;
                case VILLAGE:
                    painter->drawPixmap(rect1, templePixmap, rect1);
                    break;
                case ARMORHOUSE:
                    painter->drawPixmap(rect1, bannerPixmap, rect1);
                    break;
                case BOOSTTOWER:
                    painter->drawPixmap(rect1, towerPixmap, rect1);
                    break;
            }
        } catch (...) { }

        try {
            if(facade->getCreatureType(row, column) == BASE)
            {
                QRectF rect(0,0,100,100);
                painter->drawPixmap(rect, basePixmap, rect);
            }
            else if (facade->getCreatureType(row, column) == UNIT){
                QRectF rect(0, 0, 100, 100);

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
        return QRectF(0, 0, 100, 100);
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

            QAction *moveAction = menu.addAction("Движение");
            QAction *attackAction = menu.addAction("Атака");

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
        this->rowsAmount = rowsAmount;
        this->columnsAmount = columnsAmount;
        for(int i = 0; i < rowsAmount; i++)
        {
            for(int j = 0; j < columnsAmount; j++)
            {
                FieldCellWidgetItem* rect = new FieldCellWidgetItem(scene, handler, facade, i, j);
                rect->setPos(QPointF(100 * j, 100 * i));
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
