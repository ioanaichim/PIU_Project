#include "OEvents.h"
#include "PlanDialog.h"

/* Constructor cu ceea ce trebuia sa apara in fereastra principala*/
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
    //workwidget->setVisible(false);//indisponibil pana cand se incepe un nou proiect

    setCentralWidget(workwidget);
    setWindowTitle(tr("OEvents"));
    setUnifiedTitleAndToolBarOnMac(true);
}

/* Metoda publica pentru crearea unui proiect nou */
void OEvents::newProject()
{
    //TODO
    room = new Room(1);

    addPlan();
    //planDialog = new PlanDialog(room, this);
    //planDialog->setModal(true);
    //int dialogCode = planDialog->exec();

    //if (dialogCode == QDialog::Accepted) {
    //    room = planDialog->getmyRoom(); 
    //    //connect(planDialog, &PlanDialog::planInserted, this, &OEvents::addPlan);
    //    addPlan();
    //}
    
}

/* Metoda publica pentru actualizarea unui proiect existent */
void OEvents::loadProject(const QString& fileName)
{
    QString val;
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        val = file.readAll();
        file.close();
    }
    else
    {
        cout << "file open failed: " << fileName.toStdString() << endl;
    }

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject set = d.object();
    QJsonValue value = set.value(QString("chair1"));
    QJsonObject item = value.toObject();

    /* in case of string value get value and convert into string*/
    QJsonValue subobj = item["color"];

    /* in case of array get array and convert into string*/
    QJsonArray test = item["coordinates"].toArray();

    QTextStream in(&file);//setari salvate intr-un fisier txt de ex
    //TODO creare si apelare fct care citeste setarile si datele din fisier
    //dupa care actualizare status bar
    statusBar()->showMessage(tr("File loaded"), 2000);
}

/* Metoda publica pentru deschiderea unui proiect existent */
void OEvents::openProject()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadProject(fileName);
}

/* Metoda publica pentru afisarea mesajului initial al status-ului */
void OEvents::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

/* Metoda pentru avertuzarea userului ca nu au fost salvate ultimele modificari facute in proiect */
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

/* Metoda publica pentru salvarea documentului */
bool OEvents::save()
{
    //functionalitate de scriere a datelor necasare intr-un fisier JSON
    QString fileName = QFileDialog::getSaveFileName(this);

    QJsonDocument document;
    QJsonObject mainObject;
    //mainObject.insert("chair1", element->write());
    //mainObject.insert("chair2", element->write());
    mainObject.insert("chair1", "green");
    mainObject.insert("chair2", "red");
    document.setObject(mainObject);
    QByteArray bytes = document.toJson(QJsonDocument::Indented);

    QFile file(fileName + ".json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream iStream(&file);
        iStream.setCodec("utf-8");
        iStream << bytes;
        file.close();
    }
    else
    {
        cout << "file open failed: " << fileName.toStdString() << endl;
    }

    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

/* Metoda publica pentru verificarea daca proiectul a fost modificat de la ultima salvare */
void OEvents::projectWasModified()
{

}

/* Metoda publica pentru adaugare unui plan */
void OEvents::addPlan()
{ 
    //workwidget->setVisible(true);
    
    QPen pen(Qt::blue, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    scene->clear();
    scene->setBackgroundBrush(Qt::gray);
    room->setPen( pen);
    room->setBrush(Qt::white);

    scene->setSceneRect(room->boundingRect());
    scene->addItem(room);
    scene->setFocusItem(room);

}

/* Metoda publica pentru stergerea unui element */
void OEvents::deleteItem()
{
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();
    
    for (QGraphicsItem* item : qAsConst(selectedItems)) {
        scene->removeItem(item);
        delete item;
    }
}

/* Metoda publica pentru duplicare unui element */
void OEvents::duplicateItem()
{
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();

    for (QGraphicsItem* item : qAsConst(selectedItems)) {
        scene->addItem(item);
        
    }
}

/* Metoda publica pentru schimbarea zoom-ului suprafetei de desenare */
void OEvents::sceneScaleChanged(const QString& scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QTransform oldMatrix = view->transform();
    view->resetTransform();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}

/* Metoda publica pentru schimbarea culorii unui element */
void OEvents::itemColorChanged()
{
    fillAction = qobject_cast<QAction*>(sender());
    fillColorToolButton->setIcon(createColorToolButtonIcon( ":/images/floodfill.png",
        qvariant_cast<QColor>(fillAction->data())));
    fillButtonTriggered();
}

/* Metoda publica pentru schimbarea culorii conturului unui element */
void OEvents::lineColorChanged()
{
}

/* Metoda publica pentru schimbarea culorii unui element */
void OEvents::fillButtonTriggered()
{
    scene->setItemColor(qvariant_cast<QColor>(fillAction->data()));
}

/* Metoda publica pentru schimbarea culorii conturului unui element */
void OEvents::lineButtonTriggered()
{
    scene->setLineColor(qvariant_cast<QColor>(lineAction->data()));
}

/* Metoda publica pentru selectarea unui item din scena cu ajutorul mouse-ului */
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

/* Metoda publica pentru inserare */
void OEvents::itemInserted(Element* item)
{
    /*pointerTypeGroup->button(int(PlanScene::MoveItem))->setChecked(true);
    scene->setMode(PlanScene::Mode(pointerTypeGroup->checkedId()));
    buttonGroup->button(int(item->diagramType()))->setChecked(false);*/
}

/* Metoda publica pentru butonul About cu informatii despre proiect */
void OEvents::about()
{
    QMessageBox::about(this, tr("About Application"),
        tr("The <b>OEvents planning</b> "
            "GUI application using Qt, with a menu bar, "
            "toolbars, and a status bar."));
}

/* Metoda publica pentru crearea panelul cu elemente disponibile de pus in plan */
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

/* Metoda publica pentru construire bara de meniu si bara de instrumente */
void OEvents::createActions()
{
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

/* Metoda publica pentru bara cu instrumente ce se pot aplica pe elementul selectat */
void OEvents::createToolbars()
{
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

/* Metoda publica pentru celula de baza de afisare a elementelor ce sunt disponibile (cell table cu elemente disponibile de pus in plan) */
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
/* Metoda publica pentru crearea celulei de proprietati ale elemetului */
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
/* Metoda publica care trateaza un grup de butoane */
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
//QMenu* OEvents::createColorMenu(const char* slot, QColor defaultColor)
//{
//    QList<QColor> colors;
//    colors << Qt::black << Qt::white << Qt::red << Qt::blue << Qt::yellow;
//    QStringList names;
//    names << tr("black") << tr("white") << tr("red") << tr("blue")
//        << tr("yellow");
//
//    QMenu* colorMenu = new QMenu(this);
//    for (int i = 0; i < colors.count(); ++i) {
//        QAction* action = new QAction(names.at(i), this);
//        action->setData(colors.at(i));
//        action->setIcon(createColorIcon(colors.at(i)));
//        connect(action, SIGNAL(triggered()), this, slot);
//        colorMenu->addAction(action);
//        if (colors.at(i) == defaultColor)
//            colorMenu->setDefaultAction(action);
//    }
//    return colorMenu;
//}

/* Metoda publica pentru meniul din care se pot alege culori */
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

/* Metoda publica pentru culoare */
QIcon OEvents::createColorIcon(QColor color)
{
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}



