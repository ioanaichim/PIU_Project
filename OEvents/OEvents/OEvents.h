#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OEvents.h"

class OEvents : public QMainWindow
{
    Q_OBJECT

public:
    OEvents(QWidget *parent = Q_NULLPTR);
    ~OEvents();

private:
    Ui::OEventsClass ui;
};
