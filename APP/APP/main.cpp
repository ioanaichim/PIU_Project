#include "APP.h"
#include <QApplication>

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QTextEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QListWidget>
#include <QPainter>
#include <QMessageBox>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;
    QWidget* widget = new QWidget(&window);
    QGridLayout* layout = new QGridLayout(widget);

    window.setCentralWidget(widget);
    widget->setLayout(layout);

    QGroupBox* box = new QGroupBox("", widget);
    layout->addWidget(box, 0, 1, 1, 1);


    QGroupBox* drawbox = new QGroupBox("Suprafata de desen:", widget);
    drawbox->setMinimumSize(700, 700);
    layout->addWidget(drawbox, 0, 2, 1, 2);

    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    QVBoxLayout* drawLayout = new QVBoxLayout(drawbox);

    QWidget* propertiesWidget = new QWidget(box);
    QWidget* checkBoxWidget = new QWidget(box);

    QWidget* drawWidget = new QWidget(drawbox);

    QListWidget* listWidget = new QListWidget(box);

    boxLayout->addWidget(new QLabel("Elemente de pus in scena:"));
    boxLayout->addWidget(listWidget);
    boxLayout->addWidget(propertiesWidget);
    boxLayout->addWidget(checkBoxWidget);

    drawLayout->addWidget(drawWidget);


    QVBoxLayout* elementsLayout = new QVBoxLayout(listWidget);

    QListWidgetItem* masa = new QListWidgetItem("Masa");
    listWidget->addItem(masa);
    QListWidgetItem* scaun = new QListWidgetItem("Scaun");
    listWidget->addItem(scaun);
    QListWidgetItem* scena = new QListWidgetItem("Scena");
    listWidget->addItem(scena);
    elementsLayout->addWidget(listWidget);

    QVBoxLayout* propertiesLayout = new QVBoxLayout(propertiesWidget);
    QTextEdit* text = new QTextEdit(propertiesWidget);
    propertiesLayout->addWidget(new QLabel("Proprietetile elementului selectat:"));
    propertiesLayout->addWidget(text);

    QListWidgetItem* current = listWidget->currentItem();
    //current->setText("A");
    text->setText("Merge sa scriu text aici \n si sa il suprascriu");
    //text->setText("aaa");

    QHBoxLayout* checkBoxLayout = new QHBoxLayout(checkBoxWidget);
    checkBoxLayout->addWidget(new QCheckBox(checkBoxWidget));
    checkBoxLayout->addWidget(new QLabel("Distantare sociala                    "));

    QVBoxLayout* drawingLayout = new QVBoxLayout(drawWidget);
    drawingLayout->addWidget(new QLabel("Suprafata desen:"));
    drawingLayout->addWidget(new QTextEdit(drawWidget));

    
    layout->addWidget(new QLineEdit("Status:"), 1, 1, 1, 3);

    window.show();

    return a.exec();
}