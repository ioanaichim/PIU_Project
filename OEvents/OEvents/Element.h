#pragma once

#include <QGraphicsPixmapItem>
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>

/* ! \class Element
     *   \brief Clasă pentru elementele ce pot fi adaugate in plan:mese,scaune,scena,bufet
*/
class Element : public QGraphicsPolygonItem
{
public:
    /* Proprietatile publice ale clasei */ 
    enum ElementType { Table, Chair, Stage, Buffet };
    enum Shape { Round, Rectangle };
    QPointF getmyCoordinates() { return myCoordinates; };
    QSizeF getmySize() { return mySize; }
    QColor getmyColor() { return myColor; };
    Shape getmyShape() { return myShape; };
    ElementType getmyType() { return myType; };

    /* Constructor cu valori default */
    Element(Shape shape, QColor color, QMenu* contextMenu, QSizeF size = { 50, 50 }, QPointF refpoint = { 0,0 }, QGraphicsItem* parent = nullptr);
    Element(ElementType type, QMenu* contextMenu, QGraphicsItem* parent = nullptr);

    /* Metode publice */
    QPolygonF polygon() const { return myFigure; }
    void updateCoordinates(QPointF point);
    void updateSize(QSizeF size);
    void updateShape(Shape shape);
    void updateColor(QColor color);

    /*QRectF boundingRect() const override;
    
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;*/

protected:
    /* Metode protected */
    void setFigure();
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;
    //QVariant itemChange(GraphicsItemChange change, const QVariant& value);
 
private:
    /* Proprietatile private ale clasei */
    QPolygonF myFigure;
    QMenu* myContextMenu;

    QPointF myCoordinates; // precizie float; punctul de referinta este cel din stanga jos
    QSizeF mySize; // precizie float
    QColor myColor;
    Shape myShape;
    ElementType myType;
};



