#pragma once
#include <iostream>
#include "PlanScene.h"
#include "Room.h"
#include <QToolBox>

#include <QtWidgets>

using namespace std;


/* ! \class PlanDialog
     *   \brief Clasă
*/
class PlanDialog:public QDialog
{
    /* Macro non-standard pentru adăugarea unui comportament dinamic al claselor/obiectelor */
    Q_OBJECT
public:
    /* Constructor */
	explicit PlanDialog(Room *r,QWidget* parent= nullptr);
    /* Getter pentru o proprietate privata */
    Room* getmyRoom() { return myRoom; }
signals:
    /* Metoda de tip signal */
    void planInserted();
public slots:
    /* Metoda de tip slots */
    void changePrecision(int decimals);
    void setSize();
    void accept();
    void setRoom(int idx);
    
private:
    /* Metoda privata */
    void createRoomPropertiesBoxes();
    /* Proprietati private */
    QDoubleSpinBox* widthSpinBox;
    QDoubleSpinBox* heightSpinBox;
    QGroupBox* doubleSpinBoxesGroup;
    Room* myRoom;
};


