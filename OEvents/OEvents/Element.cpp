#include "Element.h"

Element::Element( QMenu* contextMenu,QGraphicsItem* parent)
    : QGraphicsPolygonItem(parent), myContextMenu(contextMenu)
{
    myPolygon << QPointF(-120, -80) << QPointF(-70, 80)
            << QPointF(120, 80) << QPointF(70, -80)
            << QPointF(-120, -80);
     
    setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void Element::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}


