#pragma once
#include <QToolBox>
#include <QtWidgets>

/* ! \class Room
     *\brief Clasã
*/
class Room : public QGraphicsPolygonItem
{
public:

    /* Constructor cu valori default */
    Room(int type = 0, QGraphicsItem* parent = nullptr);

    /* Metode publice */
    QSizeF getmySize() { return mySize; }
    QPolygonF polygon() const { return myFigure; }
    void setmyfigure(QPolygonF figure) { myFigure = figure; setPolygon(myFigure); }
    void updateSize(QSizeF size) { mySize = size; }

private:
    /* Proprietati private */
    QPolygonF myFigure;
    QSizeF mySize;
};
