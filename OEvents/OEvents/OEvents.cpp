#include "OEvents.h"

//ceea ce trebuia sa apara in fereastra principala
OEvents::OEvents()
{
    //QWidget* widget = new QWidget;
    //QGridLayout* layout = new QGridLayout(widget);

    //setCentralWidget(widget);
    //widget->setLayout(layout);

    //QGroupBox* box = new QGroupBox("", widget);
    //layout->addWidget(box, 0, 1, 1, 1);


    //QGroupBox* drawbox = new QGroupBox("Suprafata de desen:", widget);
    //drawbox->setMinimumSize(700, 700);
    //layout->addWidget(drawbox, 0, 2, 1, 2);

    //QVBoxLayout* boxLayout = new QVBoxLayout(box);
    //QVBoxLayout* drawLayout = new QVBoxLayout(drawbox);

    //QWidget* propertiesWidget = new QWidget(box);
    //QWidget* checkBoxWidget = new QWidget(box);

    //QWidget* drawWidget = new QWidget(drawbox);

    //QListWidget* listWidget = new QListWidget(box);

    //boxLayout->addWidget(new QLabel("Elemente de pus in scena:"));
    //boxLayout->addWidget(listWidget);
    //boxLayout->addWidget(propertiesWidget);
    //boxLayout->addWidget(checkBoxWidget);

    //drawLayout->addWidget(drawWidget);


    //QVBoxLayout* elementsLayout = new QVBoxLayout(listWidget);

    //QListWidgetItem* masa = new QListWidgetItem("Masa");
    //listWidget->addItem(masa);
    //QListWidgetItem* scaun = new QListWidgetItem("Scaun");
    //listWidget->addItem(scaun);
    //QListWidgetItem* scena = new QListWidgetItem("Scena");
    //listWidget->addItem(scena);
    //elementsLayout->addWidget(listWidget);

    //QVBoxLayout* propertiesLayout = new QVBoxLayout(propertiesWidget);
    //QTextEdit* text = new QTextEdit(propertiesWidget);
    //propertiesLayout->addWidget(new QLabel("Proprietetile elementului selectat:"));
    //propertiesLayout->addWidget(text);

    //QListWidgetItem* current = listWidget->currentItem();
    ////current->setText("A");
    //text->setText("Merge sa scriu text aici \n si sa il suprascriu");
    ////text->setText("aaa");

    //QHBoxLayout* checkBoxLayout = new QHBoxLayout(checkBoxWidget);
    //checkBoxLayout->addWidget(new QCheckBox(checkBoxWidget));
    //checkBoxLayout->addWidget(new QLabel("Distantare sociala                    "));

    //QVBoxLayout* drawingLayout = new QVBoxLayout(drawWidget);
    //drawingLayout->addWidget(new QLabel("Suprafata desen:"));
    //drawingLayout->addWidget(new QTextEdit(drawWidget));


    //layout->addWidget(new QLineEdit("Status:"), 1, 1, 1, 3);

    createActions();
    createPanel();
    createStatusBar();

    scene = new PlanScene(itemMenu, this);
    scene->setSceneRect(QRectF(0, 0, 5000, 5000));
    connect(scene, &PlanScene::itemInserted,
        this, &OEvents::itemInserted);
    connect(scene, &PlanScene::itemSelected,
        this, &OEvents::itemSelected);
    createToolbars();

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(toolBox);
    view = new QGraphicsView(scene);
    layout->addWidget(view);

    QWidget* widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("PlanScene"));
    setUnifiedTitleAndToolBarOnMac(true);
}

void OEvents::newProject()
{
    //TODO
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

//acea fct care avertizeaza userul ca nu si-a salvat ultimele modificari facte in proiect
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

    //TODO functionalitate de scriere a datelor necasare intr-un fisier text de exemplu

    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}


void OEvents::projectWasModified()
{
    //TODO
}

void OEvents::deleteItem()
{
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();
    
    for (QGraphicsItem* item : qAsConst(selectedItems)) {
        scene->removeItem(item);
        delete item;
    }
}

void OEvents::itemInserted(Element* item)
{
    //pointerTypeGroup->button(int(PlanScene::MoveItem))->setChecked(true);
    //scene->setMode(PlanScene::Mode(pointerTypeGroup->checkedId()));
   
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

void OEvents::fillButtonTriggered()
{
    scene->setItemColor(qvariant_cast<QColor>(fillAction->data()));
}


void OEvents::itemSelected(QGraphicsItem* item)
{
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
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(createCellWidget(tr("Table")), 0, 0);
    layout->addWidget(createCellWidget(tr("Chair")), 0, 1);

    QToolButton* textButton = new QToolButton;
    textButton->setCheckable(true);
    textButton->setIcon(QIcon(QPixmap(":/images/textpointer.png")));
    textButton->setIconSize(QSize(50, 50));
    QGridLayout* textLayout = new QGridLayout;
    textLayout->addWidget(textButton, 0, 0, Qt::AlignHCenter);
    textLayout->addWidget(new QLabel(tr("Text")), 1, 0, Qt::AlignCenter);
    QWidget* textWidget = new QWidget;
    textWidget->setLayout(textLayout);
    layout->addWidget(textWidget, 1, 1);

    layout->setRowStretch(3, 10);
    layout->setColumnStretch(2, 10);

    QWidget* itemWidget = new QWidget;
    itemWidget->setLayout(layout);

    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(itemWidget->sizeHint().width());
    toolBox->addItem(itemWidget, tr("Basic Elements Shapes"));
}

void OEvents::createActions()
{
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar* fileToolBar = addToolBar(tr("File"));
    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
    QAction* newAct = new QAction(newIcon, tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &OEvents::newProject);
    fileMenu->addAction(newAct);
    fileToolBar->addAction(newAct);

    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
    QAction* openAct = new QAction(openIcon, tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &OEvents::openProject);
    fileMenu->addAction(openAct);
    fileToolBar->addAction(openAct);

    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
    QAction* saveAct = new QAction(saveIcon, tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &OEvents::save);
    fileMenu->addAction(saveAct);
    fileToolBar->addAction(saveAct);


    fileMenu->addSeparator();
    deleteAction = new QAction(QIcon(":/images/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, &QAction::triggered, this, &OEvents::deleteItem);

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit application"));
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction* exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    
    exitAct->setStatusTip(tr("Exit the application"));

    QMenu* editMenu = menuBar()->addMenu(tr("&Edit"));
    QToolBar* editToolBar = addToolBar(tr("Edit"));


    QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction* aboutAct = helpMenu->addAction(tr("&About"), this, &OEvents::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    aboutAct->setShortcut(tr("F1"));


    QAction* aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));

}

void OEvents::createToolbars()
{
    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(deleteAction);

    //fill
    fillColorToolButton = new QToolButton;
    fillColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fillColorToolButton->setMenu(createColorMenu(SLOT(itemColorChanged()), Qt::white));
    fillAction = fillColorToolButton->menu()->defaultAction();
    fillColorToolButton->setIcon(createColorToolButtonIcon(":/images/floodfill.png", Qt::white));
    connect(fillColorToolButton, &QAbstractButton::clicked,this, &OEvents::fillButtonTriggered);
  
    //contur
    lineColorToolButton = new QToolButton;
    lineColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    lineColorToolButton->setMenu(createColorMenu(SLOT(lineColorChanged()), Qt::black));
    lineAction = lineColorToolButton->menu()->defaultAction();
    lineColorToolButton->setIcon(createColorToolButtonIcon(":/images/linecolor.png", Qt::black));
    //connect(lineColorToolButton, &QAbstractButton::clicked,this, &OEvents::lineButtonTriggered);

    colorToolBar = addToolBar(tr("Color"));
    colorToolBar->addWidget(fillColorToolButton);
    colorToolBar->addWidget(lineColorToolButton);

    QToolButton* pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/images/pointer.png"));
    QToolButton* linePointerButton = new QToolButton;
    linePointerButton->setCheckable(true);
    linePointerButton->setIcon(QIcon(":/images/linepointer.png"));


    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, &QComboBox::currentTextChanged, this, &OEvents::sceneScaleChanged);

    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(pointerButton);
    pointerToolbar->addWidget(linePointerButton);
    pointerToolbar->addWidget(sceneScaleCombo);
}

QWidget* OEvents::createBackgroundCellWidget(const QString & text, const QString & image)
{
    QToolButton* button = new QToolButton;
    button->setText(text);
    button->setIcon(QIcon(image));
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);


    QGridLayout* layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget* widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

//cell table cu elemente disponibile de pus in plan
QWidget* OEvents::createCellWidget(const QString & text)
{
    Element item( itemMenu);

    QToolButton* button = new QToolButton;
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget* widget = new QWidget;
    widget->setLayout(layout);

    return widget;
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



