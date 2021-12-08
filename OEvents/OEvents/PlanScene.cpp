#include "PlanScene.h"

// suprafata pe care se vor aseza elemente
PlanScene::PlanScene(QMenu* itemMenu, QObject* parent)
    : QGraphicsScene(parent)
{
    myItemMenu = itemMenu;
    myMode = MoveItem;
    
    myItemColor = Qt::white;
    myLineColor = Qt::black;
}


void PlanScene::setItemColor(const QColor& color)
{
    myItemColor = color;
        Element* item = qgraphicsitem_cast<Element*>(selectedItems().first());
        item->setBrush(myItemColor);
  
}

bool PlanScene::hasChanges()
{
    return false;
}

void PlanScene::setMode(Mode mode)
{
    myMode = mode;
}


void PlanScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    Element* item;
    switch (myMode) {
    case InsertItem:
        item = new Element(myItemMenu);
        item->setBrush(myItemColor);
        addItem(item);
        item->setPos(mouseEvent->scenePos());
        emit itemInserted(item);
        break;
       

    default:
        ;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void PlanScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (myMode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void PlanScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

