#include "PlanDialog.h"

/* Constructor */
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

/* Metoda publica pentru proprietati */
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

/* Metoda publica pentru setarea dimensiunilor camerei */
void PlanDialog::setSize()
{
    double w = widthSpinBox->value();
    double h = heightSpinBox->value();
    myRoom->updateSize(QSizeF(w * 100, h*100));
}

/* Metoda publica */
void PlanDialog::accept()
{
    setSize();
    //emit planInserted(); 
    setResult(Accepted);
    close();
}

/* Metoda publica pentru setarea camerei */
void PlanDialog::setRoom(int idx)
{
    myRoom = new Room(idx);
    
    doubleSpinBoxesGroup->setDisabled(false);
    widthSpinBox->setValue(myRoom->getmySize().width() / 100);
    heightSpinBox->setValue(myRoom->getmySize().height() / 100);
}


/* Schimbarea preciziei dimensiunilor */
void PlanDialog::changePrecision(int decimals)
{
    widthSpinBox->setDecimals(decimals);
    heightSpinBox->setDecimals(decimals);
    
}

