#include <QApplication>
#include "Meswak.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);  
    Meswak* me = new Meswak(0);
    me->show();
    return app.exec();
}

