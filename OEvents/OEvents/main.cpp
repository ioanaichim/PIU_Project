#include "OEvents.h"
#include <QApplication>

/* 
* Functia main a proiectului
*/
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    OEvents window;
    window.setGeometry(100, 100, 800, 500); // setarea pozitionarii pe ecran si a dimensiunilor initiale ale ferestrei aplicatiei
    window.show();

    return app.exec();
}