#pragma once

#include <QGraphicsPixmapItem>
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>

//elementele ce pot fi adaugate in plan:mese,scaune,scena etc.
class Element : public QGraphicsPolygonItem
{
public:
   //enum{table, chair ,scene};

    Element( QMenu* contextMenu, QGraphicsItem* parent = nullptr);

    QPolygonF polygon() const { return myPolygon; }

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;
    //TODO o fct care verifica daca s-a mai schimbat ceva la element, pozitia in special
 
private:
    QPolygonF myPolygon;
    QMenu* myContextMenu;
};



