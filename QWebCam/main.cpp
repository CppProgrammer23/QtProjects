#include "mycamcon.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myCamCon w;
    w.show();
    return a.exec();
}
