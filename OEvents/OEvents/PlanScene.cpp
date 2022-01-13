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
       /* item->setBrush(myItemColor);*/
        item->updateColor(myItemColor);
  
}
void PlanScene::setLineColor(const QColor& color)
{
    myLineColor = color;
    Element* item = qgraphicsitem_cast<Element*>(selectedItems().first());
   //item->setBrush(myLineColor);
    item->updateColor(myItemColor);
    update();

}

bool PlanScene::hasChanges()
{
   /* const QList<QGraphicsItem*> items = selectedItems();
    const auto cb = [type](const QGraphicsItem* item) { return item->type() == type; };
    return std::find_if(items.begin(), items.end(), cb) != items.end();*/
    return false;
}
bool checkCollide(QGraphicsItem* item, QList<QGraphicsItem*> items) {
    QPointF c1 = item->boundingRect().center();
    foreach(QGraphicsItem * t, items) {
        qreal distance = QLineF(c1, t->boundingRect().center()).length();
        qreal radii = (item->boundingRect().width() + t->boundingRect().width()) / 2;
        if (distance <= radii) return true;
    }
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

    
    switch (myMode) {
    case InsertItem:
        Element* item;
        item = new Element(myItemType,myItemMenu);
        //item->setBrush(myItemColor);
        //addItem(item);
        item->updateCoordinates(mouseEvent->scenePos());
        item->setPos(mouseEvent->scenePos());
        addItem(item);
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
        //daca am vreun element selectat
        if (selectedItems().count() > 0)
        {
            Element* item = qgraphicsitem_cast<Element*>(selectedItems().first());
            int myidx = this->items().indexOf(item);
            QList<QGraphicsItem*> itemlist = this->items();
            itemlist.removeAt(myidx);
            //check collision
            if (!checkCollide(item, itemlist))
            {
                //no collision
                item->updateColor(Qt::green);
                item->setBrush(Qt::green);
            }
            else
            {
                //collision!!!!!
                item->updateColor(Qt::red);
                item->setBrush(Qt::red);
                //reset position
                //DoCollision();
            }
        }
    }
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

