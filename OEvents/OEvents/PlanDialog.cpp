#include "PlanDialog.h"

PlanDialog::PlanDialog(Room *r,QWidget* parent)
    
{
    myRoom = r;
    resize(400, 400);
    QListWidget* templates=new QListWidget(this);
    QListWidgetItem* item = new QListWidgetItem(QIcon(":/images/tmp1.png"), tr("Rectangle shape"));
    templates->addItem(item);
    
    item = new QListWidgetItem(QIcon(":/images/tmp2.png"), tr("L shape"));
    templates->addItem(item);
   
    connect(templates, &QListWidget::currentRowChanged, this, &PlanDialog::setRoom);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(this);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    buttonBox->setCenterButtons(true);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &PlanDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &PlanDialog::reject);
    createRoomPropertiesBoxes();

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(templates);
    layout->addWidget(doubleSpinBoxesGroup);
    layout->addWidget(buttonBox);
    setLayout(layout);
    
    setWindowTitle(tr("New Project"));
}
void PlanDialog::createRoomPropertiesBoxes()
{
    doubleSpinBoxesGroup = new QGroupBox(tr("Room properties:"));

    QLabel* precisionLabel = new QLabel(tr("Number of decimal places to show:"));
    QSpinBox* precisionSpinBox = new QSpinBox;
    precisionSpinBox->setRange(0, 50);
    precisionSpinBox->setValue(2);
   
    QLabel* widthLabel = new QLabel(tr("[OX]Room width(m): "));
    widthSpinBox = new QDoubleSpinBox;
    widthSpinBox->setRange(2.0, 200.0);//2m-20m
    widthSpinBox->setSingleStep(0.5);
    widthSpinBox->setValue(10.0);
  
    QLabel* heightLabel = new QLabel(tr("[OY]Room height(m): "));
    heightSpinBox = new QDoubleSpinBox;
    heightSpinBox->setRange(2.0, 400.0); // 2m - 40m
    heightSpinBox->setSingleStep(0.5);
    heightSpinBox->setValue(20.0);
   

    connect(precisionSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),this, &PlanDialog::changePrecision);
  
    //aranjare
    QVBoxLayout* spinBoxLayout = new QVBoxLayout;
    spinBoxLayout->addWidget(precisionLabel);
    spinBoxLayout->addWidget(precisionSpinBox);
    spinBoxLayout->addWidget(widthLabel);
    spinBoxLayout->addWidget(widthSpinBox);
    spinBoxLayout->addWidget(heightLabel);
    spinBoxLayout->addWidget(heightSpinBox);
  
    doubleSpinBoxesGroup->setLayout(spinBoxLayout);
    doubleSpinBoxesGroup->setDisabled(true);
}


void PlanDialog::setSize()
{
    double w = widthSpinBox->value();
    double h = heightSpinBox->value();
    myRoom->updateSize(QSizeF(w * 100, h*100));
}

void PlanDialog::accept()
{
    setSize();
    //emit planInserted(); 
    setResult(Accepted);
    close();
}

void PlanDialog::setRoom(int idx)
{
    myRoom = new Room(idx);
    
    doubleSpinBoxesGroup->setDisabled(false);
    widthSpinBox->setValue(myRoom->getmySize().width() / 100);
    heightSpinBox->setValue(myRoom->getmySize().height() / 100);
}

//---------------------------------------------------------------------------------------------

Room::Room( int type,QGraphicsItem* parent)
{
    QPointF myCoordinates = QPointF(0,0);
    
    switch (type) {
    case 0://rectangle
        mySize = QSizeF(400, 600);
        myFigure<< QPointF(myCoordinates.x(), myCoordinates.y())
        << QPointF(myCoordinates.x() + mySize.width(), myCoordinates.y())
        << QPointF(myCoordinates.x() + mySize.width(), myCoordinates.y() + mySize.height())
        << QPointF(myCoordinates.x(), myCoordinates.y() + mySize.height())
        << QPointF(myCoordinates.x(), myCoordinates.y());
        break;

    case 1://L shaped
        mySize = QSize(700, 1000);
        myFigure << QPointF(myCoordinates.x(), myCoordinates.y())
            << QPointF(myCoordinates.x() + mySize.width(), myCoordinates.y())
            << QPointF(myCoordinates.x() + mySize.width(), myCoordinates.y() + mySize.height())
            << QPointF(myCoordinates.x() + mySize.width()/2, myCoordinates.y() + mySize.height())
            << QPointF(myCoordinates.x() + mySize.width() / 2, myCoordinates.y() + mySize.height()/2)
            << QPointF(myCoordinates.x(), myCoordinates.y() + mySize.height()/2)
            << QPointF(myCoordinates.x(), myCoordinates.y());
        break;
    }

    setPolygon(myFigure);
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, false);
}

void PlanDialog::changePrecision(int decimals)
{
    widthSpinBox->setDecimals(decimals);
    heightSpinBox->setDecimals(decimals);
    
}

