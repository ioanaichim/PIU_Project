/********************************************************************************
** Form generated from reading UI file 'OEvents.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OEVENTS_H
#define UI_OEVENTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OEventsClass
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionClose;
    QAction *actionNew;
    QWidget *centralWidget;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OEventsClass)
    {
        if (OEventsClass->objectName().isEmpty())
            OEventsClass->setObjectName(QString::fromUtf8("OEventsClass"));
        OEventsClass->resize(599, 420);
        actionOpen = new QAction(OEventsClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(OEventsClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionClose = new QAction(OEventsClass);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionNew = new QAction(OEventsClass);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        centralWidget = new QWidget(OEventsClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(50, 10, 75, 24));
        OEventsClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(OEventsClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 599, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        OEventsClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OEventsClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        OEventsClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(OEventsClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        OEventsClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionClose);

        retranslateUi(OEventsClass);

        QMetaObject::connectSlotsByName(OEventsClass);
    } // setupUi

    void retranslateUi(QMainWindow *OEventsClass)
    {
        OEventsClass->setWindowTitle(QCoreApplication::translate("OEventsClass", "OEvents", nullptr));
        actionOpen->setText(QCoreApplication::translate("OEventsClass", "Open", nullptr));
        actionSave->setText(QCoreApplication::translate("OEventsClass", "Save", nullptr));
        actionClose->setText(QCoreApplication::translate("OEventsClass", "Close", nullptr));
        actionNew->setText(QCoreApplication::translate("OEventsClass", "New", nullptr));
        pushButton->setText(QCoreApplication::translate("OEventsClass", "PushButton", nullptr));
        menuFile->setTitle(QCoreApplication::translate("OEventsClass", "File", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("OEventsClass", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OEventsClass: public Ui_OEventsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OEVENTS_H
