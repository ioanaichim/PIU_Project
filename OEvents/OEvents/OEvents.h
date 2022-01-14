#pragma once

#include <QtWidgets/QMainWindow>

#include <iostream>
#include "Element.h"
#include "PlanScene.h"
#include "PlanDialog.h"
#include <QToolBox>

#include <QJsonObject>
#include <QtWidgets>

using namespace std;

/* ! \class OEvents
     *   \brief Clasă principala a proiectului / GUI
*/
class OEvents : public QMainWindow
{
    /* Macro non-standard pentru adăugarea unui comportament dinamic al claselor/obiectelor */
    /* Sintaxa pentru semnale si sloturi nu respectă standardele C++,
    este prelucrată de MOC, de aceea apare macro-ul Q_OBJECT */
    Q_OBJECT

public:
    /* Metode publice */
    OEvents();
    void loadProject(const QString& fileName);
    /*Proprietate publica*/
    Element* element;

private slots:
    /* Metode publice */
    void newProject();
    void openProject();
    bool save();
    bool maybeSave();
    void about();
    void projectWasModified();
    void addPlan();
    /* Metode publice referitoare la actiuni/schimbari pe elementele ce se adauga in plan*/
    void deleteItem();
    void duplicateItem();
    void itemColorChanged();
    void lineColorChanged();
    void fillButtonTriggered();
    void itemSelected(QGraphicsItem* item);
    void itemInserted(Element* item);

    void sceneScaleChanged(const QString& scale);

private:
    /* Metode private pentru asezarea componentelor in aplicatie, in fereastra principala */
    void createActions();
    void createStatusBar();

    void createPanel();
    void createToolbars();
   
    QWidget* createCellWidget(const QString& text, const QString& image, Element::ElementType type);
    QWidget* createCellWidgetProperty(const QString& name,double val);
    void buttonGroupClicked(QAbstractButton* button);

    //QMenu* createColorMenu(const char* slot, QColor defaultColor);
    QIcon createColorToolButtonIcon(const QString& image, QColor color);
    QIcon createColorIcon(QColor color);

    /* Proprietatile private ale clasei */
    PlanScene* scene;
    QGraphicsView* view;
    PlanDialog* planDialog;
    QWidget* workwidget;
    Room* room;
    QString projectName;
    QList<Element*> elements;

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

