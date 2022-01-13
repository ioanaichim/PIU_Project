#include "OEvents.h"
#include "PlanDialog.h"

//ceea ce trebuia sa apara in fereastra principala
OEvents::OEvents()
{
    createActions();
    createPanel();
    createStatusBar();

    scene = new PlanScene(itemMenu, this);
    scene->setSceneRect(QRectF(0, 0, 5000, 5000));
    //connect(scene, &PlanScene::itemInserted,this, &OEvents::itemInserted);
    connect(scene, &PlanScene::itemSelected,this, &OEvents::itemSelected);
    
   
    createToolbars();

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(toolBox);
    view = new QGraphicsView(scene);
    layout->addWidget(view);

    QWidget* workwidget = new QWidget;
    workwidget->setLayout(layout);
    //workwidget->setVisible(false);

    setCentralWidget(workwidget);
    setWindowTitle(tr("OEvents"));
    setUnifiedTitleAndToolBarOnMac(true);
}

void OEvents::newProject()
{
    //TODO
    room = new Room();
    addPlan();
    //planDialog = new PlanDialog(room, this);
    //planDialog->setModal(true);
    //planDialog->exec();
    //connect(planDialog, &PlanDialog::planInserted, this, &OEvents::addPlan);
}

void OEvents::loadProject(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("OEvents"),
            tr("Cannot read file %1:\n%2.")
            .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);//setari salvate intr-un fisier txt de ex
    //TODO creare si apelare fct care citeste setarile si datele din fisier
    //dupa care actualizare status bar
    statusBar()->showMessage(tr("File loaded"), 2000);
}

void OEvents::openProject()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadProject(fileName);
}

void OEvents::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

//acea fct care avertizeaza userul ca nu si-a salvat ultimele modificari facute in proiect
bool OEvents::maybeSave()
{
    if (scene->hasChanges())
        return true;
    const QMessageBox::StandardButton ret
        = QMessageBox::warning(this, tr("Application"),
            tr("The project has been modified.\n"
                "Do you want to save your changes?"),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret) {
    case QMessageBox::Save:
        return save();
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}

bool OEvents::save()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Plan Scene"), "",
        tr("Json file (*.json);;All Files (*)"));

    QFile saveFile=QString(fileName);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }
    for each (QGraphicsItem * item in scene->items())
    {
        QJsonObject planObject;
        /*planObject["type"] = item->type();   
        planObject["shape"] = item->shape();
        planObject["size"] = item->size();
        planObject["coords"] = item->pos();    
        planObject["color"] = item->color();
        write(planObject);*/
        saveFile.write(QJsonDocument(planObject).toJson());
    } 

    return true;
    //TODO functionalitate de scriere a datelor necasare intr-un fisier text de exemplu

    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}


void OEvents::projectWasModified()
{
    //TODO
}

void OEvents::addPlan()
{ 
    //workwidget->setVisible(true);
    // if(scene->items().count()>0)
    scene->clear();
    room->setBrush(Qt::darkYellow);
    
    scene->addItem(room);
    

}

void OEvents::deleteItem()
{
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();
    
    for (QGraphicsItem* item : qAsConst(selectedItems)) {
        scene->removeItem(item);
        delete item;
    }
}
void OEvents::duplicateItem()
{
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();

    for (QGraphicsItem* item : qAsConst(selectedItems)) {
        scene->addItem(item);
        
    }
}


void OEvents::sceneScaleChanged(const QString& scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QTransform oldMatrix = view->transform();
    view->resetTransform();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}

void OEvents::itemColorChanged()
{
    fillAction = qobject_cast<QAction*>(sender());
    fillColorToolButton->setIcon(createColorToolButtonIcon( ":/images/floodfill.png",
        qvariant_cast<QColor>(fillAction->data())));
    fillButtonTriggered();
}

void OEvents::lineColorChanged()
{
}

void OEvents::fillButtonTriggered()
{
    scene->setItemColor(qvariant_cast<QColor>(fillAction->data()));
}

void OEvents::lineButtonTriggered()
{
    scene->setLineColor(qvariant_cast<QColor>(lineAction->data()));
}

void OEvents::itemSelected(QGraphicsItem* item)
{
    Element* selItem =qgraphicsitem_cast<Element*>(item);
    //update properties
    QVBoxLayout* propertiesLayout = new QVBoxLayout(propertiesWidget);
    propertiesLayout->addWidget(createCellWidgetProperty("Length:", selItem->getmySize().height()));
    propertiesLayout->addWidget(createCellWidgetProperty("Width:", selItem->getmySize().width()));
    propertiesLayout->addWidget(createCellWidgetProperty("Position x:", selItem->getmyCoordinates().x()));
    propertiesLayout->addWidget(createCellWidgetProperty("Position y:", selItem->getmyCoordinates().y()));

    propertiesWidget->setLayout(propertiesLayout);
    
}

void OEvents::itemInserted(Element* item)
{
    /*pointerTypeGroup->button(int(PlanScene::MoveItem))->setChecked(true);
    scene->setMode(PlanScene::Mode(pointerTypeGroup->checkedId()));
    buttonGroup->button(int(item->diagramType()))->setChecked(false);*/
}

void OEvents::about()
{
    QMessageBox::about(this, tr("About Application"),
        tr("The <b>OEvents</b> "
            "GUI application using Qt, with a menu bar, "
            "toolbars, and a status bar."));
}


void OEvents::createPanel()
{
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    connect(buttonGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this, &OEvents::buttonGroupClicked);
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(createCellWidget(tr("Table"),":/images/table.png",Element::ElementType::Table), 0, 0);
    layout->addWidget(createCellWidget(tr("Chair"),":/images/chair.png", Element::ElementType::Chair), 0, 1);
    layout->addWidget(createCellWidget(tr("Stage"),":/images/stage.png", Element::ElementType::Stage), 1, 0);
    layout->addWidget(createCellWidget(tr("Buffet"),":/images/buffet.png", Element::ElementType::Buffet), 1, 1);

    layout->setRowStretch(3, 10);
    layout->setColumnStretch(2, 10);

    QWidget* itemWidget = new QWidget;
    itemWidget->setLayout(layout);

    QWidget* propertiesWidget = new QWidget;
    QVBoxLayout* propertiesLayout = new QVBoxLayout(propertiesWidget);
    propertiesLayout->addWidget(createCellWidgetProperty("Length:", 0.0));
    propertiesLayout->addWidget(createCellWidgetProperty("Width:", 0.0 /*selItem->getmySize().width()*/));
    propertiesLayout->addWidget(createCellWidgetProperty("Position x:", 0.0 /*selItem->getmyCoordinates().x()*/));
    propertiesLayout->addWidget(createCellWidgetProperty("Position y:", 0.0/*selItem->getmyCoordinates().y()*/));

    propertiesWidget->setLayout(propertiesLayout);

    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(itemWidget->sizeHint().width());
    toolBox->addItem(itemWidget, tr("Basic Elements "));
    toolBox->addItem(propertiesWidget, tr("Element Properties "));


}

void OEvents::createActions()
{
    //bara de meniu + bara de instrumente
    QMenu* fileMenu = menuBar()->addMenu(tr("File"));
    QToolBar* fileToolBar = addToolBar(tr("File"));
    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
    QAction* newAct = new QAction(newIcon, tr("New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &OEvents::newProject);
    fileMenu->addAction(newAct);
    fileToolBar->addAction(newAct);

    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
    QAction* openAct = new QAction(openIcon, tr("Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &OEvents::openProject);
    fileMenu->addAction(openAct);
    fileToolBar->addAction(openAct);

    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
    QAction* saveAct = new QAction(saveIcon, tr("Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the project to disk"));
    connect(saveAct, &QAction::triggered, this, &OEvents::save);
    fileMenu->addAction(saveAct);
    fileToolBar->addAction(saveAct);


    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction* exitAct = fileMenu->addAction(exitIcon, tr("Exit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));

    QMenu* editMenu = menuBar()->addMenu(tr("&Edit"));
    QToolBar* editToolBar = addToolBar(tr("Edit"));
    const QIcon deleteIcon = QIcon::fromTheme("item-delete", QIcon(":/images/delete.png"));
    QAction* deleteAction = new QAction(deleteIcon, tr("Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from scene"));
    connect(deleteAction, &QAction::triggered, this, &OEvents::deleteItem);
    editMenu->addAction(deleteAction);
    editToolBar->addAction(deleteAction);

    const QIcon copyIcon = QIcon::fromTheme("item-copy", QIcon(":/images/copy.png"));
    QAction* copyAction = new QAction(copyIcon, tr("Duplicate"), this);
    copyAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    copyAction->setStatusTip(tr("Duplicate item from scene"));
    connect(copyAction, &QAction::triggered, this, &OEvents::duplicateItem);
    //connect(copyAction, &QAction::triggered, this, &OEvents::duplicateItem);
    editMenu->addAction(copyAction);
    editToolBar->addAction(copyAction);


    QMenu* helpMenu = menuBar()->addMenu(tr("Help"));
    QAction* aboutAct = helpMenu->addAction(tr("About"), this, &OEvents::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    aboutAct->setShortcut(tr("F1"));
    QAction* aboutQtAct = helpMenu->addAction(tr("About Qt"), qApp, &QApplication::aboutQt);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));

}

void OEvents::createToolbars()
{
    //fill
    fillColorToolButton = new QToolButton;
    fillColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fillColorToolButton->setMenu(createColorMenu(SLOT(itemColorChanged()), Qt::white));
    fillColorToolButton->setStatusTip(tr("Item fill color"));
    fillAction = fillColorToolButton->menu()->defaultAction();
    fillColorToolButton->setIcon(createColorToolButtonIcon(":/images/floodfill.png", Qt::white));
    connect(fillColorToolButton, &QAbstractButton::clicked,this, &OEvents::fillButtonTriggered);
  
    //contur
    lineColorToolButton = new QToolButton;
    lineColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    lineColorToolButton->setMenu(createColorMenu(SLOT(lineColorChanged()), Qt::black));
    lineColorToolButton->setStatusTip(tr("Item line color"));
    lineAction = lineColorToolButton->menu()->defaultAction();
    lineColorToolButton->setIcon(createColorToolButtonIcon(":/images/linecolor.png", Qt::black));
    connect(lineColorToolButton, &QAbstractButton::clicked,this, &OEvents::lineButtonTriggered);

    colorToolBar = addToolBar(tr("Color"));
    colorToolBar->addWidget(fillColorToolButton);
    colorToolBar->addWidget(lineColorToolButton);

    sceneScaleCombo = new QComboBox;
    sceneScaleCombo->setStatusTip(tr("Zoom"));
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%")<< tr("200%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, &QComboBox::currentTextChanged, this, &OEvents::sceneScaleChanged);

    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(sceneScaleCombo);
}


//cell table cu elemente disponibile de pus in plan
QWidget* OEvents::createCellWidget(const QString & text,const QString & image,Element::ElementType type)
{

    QToolButton* button = new QToolButton;
    button->setIconSize(QSize(50, 50));
    button->setIcon(QIcon(image));
    button->setCheckable(true);
    buttonGroup->addButton(button, int(type));

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget* widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}
QWidget* OEvents::createCellWidgetProperty(const QString& name,double val)
{
    QWidget* widget = new QWidget;
    QGridLayout* layout = new QGridLayout;
    QDoubleSpinBox* value = new QDoubleSpinBox(widget);
    value->setValue(val);
    layout->addWidget(new QLabel(name), 0, 0);
    layout->addWidget(value, 0, 1);
    //connect(value, QSpinBox::valueChanged, scene, propertyChanged);

    widget->setLayout(layout);

    return widget;
}

void OEvents::buttonGroupClicked(QAbstractButton* button)
{
    const QList<QAbstractButton*> buttons = buttonGroup->buttons();
    for (QAbstractButton* myButton : buttons) {
        if (myButton != button)
            button->setChecked(false);
    }
    const int id = buttonGroup->id(button);
    
    scene->setItemType(Element::ElementType(id));
    scene->setMode(PlanScene::InsertItem);
}

//sectiune din care pot alege culoarea
QMenu* OEvents::createColorMenu(const char* slot, QColor defaultColor)
{
    QList<QColor> colors;
    colors << Qt::black << Qt::white << Qt::red << Qt::blue << Qt::yellow;
    QStringList names;
    names << tr("black") << tr("white") << tr("red") << tr("blue")
        << tr("yellow");

    QMenu* colorMenu = new QMenu(this);
    for (int i = 0; i < colors.count(); ++i) {
        QAction* action = new QAction(names.at(i), this);
        action->setData(colors.at(i));
        action->setIcon(createColorIcon(colors.at(i)));
        connect(action, SIGNAL(triggered()), this, slot);
        colorMenu->addAction(action);
        if (colors.at(i) == defaultColor)
            colorMenu->setDefaultAction(action);
    }
    return colorMenu;
}
QIcon OEvents::createColorToolButtonIcon(const QString& imageFile, QColor color)
{
    QPixmap pixmap(50, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image(imageFile);
    // Draw icon centred horizontally on button.
    QRect target(4, 0, 42, 43);
    QRect source(0, 0, 42, 43);
    painter.fillRect(QRect(0, 60, 50, 80), color);
    painter.drawPixmap(target, image, source);

    return QIcon(pixmap);
}

QIcon OEvents::createColorIcon(QColor color)
{
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}



