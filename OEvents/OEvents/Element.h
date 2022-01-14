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

    enum ShapeType { Round, Rectangle };

      /* Constructor cu valori default */
    Element(ShapeType shape, QColor color, QMenu* contextMenu, QSizeF size = { 50, 50 }, QPointF refpoint = { 0,0 }, QGraphicsItem* parent = nullptr);
    Element(ElementType type, QMenu* contextMenu, QGraphicsItem* parent = nullptr);

    /*QRectF boundingRect() const override;
    
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;*/

    QPointF getmyCoordinates() { return myCoordinates; };
    QSizeF getmySize() { return mySize; }
    QColor getmyColor(){ return myColor; };
    ShapeType getmyShape() { return myShape; }
    ElementType getmyType() { return myType; };

    /* Metode publice */
    QPolygonF polygon() const { return myFigure; }
    void updateCoordinates(QPointF point);
    void updateSize(QSizeF size);
    void updateShape(ShapeType shape);
    void updateColor(QColor color);


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
    ShapeType myShape;
    ElementType myType;
};



