﻿#include "Element.h"

/* Constructor */
Element::Element(Shape shape, QColor color, QMenu* contextMenu, QSizeF size , QPointF refpoint, QGraphicsItem* parent )
{
    //setez parametrii
    myCoordinates = refpoint;
    myColor = color;
    mySize = size;
    myShape = shape;

    setFigure();
}

/* Constructor */
Element::Element(ElementType type, QMenu* contextMenu, QGraphicsItem* parent)
{
    //setari valori default in functie de tipul elementului
    switch (type)
    {
    case Table:
        mySize = QSizeF(60,50);
        myShape = Shape::Rectangle;
        myColor = QColor("green");
        break;
    case Chair:
        mySize = QSizeF(30,30);
        myShape = Shape::Round;
        myColor = QColor("blue");
        break;
    case Stage:
        mySize = QSizeF(100, 50);
        myShape = Shape::Rectangle;
        myColor = QColor("gray");
        break;
    case Buffet:
        mySize = QSizeF(80, 40);
        myShape = Shape::Rectangle;
        myColor = QColor("red");
        break;
    }
    myCoordinates = QPointF(0,0);
    setFigure();
}

/* Metodă publică pentru actualizarea coordonatelor elementului (punctul din stanga sus) */
void Element::updateCoordinates(QPointF point)
{
    myCoordinates = point;
}

/* Metodă publică pentru actualizarea dimensiunii elementului */
void Element::updateSize(QSizeF size)
{
    mySize = size;
}

/* Metodă publică pentru actualizarea formei elementului */
void Element::updateShape(Shape shape)
{
    myShape = shape;
}

/* Metodă publică pentru actualizarea culorii elementului */
void Element::updateColor(QColor color)
{
    myColor = color;
}

//void Element::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
//{
//    QRectF rect = boundingRect();
//
//    QPen pen(myColor, 3);
//    painter->setPen(pen);
//    switch(myShape)
//    {
//    case Round:
//        painter->drawEllipse(rect);
//        break;
//    case Rectangle:
//        painter->drawRect(rect);
//    }
//}
//QRectF Element::boundingRect() const
//{
//    return QRectF(myCoordinates.x(), myCoordinates.y(), mySize.width(), mySize.height());
//}

/* Metodă publică pentru setarea elemetului in functie de coordonatele mouse-ului */
void Element::setFigure()
{
    myFigure << QPointF(myCoordinates.x(), myCoordinates.y())
        << QPointF(myCoordinates.x() + mySize.width(), myCoordinates.y())
        << QPointF(myCoordinates.x() + mySize.width(), myCoordinates.y() + mySize.height())
        << QPointF(myCoordinates.x(), myCoordinates.y() + mySize.height())
        << QPointF(myCoordinates.x(), myCoordinates.y());

    setPolygon(myFigure);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

/* Metodă publică */
void Element::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}
