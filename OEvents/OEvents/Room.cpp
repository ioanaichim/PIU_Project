#include "Room.h"


/* Constructor */
Room::Room(int type, QGraphicsItem* parent)
{
    QPointF myCoordinates = QPointF(0, 0);

    switch (type) {
    case 0://rectangle
        mySize = QSizeF(400, 600);
        myFigure << QPointF(myCoordinates.x(), myCoordinates.y())
            << QPointF(myCoordinates.x() + mySize.width(), myCoordinates.y())
            << QPointF(myCoordinates.x() + mySize.width(), myCoordinates.y() + mySize.height())
            << QPointF(myCoordinates.x(), myCoordinates.y() + mySize.height())
            << QPointF(myCoordinates.x(), myCoordinates.y());
        break;

    case 1://L shaped
        mySize = QSize(700, 1000);
        myFigure << QPointF(myCoordinates.x(), myCoordinates.y())
            << QPointF(myCoordinates.x() + mySize.width(), myCoordinates.y())
            << QPointF(myCoordinates.x() + mySize.width(), myCoordinates.y() + mySize.height())
            << QPointF(myCoordinates.x() + mySize.width() / 2, myCoordinates.y() + mySize.height())
            << QPointF(myCoordinates.x() + mySize.width() / 2, myCoordinates.y() + mySize.height() / 2)
            << QPointF(myCoordinates.x(), myCoordinates.y() + mySize.height() / 2)
            << QPointF(myCoordinates.x(), myCoordinates.y());
        break;
    }

    setPolygon(myFigure);
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, false);
}
