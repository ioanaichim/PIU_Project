#pragma once
#include "Element.h"

#include <QGraphicsScene>

//fereastra in care se construieste planificarea
class PlanScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { InsertItem, MoveItem };

    explicit PlanScene(QMenu* itemMenu, QObject* parent = nullptr);

    QColor itemColor() const { return myItemColor; }
    QColor lineColor() const { return myLineColor; }
    void setItemColor(const QColor& color);

    void setLineColor(const QColor& color);

    bool hasChanges();

public slots:
    void setMode(Mode mode);
    void setItemShape(Element::Shape shape);
    void setItemType(Element::ElementType type);

signals:
    void itemInserted(Element* item);
    void itemSelected(QGraphicsItem* item);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) override;

private:

    QMenu* myItemMenu;
    Mode myMode;
    Element::Shape myItemShape;
    Element::ElementType myItemType;
    
    //punctul in care plasez item-ul
    QPointF startPoint;
    //item-ul poate fi colorat diferit si conturul lui de asemenea///cel mai probabil va fi pus in proprietatile elementului
    QColor myItemColor;
    QColor myLineColor;
};

