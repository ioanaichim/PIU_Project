#include "Element.h"
/* Constructor */

Element::Element(ShapeType shape, QColor color, QMenu* contextMenu, QSizeF size , QPointF refpoint, QGraphicsItem* parent )

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
        mySize = QSizeF(80,150);
        myShape = ShapeType::Rectangle;
        myColor = QColor("green");
        break;
    case Chair:
        mySize = QSizeF(35,35);
        myShape = ShapeType::Round;
        myColor = QColor("blue");
        break;
    case Stage:
        mySize = QSizeF(300, 450);
        myShape = ShapeType::Rectangle;
        myColor = QColor("gray");
        break;
    case Buffet:
        mySize = QSizeF(50, 130);
        myShape = ShapeType::Rectangle;
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
void Element::updateShape(ShapeType shape)

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

/* Metoda publica pentru Adaugarea unui element in Json */
QJsonObject Element::write()
{
    QJsonObject chair;
    chair.insert("color", "yellow");
    return chair;
}