/********************************************************************************
** Form generated from reading UI file 'APPHp9836.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef APPHP9836_H
#define APPHP9836_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_APPClass
{
public:
    QWidget* centralWidget;
    QRadioButton* radioButton;
    QMenuBar* menuBar;
    QToolBar* mainToolBar;
    QStatusBar* statusBar;

    void setupUi(QMainWindow* APPClass)
    {
        if (APPClass->objectName().isEmpty())
            APPClass->setObjectName(QStringLiteral("APPClass"));
        APPClass->resize(816, 493);
        centralWidget = new QWidget(APPClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        radioButton = new QRadioButton(centralWidget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(80, 70, 119, 23));
        APPClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(APPClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 816, 31));
        APPClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(APPClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        APPClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(APPClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        APPClass->setStatusBar(statusBar);

        retranslateUi(APPClass);

        QMetaObject::connectSlotsByName(APPClass);
    } // setupUi

    void retranslateUi(QMainWindow* APPClass)
    {
        APPClass->setWindowTitle(QApplication::translate("APPClass", "APP", Q_NULLPTR));
        radioButton->setText(QApplication::translate("APPClass", "RadioButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class APPClass : public Ui_APPClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // APPHP9836_H
