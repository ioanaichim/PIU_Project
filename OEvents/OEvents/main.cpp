#include "OEvents.h"
#include <QApplication>


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    OEvents window;
    window.setGeometry(100, 100, 800, 500);
    window.show();

    return app.exec();
}