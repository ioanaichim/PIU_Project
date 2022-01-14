#include "Element.h"

Element::Element(ShapeType shape, QColor color, QMenu* contextMenu, QSizeF size , QPointF refpoint, QGraphicsItem* parent )
   
{
    //setez parametrii
    myCoordinates = refpoint;
    myColor = color;
    mySize = size;
    myShape = shape;

    setFigure();
}
Element::Element(ElementType type, QMenu* contextMenu, QGraphicsItem* parent)
{
    
    //setari valori default in functie de tipul elementului
    switch (type)
    {
    case Table:
        mySize = QSizeF(60,50);
        myShape = ShapeType::Rectangle;
        myColor = QColor("green");
        break;
    case Chair:
        mySize = QSizeF(30,30);
        myShape = ShapeType::Round;
        myColor = QColor("blue");
        break;
    case Stage:
        mySize = QSizeF(100, 50);
        myShape = ShapeType::Rectangle;
        myColor = QColor("gray");
        break;
    case Buffet:
        mySize = QSizeF(80, 40);
        myShape = ShapeType::Rectangle;
        myColor = QColor("red");
        break;
    }
    myCoordinates = QPointF(0,0);
    setFigure();
}
void Element::updateCoordinates(QPointF point)
{
    myCoordinates = point;
}
void Element::updateSize(QSizeF size)
{
    mySize = size;
}
void Element::updateShape(ShapeType shape)
{
    myShape = shape;
}
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
        
       //updateCoordinates();
        
    }
    if (change == QGraphicsItem::ItemScaleChange) {
       // updateSize();
        
    }
    if (change == QGraphicsItem::ItemSendsGeometryChanges) {
        // updateShape();

    }

    return value;
}


