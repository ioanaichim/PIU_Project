#include "PlanScene.h"

// suprafata pe care se vor aseza elemente
PlanScene::PlanScene(QMenu* itemMenu, QObject* parent)
    : QGraphicsScene(parent)
{
    myItemMenu = itemMenu;
    myMode = Mode::MoveItem;
    
    myItemColor = Qt::white;
    myLineColor = Qt::black;
}


void PlanScene::setItemColor(const QColor& color)
{
    myItemColor = color;
        Element* item = qgraphicsitem_cast<Element*>(selectedItems().first());
        item->setBrush(myItemColor);
  
}
void PlanScene::setLineColor(const QColor& color)
{
    myLineColor = color;
    Element* item = qgraphicsitem_cast<Element*>(selectedItems().first());
    item->setBrush(myLineColor);
    update();

}

bool PlanScene::hasChanges()
{
    return false;
}

void PlanScene::setItemShape(Element::Shape shape)
{
    myItemShape = shape;
}

void PlanScene::setItemType(Element::ElementType type)
{
    myItemType = type;
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
        item = new Element(myItemType,myItemMenu);
        item->setBrush(myItemColor);
        addItem(item);
        item->updateCoordinates(mouseEvent->scenePos());
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
    if (myMode == InsertItem)  myMode = Mode::MoveItem;
    if (myMode == MoveItem)
    {
        //check collision
        
    }
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

