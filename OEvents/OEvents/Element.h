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
    enum ElementType { Table, Chair, Stage, Buffet };
    enum Shape { Round, Square, Rectangle};

    //constructor cu valori default
    Element(Shape shape, QColor color , QMenu* contextMenu, QSizeF size = { 10, 10 }, QPointF refpoint = { 50,50 }, QGraphicsItem* parent = nullptr);

    QPolygonF polygon() const { return myFigure; }
    void updateCoordinates();
    void updateSize();
    void updateColor();

protected:
    void setFigure();
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;
    //TODO o fct care verifica daca s-a mai schimbat ceva la element, pozitia in special
    QVariant Element::itemChange(GraphicsItemChange change, const QVariant& value);
 
private:
    QPolygonF myFigure;
    QMenu* myContextMenu;

    QPointF myCoordinates;//precizie float; punctul de referinta este cel din stanga jos
    QSizeF mySize;//precizie float
    QColor myColor;
    Shape myShape;

};



