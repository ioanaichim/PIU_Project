#include "Element.h"

Element::Element(Shape shape, QColor color, QMenu* contextMenu, QSizeF size , QPointF refpoint, QGraphicsItem* parent )
    : QGraphicsPolygonItem(parent), myContextMenu(contextMenu)
{
    //setez parametrii
    myCoordinates = refpoint;
    myColor = color;
    mySize = size;
    myShape = shape;

    setFigure();
}
Element::Element(ElementType type, QMenu* contextMenu, QGraphicsItem* parent):QGraphicsPolygonItem(parent), myContextMenu(contextMenu)
{

    //setari valori default in functie de tipul elementului
    switch (type)
    {
    case Table:
        mySize = QSizeF(60,50);
        myShape = Shape::Rectangle;
        break;
    case Chair:
        mySize = QSizeF(30,30);
        myShape = Shape::Square;
        break;
    case Stage:
        mySize = QSizeF(100, 50);
        myShape = Shape::Rectangle;
        break;
    case Buffet:
        mySize = QSizeF(80, 40);
        myShape = Shape::Rectangle;
        break;
    }
    myColor =QColor("white");
    myCoordinates = QPointF(0,0);
    setFigure();
}
void Element::updateCoordinates(QPointF point)
{
    myCoordinates = point;
}
void Element::updateSize()
{
    
}
void Element::updateColor()
{
}
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


void Element::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}
QVariant Element::itemChange(GraphicsItemChange change, const QVariant& value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        
       // updateCoordinates();
        update();
    }
    if (change == QGraphicsItem::ItemScaleChange) {
       // updateSize();
        update();
    }

    return value;
}


