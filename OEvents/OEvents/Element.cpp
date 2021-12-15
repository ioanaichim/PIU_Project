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
void Element::updateCoordinates()
{
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
        
        updateCoordinates();
    }
    if (change == QGraphicsItem::ItemScaleChange) {
        updateSize();
    }

    return value;
}


