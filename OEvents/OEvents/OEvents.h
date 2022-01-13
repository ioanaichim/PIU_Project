#pragma once

#include <QtWidgets/QMainWindow>

#include <iostream>
#include "Element.h"
#include "PlanScene.h"
#include "PlanDialog.h"
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
    bool maybeSave();//TODO--- made
    void about();//TODO--prototype made
    void projectWasModified();//TODO
    void addPlan();
   //---- actiuni/schimbari pe elementele ce se adauga in plan
    void deleteItem();

    void duplicateItem();

    void sceneScaleChanged(const QString& scale);
    void itemColorChanged();
    void lineColorChanged();
    void fillButtonTriggered();
    void lineButtonTriggered();
    void itemSelected(QGraphicsItem* item);

    void itemInserted(Element* item);

private:
    //tine de asezarea componentelor in aplicatie, in fereastra principala
    void createActions();
    void createStatusBar();


    //panel cu elemente disponibile de pus in plan
    void createPanel();
    //bara cu instrumente ce se pot aplica pe elementul selectat
    void createToolbars();
   
    //celula de baza de afisare a elementelor ce sunt disponibile
    QWidget* createCellWidget(const QString& text, const QString& image, Element::ElementType type);
    QWidget* createCellWidgetProperty(const QString& name,double val);
    void buttonGroupClicked(QAbstractButton* button);
    //meniu din care se pot alege culori
    QMenu* createColorMenu(const char* slot, QColor defaultColor);
    QIcon createColorToolButtonIcon(const QString& image, QColor color);
    QIcon createColorIcon(QColor color);

    PlanScene* scene;
    QGraphicsView* view;
    PlanDialog* planDialog;
    QWidget* workwidget;
    Room* room;
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

    QWidget* propertiesWidget;
    QToolBox* toolBox;
    QToolButton* fillColorToolButton;
    QToolButton* lineColorToolButton;
    QButtonGroup* buttonGroup;

    QAction* fillAction;
    QAction* lineAction;

};

