#pragma once
#include "Element.h"

#include <QGraphicsScene>

//fereastra in care se construieste planificarea
class PlanScene : public QGraphicsScene
{
    /* Macro non-standard pentru adăugarea unui comportament dinamic al claselor/obiectelor */
    /* Sintaxa pentru semnale si sloturi nu respectă standardele C++, 
    este prelucrată de MOC, de aceea apare macro-ul Q_OBJECT */
    Q_OBJECT

public:
    /* Proprietati publice */
    enum Mode { InsertItem, MoveItem };

    /* Costructor */
    explicit PlanScene(QMenu* itemMenu, QObject* parent = nullptr);

    /* Gettere si Settere pentru proprietatile private */
    QColor itemColor() const { return myItemColor; }
    QColor lineColor() const { return myLineColor; }

    /* Metode publice */
    void setItemColor(const QColor& color);
    void setLineColor(const QColor& color);
    bool hasChanges();

public slots:
    /* Metode de tip slots */
    void setMode(Mode mode);
    void setItemShape(Element::ShapeType shape);
    void setItemType(Element::ElementType type);

signals:
    /* Metode de tip signals */
    void itemInserted(Element* item);
    void itemSelected(QGraphicsItem* item);


protected:
    /* Metode protected */
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) override;

private:
    /* Metode private */
    QMenu* myItemMenu;
    Mode myMode;
    Element::ShapeType myItemShape;
    Element::ElementType myItemType;
    
    QPointF startPoint;  //punctul in care plasez item-ul
    QColor myItemColor;  //item-ul poate fi colorat diferit si conturul lui de asemenea
    QColor myLineColor;
};

