#pragma once

#include <QtWidgets/QMainWindow>
//#include "ui_OEvents.h"
//#include <QMainWindow>
//#include <QWidget>
//#include <QVBoxLayout>
//#include <QPushButton>
//#include <QLabel>
//#include <QLineEdit>
//#include <QGroupBox>
//#include <QTextEdit>
//#include <QTextEdit>
//#include <QCheckBox>
//#include <QListWidget>
//#include <QPainter>
//#include <QMessageBox>
#include <iostream>
#include "Element.h"
#include "PlanScene.h"
#include <QToolBox>

#include <QtWidgets>

using namespace std;

class OEvents : public QMainWindow
{
    Q_OBJECT

public:
    OEvents();
    void loadProject(const QString& fileName); //TODO

private slots:
    void newProject();//TODO
    void openProject();//TODO
    bool save();//TODO
    bool maybeSave();//TODO
    void about();//TODO
    void projectWasModified();//TODO

   //---- actiuni/schimbari pe elementele ce se adauga in plan
    void deleteItem();
    void itemInserted(Element* item);

    void sceneScaleChanged(const QString& scale);
    void itemColorChanged();
    //void lineColorChanged();
    void fillButtonTriggered();
    void itemSelected(QGraphicsItem* item);

private:
    //tine de asezarea componentelor in aplicatie
    void createActions();
    void createStatusBar();
    //void readSettings();
    //void writeSettings();

    //panel cu elemente disponibile
    void createPanel();
    //bara cu instrumente ce se pot aplica pe elementul selectat
    void createToolbars();
   
    QWidget* createCellWidget(const QString& text, const QString& image);
    //meniu din care se pot alege culori
    QMenu* createColorMenu(const char* slot, QColor defaultColor);
    QIcon createColorToolButtonIcon(const QString& image, QColor color);
    QIcon createColorIcon(QColor color);

    PlanScene* scene;
    QGraphicsView* view;

    QString projectName;

    QAction* exitAction;
    QAction* addAction;
    QAction* deleteAction;

    QAction* aboutAction;

    QMenu* fileMenu;
    QMenu* itemMenu;
    QMenu* aboutMenu;

    QToolBar* textToolBar;
    QToolBar* editToolBar;
    QToolBar* colorToolBar;
    QToolBar* pointerToolbar;

    QComboBox* sceneScaleCombo;
    QComboBox* itemColorCombo;

    QToolBox* toolBox;
   /* QButtonGroup* buttonGroup;
    QButtonGroup* pointerTypeGroup;
    QButtonGroup* backgroundButtonGroup;*/
    QToolButton* fillColorToolButton;
    QToolButton* lineColorToolButton;

    QAction* fillAction;
    QAction* lineAction;
};

