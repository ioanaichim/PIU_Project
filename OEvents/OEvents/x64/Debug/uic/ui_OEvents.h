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
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OEventsClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OEventsClass)
    {
        if (OEventsClass->objectName().isEmpty())
            OEventsClass->setObjectName(QString::fromUtf8("OEventsClass"));
        OEventsClass->resize(600, 400);
        menuBar = new QMenuBar(OEventsClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        OEventsClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OEventsClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        OEventsClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(OEventsClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        OEventsClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(OEventsClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        OEventsClass->setStatusBar(statusBar);

        retranslateUi(OEventsClass);

        QMetaObject::connectSlotsByName(OEventsClass);
    } // setupUi

    void retranslateUi(QMainWindow *OEventsClass)
    {
        OEventsClass->setWindowTitle(QCoreApplication::translate("OEventsClass", "OEvents", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OEventsClass: public Ui_OEventsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OEVENTS_H
