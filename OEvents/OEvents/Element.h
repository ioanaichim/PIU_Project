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
   
    enum ElementType { Table, Chair, Stage, Buffet };
    enum Shape { Round, Square, Rectangle};

    //constructor cu valori default
    Element(Shape shape, QColor color , QMenu* contextMenu, QSizeF size = { 50, 50 }, QPointF refpoint = { 0,0 }, QGraphicsItem* parent = nullptr);
    Element(ElementType type, QMenu* contextMenu, QGraphicsItem* parent = nullptr);


    QPolygonF polygon() const { return myFigure; }
    void updateCoordinates(QPointF point);
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
    ElementType myType;

public:
    QJsonObject write();
};



