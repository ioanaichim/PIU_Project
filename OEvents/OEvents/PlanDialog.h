#pragma once
#include <iostream>
#include "PlanScene.h"
#include <QToolBox>

#include <QtWidgets>

using namespace std;
class Room : public QGraphicsPolygonItem
{
public:

    //constructor cu valori default
    
    Room(int type=1,QGraphicsItem* parent = nullptr);


    QSizeF getmySize() { return mySize; }

    QPolygonF polygon() const { return myFigure; }
    void setmyfigure(QPolygonF figure) { myFigure = figure; setPolygon(myFigure); }
    void updateSize(QSizeF size) { mySize = size; }
private:
    QPolygonF myFigure;
    QSizeF mySize;
};

class PlanDialog:public QDialog
{
    Q_OBJECT
public:
	explicit PlanDialog(Room *r,QWidget* parent= nullptr);
    
    Room* getmyRoom() { return myRoom; }
signals:
    void planInserted();
public slots:
    void changePrecision(int decimals);
    void setSize();
    void accept();
    void setRoom(int idx);

    void closeEvent(QCloseEvent* event)override;
    
private:
    void createRoomPropertiesBoxes();
    QDoubleSpinBox* widthSpinBox;
    QDoubleSpinBox* heightSpinBox;
    QGroupBox* doubleSpinBoxesGroup;
    Room* myRoom;
};


