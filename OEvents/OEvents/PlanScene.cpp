#include "PlanScene.h"

/* Constructor pentru suprafata pe care se vor aseza elemente */
PlanScene::PlanScene(QMenu* itemMenu, QObject* parent)
    : QGraphicsScene(parent)
{
    myItemMenu = itemMenu;
    myMode = Mode::MoveItem;
    
    myItemColor = Qt::white;
    myLineColor = Qt::black;
}

/* Metoda publica pentru setarea culorii item-urilor */
void PlanScene::setItemColor(const QColor& color)
{
    myItemColor = color;
        Element* item = qgraphicsitem_cast<Element*>(selectedItems().first());
       /* item->setBrush(myItemColor);*/
        item->updateColor(myItemColor);
  
}


/* Metoda publica pentru verificarea schimbarilor */
bool PlanScene::hasChanges()
{
  
    return false;
}

/* Functie publica pentru reasezarea in cazul coliziunii */
void solveCollission(QGraphicsItem* itemCollided, QGraphicsItem* myitem)
{

    qreal wc = itemCollided->boundingRect().width();
    qreal hc = itemCollided->boundingRect().height();
    qreal myw = myitem->boundingRect().width();
    qreal myh = myitem->boundingRect().height();
    
    
        qreal xdist = itemCollided->pos().x()+wc/2 -( myitem->pos().x()+myw/2);
        qreal ydist = itemCollided->pos().y()-hc/2 - (myitem->pos().y()-myh/2);
        qreal xmin = (myw + wc) / 2;
        qreal ymin = (myh + hc) / 2;
       
        QPointF newPos = myitem->pos();

        if (xmin > abs(xdist) && xdist<0) newPos.setX(newPos.x() + xmin + xdist);//in dreapta obiectului
        if (xmin > abs(xdist) && xdist>0)  newPos.setX(newPos.x() - xmin + xdist);//in stanga obiectului
        /*if (ymin > abs(ydist) && ydist<0) newPos.setY(newPos.y() + ymin - ydist);
        if (ymin > abs(ydist) && ydist >0) newPos.setY(newPos.y() - ymin + ydist);*/
        myitem->setPos(newPos);

}
/* Metoda publica pentru detectarea coliziunilor */
bool checkCollide(QGraphicsItem* item, QList<QGraphicsItem*> items) {
    QPointF center = item->boundingRect().center();
    foreach(QGraphicsItem * t, items) {
        /*QPointF tc = t->boundingRect().center();
        qreal xmin = (item->boundingRect().width() + t->boundingRect().width()) / 2;
        qreal ymin = (item->boundingRect().height() + t->boundingRect().height()) / 2*/
        /* qreal distance = QLineF(center, tc).length();
         qreal radii = (item->boundingRect().width() + t->boundingRect().width()) / 2;
         if (distance <= radii) return true;*/
        if (item->collidesWithItem(t))
        {
            solveCollission(t, item);
            return true;
        }

    }
    return false;
}

/* Metoda publica pentru setarea formei item-ului */
void PlanScene::setItemShape(Element::ShapeType shape)
{
    myItemShape = shape;
}

/* Metoda publica pentru setarea tipului item-ului */
void PlanScene::setItemType(Element::ElementType type)
{
    myItemType = type;
}

/* Metoda publica */
void PlanScene::setMode(Mode mode)
{
    myMode = mode;
}

/* Metoda publica pentru tratarea evenimentului mousePress al mouse-ului */
void PlanScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    
    switch (myMode) {
    case InsertItem:
        Element* item;
        item = new Element(myItemType,myItemMenu,myRoom);
        item->setBrush(item->getmyColor());
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

/* Metoda publica pentru tratarea evenimentului mouseMove al mouse-ului */
void PlanScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (myMode == MoveItem) {
       
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

/* Metoda publica pentru tratarea evenimentului mouseRelease al mouse-ului */
void PlanScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (myMode == InsertItem)
    {
        if (selectedItems().count() > 0)
        {
            Element* item = qgraphicsitem_cast<Element*>(selectedItems().first());
            int myidx = this->items().indexOf(item);
            QList<QGraphicsItem*> itemlist = this->items();
            itemlist.removeAt(myidx);//remove item selectat
            itemlist.removeLast();//remove item room
            //check collision
            checkCollide(item, itemlist);
        }
        myMode = Mode::MoveItem;
    }
    else if (myMode == MoveItem)
    {
        //daca am vreun element selectat
        if (selectedItems().count() > 0)
        {
            Element* item = qgraphicsitem_cast<Element*>(selectedItems().first());
            int myidx = this->items().indexOf(item);
            QList<QGraphicsItem*> itemlist = this->items();
            itemlist.removeAt(myidx);//remove item selectat
            itemlist.removeLast();//remove item room
            //check collision
            if (!checkCollide(item, itemlist))
            {
                //no collision
               
                //item->setBrush(Qt::green);
            }
            else
            {
                //collision!!!!!
               
                //item->setBrush(Qt::black);
                //reset position
                //DoCollision();
            }
        }
    }
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

