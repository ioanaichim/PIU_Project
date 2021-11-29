#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_APP.h"

class APP : public QMainWindow
{
    Q_OBJECT

public:
    APP(QWidget *parent = Q_NULLPTR);

private:
    Ui::APPClass ui;
};
